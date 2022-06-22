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
        Windows::Foundation::IAsyncAction ItemsControl_Messages_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ChatViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e);
        void UserControl_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void UserControl_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::event_token m_ChatViewModel_EventToken;
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct ChatFriend : ChatFriendT<ChatFriend, implementation::ChatFriend>
    {
    };
}
