#pragma once

#include "MainPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
        void sideNavView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
