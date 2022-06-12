#pragma once

#include "StartPage.g.h"

using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace winrt::FluentChat::implementation
{
    struct StartPage : StartPageT<StartPage>
    {
        StartPage();
        FluentChat::AppViewModel AppViewModel();
        void navView_SelectionChanged(NavigationView const& sender, NavigationViewSelectionChangedEventArgs const& args);
        ::NavigationView NavigationView();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct StartPage : StartPageT<StartPage, implementation::StartPage>
    {
    };
}
