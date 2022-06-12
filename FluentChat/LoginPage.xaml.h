#pragma once
#include "winrt/Windows.Storage.h"
#include "LoginPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct LoginPage : LoginPageT<LoginPage>
    {
        LoginPage();
        FluentChat::AppViewModel AppViewModel();
        void UserViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e);
        void LoginButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RememberPassword_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RememberPassword_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        Windows::Storage::IApplicationDataContainer m_settings;        
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
}
