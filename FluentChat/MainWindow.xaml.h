#pragma once
#include "pch.h"
#include "MainWindow.g.h"

namespace winrt::FluentChat::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
        FluentChat::AppViewModel AppViewModel();
        void UserViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
