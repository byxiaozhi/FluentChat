#include "pch.h"
#include "ChatGroup.xaml.h"
#include "App.xaml.h"
#include "winrt/Windows.System.Threading.h"
#if __has_include("ChatGroup.g.cpp")
#include "ChatGroup.g.cpp"
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
	ChatGroup::ChatGroup()
	{
		InitializeComponent();
	}
	FluentChat::AppViewModel ChatGroup::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}
	FluentChat::TransportService ChatGroup::TransportService()
	{
		return AppViewModel().TransportService();
	}
	IAsyncAction ChatGroup::Button_SendMsg_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto message = JsonValue::CreateStringValue(TextBox_Send().Text());
		auto groupId = AppViewModel().ChatViewModel().ChatInfo().GetNamedValue(L"groupId");
		JsonObject json;
		json.SetNamedValue(L"groupId", groupId);
		json.SetNamedValue(L"message", message);
		auto response = co_await TransportService().InvokeAsync(L"message", L"sendGroupMessage", json);
		if (response.GetNamedBoolean(L"success")) {
			TextBox_Send().Text(L"");
			JsonObject json;
			JsonObject from;
			from.SetNamedValue(L"nickName", JsonValue::CreateStringValue(AppViewModel().UserViewModel().NickName()));
			json.SetNamedValue(L"from", from);
			json.SetNamedValue(L"message", message);
			json.SetNamedValue(L"position", JsonValue::CreateStringValue(L"right"));
			ListView_Messages().Items().Append(json);
		}
	}
	IAsyncAction ChatGroup::ListView_Messages_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		co_await LoadMessage();
	}
	void ChatGroup::UserControl_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		m_ChatViewModel_EventToken = AppViewModel().ChatViewModel().PropertyChanged({ this ,&ChatGroup::ChatViewModel_PropertyChanged });
		m_OnDispatch_EventToken = AppViewModel().TransportService().OnDispatch({ this, &ChatGroup::OnDispatch });
	}
	void ChatGroup::UserControl_Unloaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		AppViewModel().ChatViewModel().PropertyChanged(m_ChatViewModel_EventToken);
		AppViewModel().TransportService().OnDispatch(m_OnDispatch_EventToken);
	}
	IAsyncAction ChatGroup::LoadMessage()
	{
		auto groupId = AppViewModel().ChatViewModel().ChatInfo().GetNamedValue(L"groupId");
		JsonObject json;
		json.SetNamedValue(L"groupId", groupId);
		auto response = co_await TransportService().InvokeAsync(L"message", L"getGroupMessages", json);
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
	void ChatGroup::SendMessage_Invoked(winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator const& sender, winrt::Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const& args)
	{
		Button_SendMsg_Click(Button_SendMsg(), nullptr);
	}
	void ChatGroup::OnDispatch(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Data::Json::JsonObject const& e)
	{
		auto& args = e.GetNamedObject(L"args").GetObjectW();
		if (e.GetNamedString(L"name") == L"groupMessageReceive") {
			auto& from = args.GetNamedObject(L"from").GetObjectW();
			if (from.GetNamedNumber(L"groupId") == AppViewModel().ChatViewModel().ChatInfo().GetNamedNumber(L"groupId")) {
				args.SetNamedValue(L"position", JsonValue::CreateStringValue(L"left"));
				ListView_Messages().Items().Append(args);
			}
		}
	}
	HorizontalAlignment ChatGroup::BubblePositionConverter(Windows::Data::Json::JsonObject args)
	{
		auto position = args.GetNamedString(L"position");
		return position == L"right" ? HorizontalAlignment::Right : HorizontalAlignment::Left;
	}
	winrt::hstring ChatGroup::DisplayNameConverter(Windows::Data::Json::JsonObject args)
	{
		auto from = args.GetNamedObject(L"from").GetObjectW();
		auto nickName = from.GetNamedString(L"nickName");
		return nickName;
	}
	void ChatGroup::ChatViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e)
	{
		if (e.PropertyName() == L"ChatInfo") {
			LoadMessage();
		}
	}
}
