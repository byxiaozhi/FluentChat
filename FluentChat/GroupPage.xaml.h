#pragma once

#include "GroupPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct GroupPage : GroupPageT<GroupPage>
    {
        GroupPage();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
        winrt::Windows::Foundation::IAsyncAction ListView_Groups_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ListView_Groups_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void Reload_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct GroupPage : GroupPageT<GroupPage, implementation::GroupPage>
    {
    };
}
