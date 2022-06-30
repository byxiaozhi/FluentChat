#include "pch.h"
#include "ChatFriend.xaml.h"
#include "App.xaml.h"
#include "winrt/Windows.System.Threading.h"
#if __has_include("ChatFriend.g.cpp")
#include "ChatFriend.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Data::Json;
using namespace Microsoft::UI::Xaml::Data;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::FluentChat::implementation
{
	ChatFriend::ChatFriend()
	{
		InitializeComponent();
	}
	FluentChat::AppViewModel ChatFriend::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}
	FluentChat::TransportService ChatFriend::TransportService()
	{
		return AppViewModel().TransportService();
	}
	IAsyncAction ChatFriend::Button_SendMsg_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		if (TextBox_Send().Text() == L"")
			return;
		try {
			auto message = JsonValue::CreateStringValue(TextBox_Send().Text());
			auto friendId = AppViewModel().ChatViewModel().ChatInfo().GetNamedValue(L"friendId");
			JsonObject json;
			json.SetNamedValue(L"friendId", friendId);
			json.SetNamedValue(L"message", message);
			auto response = co_await TransportService().InvokeAsync(L"message", L"sendFriendMessage", json);
			if (response.GetNamedBoolean(L"success")) {
				TextBox_Send().Text(L"");
				JsonObject json;
				json.SetNamedValue(L"nickName", JsonValue::CreateStringValue(AppViewModel().UserViewModel().NickName()));
				json.SetNamedValue(L"message", message);
				json.SetNamedValue(L"position", JsonValue::CreateStringValue(L"right"));
				ListView_Messages().Items().Append(json);
			}
		}
		catch (winrt::hresult_error const& ex) {
			ContentDialog(L"发送失败", L"未知错误");
		}
	}
	IAsyncAction ChatFriend::ListView_Messages_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		co_await LoadMessage();
	}
	void ChatFriend::UserControl_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		m_ChatViewModel_EventToken = AppViewModel().ChatViewModel().PropertyChanged({ this ,&ChatFriend::ChatViewModel_PropertyChanged });
		m_OnDispatch_EventToken = AppViewModel().TransportService().OnDispatch({ this, &ChatFriend::OnDispatch });
	}
	void ChatFriend::UserControl_Unloaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		AppViewModel().ChatViewModel().PropertyChanged(m_ChatViewModel_EventToken);
		AppViewModel().TransportService().OnDispatch(m_OnDispatch_EventToken);
	}
	IAsyncAction ChatFriend::LoadMessage()
	{
		auto chatInfo = AppViewModel().ChatViewModel().ChatInfo();
		if (chatInfo == nullptr)
			return;
		auto friendId = chatInfo.GetNamedValue(L"friendId");
		if (friendId == nullptr)
			return;
		JsonObject json;
		json.SetNamedValue(L"friendId", friendId);
		auto response = co_await TransportService().InvokeAsync(L"message", L"getFriendMessages", json);
		auto messages = response.GetNamedArray(L"messages");
		ListView_Messages().Items().Clear();
		for (auto& item : messages)
		{
			auto itemJson = item.GetObjectW();
			auto isSelf = itemJson.GetNamedValue(L"from").GetObjectW().GetNamedString(L"email") == AppViewModel().UserViewModel().Email();
			itemJson.SetNamedValue(L"position", JsonValue::CreateStringValue(isSelf ? L"right" : L"left"));
			ListView_Messages().Items().InsertAt(0, itemJson);
		}
	}
	void ChatFriend::SendMessage_Invoked(winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator const& sender, winrt::Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const& args)
	{
		Button_SendMsg_Click(Button_SendMsg(), nullptr);
	}
	void ChatFriend::OnDispatch(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Data::Json::JsonObject const& e)
	{
		auto& args = e.GetNamedObject(L"args").GetObjectW();
		if (e.GetNamedString(L"name") == L"messageReceive") {
			auto& from = args.GetNamedObject(L"from").GetObjectW();
			if (from.GetNamedNumber(L"friendId") == AppViewModel().ChatViewModel().ChatInfo().GetNamedNumber(L"friendId")) {
				args.SetNamedValue(L"position", JsonValue::CreateStringValue(L"left"));
				ListView_Messages().Items().Append(args);
			}
		}
	}
	HorizontalAlignment ChatFriend::BubblePositionConverter(Windows::Data::Json::JsonObject args)
	{
		auto position = args.GetNamedString(L"position");
		return position == L"right" ? HorizontalAlignment::Right : HorizontalAlignment::Left;
	}
	IAsyncAction ChatFriend::ContentDialog(hstring title, hstring content)
	{
		auto dialog = Controls::ContentDialog();
		dialog.XamlRoot(this->XamlRoot());
		dialog.Title(box_value(title));
		dialog.Content(box_value(content));
		dialog.CloseButtonText(L"确定");
		co_await dialog.ShowAsync();
	}
	void ChatFriend::ChatViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e)
	{
		if (e.PropertyName() == L"ChatInfo") {
			LoadMessage();
		}
	}
}
