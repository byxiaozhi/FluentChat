#pragma once

#include "FriendPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct FriendPage : FriendPageT<FriendPage>
    {
        FriendPage();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
        winrt::Windows::Foundation::IAsyncAction ListView_Friends_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ListView_Friends_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction DeleleFriend_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction ContentDialog(hstring title, hstring content);
        void Reload_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct FriendPage : FriendPageT<FriendPage, implementation::FriendPage>
    {
    };
}
