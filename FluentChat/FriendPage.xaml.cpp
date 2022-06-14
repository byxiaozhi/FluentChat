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
		if (chat.ChatType() != 0 || chat.ChatInfo() == nullptr || chat.ChatInfo().GetNamedNumber(L"friendId") != item.GetNamedNumber(L"friendId")) {
			chat.ChatType(0);
			chat.ChatInfo(item);
		}
	}
}






