#pragma once

#include "LoginPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct LoginPage : LoginPageT<LoginPage>
    {
        LoginPage();

        FluentChat::AppViewModel AppViewModel();

        void LoginButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        FluentChat::AppViewModel m_appViewModel;
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
}
