#include "pch.h"
#include "ChatFriend.xaml.h"
#include "App.xaml.h"
#if __has_include("ChatFriend.g.cpp")
#include "ChatFriend.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Data::Json;

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
        auto friendId = AppViewModel().ChatViewModel().ChatInfo().GetNamedValue(L"friendId");
        JsonObject json;
        json.SetNamedValue(L"friendId", friendId);
        json.SetNamedValue(L"message", JsonValue::CreateStringValue(TextBox_Send().Text()));

        JsonObject response = co_await TransportService().InvokeAsync(L"message", L"sendFriendMessage", json);
        if (response.GetNamedBoolean(L"success")) {
            TextBox_Send().Text(L"");
        }
    }
}



