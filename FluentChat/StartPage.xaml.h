#pragma once

#include "StartPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct StartPage : StartPageT<StartPage>
    {
        StartPage();
        void navView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct StartPage : StartPageT<StartPage, implementation::StartPage>
    {
    };
}
