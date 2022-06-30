#include "pch.h"
#include "App.xaml.h"
#include "FriendPage.xaml.h"
#if __has_include("FriendPage.g.cpp")
#include "FriendPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Data::Json;
using namespace Windows::Foundation;
using namespace Controls;

namespace winrt::FluentChat::implementation
{
	FriendPage::FriendPage()
	{
		InitializeComponent();
	}
	FluentChat::AppViewModel FriendPage::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	FluentChat::TransportService FriendPage::TransportService()
	{
		return AppViewModel().TransportService();
	}

	IAsyncAction FriendPage::ListView_Friends_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto response = co_await TransportService().InvokeAsync(L"friend", L"listNormal", JsonObject());
		auto results = response.GetNamedArray(L"friends");
		ListView_Friends().Items().Clear();
		for (auto& item : results) ListView_Friends().Items().Append(item.GetObjectW());
	}

	void FriendPage::ListView_Friends_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		auto item = ListView_Friends().SelectedItem().try_as<JsonObject>();
		auto chat = AppViewModel().ChatViewModel();
		if (chat.ChatType() != 0 || chat.ChatInfo() == nullptr || item == nullptr || chat.ChatInfo().GetNamedNumber(L"friendId") != item.GetNamedNumber(L"friendId")) {
			chat.ChatType(0);
			chat.ChatView(0);
			chat.ChatInfo(item);
		}
	}

	IAsyncAction FriendPage::DeleleFriend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		auto item = sender.as<MenuFlyoutItem>().Tag().as<JsonObject>();
		auto dialog = Controls::ContentDialog();
		dialog.XamlRoot(this->XamlRoot());
		dialog.Title(box_value(L"删除好友"));
		dialog.Content(box_value(L"该操作也会将你从对方的好友列表中删除，而且无法恢复，是否删除？"));
		dialog.PrimaryButtonText(L"删除");
		dialog.CloseButtonText(L"取消");
		dialog.DefaultButton(ContentDialogButton::Close);
		auto result = co_await dialog.ShowAsync();
		if (result == ContentDialogResult::Primary)
		{

			try {
				co_await TransportService().InvokeAsync(L"friend", L"delete", item);
				co_await ListView_Friends_Loaded(ListView_Friends(), nullptr);
			}
			catch (winrt::hresult_error const& ex) {
				ContentDialog(L"删除失败", L"未知错误");
			}
		}
	}
	void FriendPage::EditAlias_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		ContentDialog(L"改不了", L"还没写这个功能");
	}
	winrt::Windows::Foundation::IAsyncAction FriendPage::ContentDialog(hstring title, hstring content)
	{
		auto dialog = Controls::ContentDialog();
		dialog.XamlRoot(this->XamlRoot());
		dialog.Title(box_value(title));
		dialog.Content(box_value(content));
		dialog.CloseButtonText(L"确定");
		co_await dialog.ShowAsync();
	}
	void FriendPage::Reload_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		ListView_Friends_Loaded(ListView_Friends(), nullptr);
	}
}















