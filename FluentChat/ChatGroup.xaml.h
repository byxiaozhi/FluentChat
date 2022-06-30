#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "winrt/Microsoft.UI.Xaml.Input.h"
#include "ChatGroup.g.h"

using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
    struct ChatGroup : ChatGroupT<ChatGroup>
    {
        ChatGroup();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
        Windows::Foundation::IAsyncAction Button_SendMsg_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction ListView_Messages_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ChatViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e);
        void UserControl_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void UserControl_Unloaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction LoadMessage();
        void SendMessage_Invoked(winrt::Microsoft::UI::Xaml::Input::KeyboardAccelerator const& sender, winrt::Microsoft::UI::Xaml::Input::KeyboardAcceleratorInvokedEventArgs const& args);
        void OnDispatch(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::Data::Json::JsonObject const& e);
        static Microsoft::UI::Xaml::HorizontalAlignment BubblePositionConverter(Windows::Data::Json::JsonObject args);
        static winrt::hstring DisplayNameConverter(Windows::Data::Json::JsonObject args);
        IAsyncAction ContentDialog(hstring title, hstring content);
        winrt::event_token m_ChatViewModel_EventToken;
        winrt::event_token m_OnDispatch_EventToken;
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct ChatGroup : ChatGroupT<ChatGroup, implementation::ChatGroup>
    {
    };
}
