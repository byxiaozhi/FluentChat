#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "ChatFriend.g.h"

namespace winrt::FluentChat::implementation
{
    struct ChatFriend : ChatFriendT<ChatFriend>
    {
        ChatFriend();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
        Windows::Foundation::IAsyncAction Button_SendMsg_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct ChatFriend : ChatFriendT<ChatFriend, implementation::ChatFriend>
    {
    };
}
