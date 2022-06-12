#pragma once
#include "pch.h"
#include "StartWindow.g.h"

namespace winrt::FluentChat::implementation
{
    struct StartWindow : StartWindowT<StartWindow>
    {
        StartWindow();
        FluentChat::AppViewModel AppViewModel();
        void UserViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct StartWindow : StartWindowT<StartWindow, implementation::StartWindow>
    {
    };
}
