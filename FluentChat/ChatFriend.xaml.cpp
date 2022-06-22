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
        auto message = JsonValue::CreateStringValue(TextBox_Send().Text());
        auto friendId = AppViewModel().ChatViewModel().ChatInfo().GetNamedValue(L"friendId");
        JsonObject json;
        json.SetNamedValue(L"friendId", friendId);
        json.SetNamedValue(L"message", message);

        auto response = co_await TransportService().InvokeAsync(L"message", L"sendFriendMessage", json);
        if (response.GetNamedBoolean(L"success")) {
            TextBox_Send().Text(L"");
            JsonObject json;
            json.SetNamedValue(L"message", message);
            json.SetNamedValue(L"position", JsonValue::CreateStringValue(L"left"));
            ItemsControl_Messages().Items().Append(json);
            co_await Windows::System::Threading::ThreadPool::RunAsync([&](Windows::Foundation::IAsyncAction const& workItem) { Sleep(100); });
            ScrollViewer_Messages().ScrollToVerticalOffset(ScrollViewer_Messages().ScrollableHeight());
        }
    }
    IAsyncAction ChatFriend::ItemsControl_Messages_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto friendId = AppViewModel().ChatViewModel().ChatInfo().GetNamedValue(L"friendId");
        JsonObject json;
        json.SetNamedValue(L"friendId", friendId);
        auto response = co_await TransportService().InvokeAsync(L"message", L"getFriendMessages", json);
        auto messages = response.GetNamedArray(L"messages");
        ItemsControl_Messages().Items().Clear();
        for (auto& item : messages)
        {
            auto itemJson = item.GetObjectW();
            if (itemJson.GetNamedValue(L"from").GetObjectW().GetNamedString(L"email") == AppViewModel().UserViewModel().Email())
                json.SetNamedValue(L"position", JsonValue::CreateStringValue(L"left"));
            else
                json.SetNamedValue(L"position", JsonValue::CreateStringValue(L"right"));
            ItemsControl_Messages().Items().InsertAt(0, itemJson);
        }
    }
    void ChatFriend::UserControl_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
    {
        m_ChatViewModel_EventToken = AppViewModel().ChatViewModel().PropertyChanged({ this ,&ChatFriend::ChatViewModel_PropertyChanged });
    }
    void ChatFriend::UserControl_Unloaded(IInspectable const& sender, RoutedEventArgs const& e)
    {
        AppViewModel().ChatViewModel().PropertyChanged(m_ChatViewModel_EventToken);
    }
    void ChatFriend::ChatViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e)
    {
        if (e.PropertyName() == L"ChatInfo") {
            ChatFriend::ItemsControl_Messages_Loaded(*this, nullptr);
        }
    }
}








