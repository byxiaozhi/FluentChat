#pragma once
#include "pch.h"
#include "winrt/Windows.Storage.h"
#include "LoginPage.g.h"

using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
    struct LoginPage : LoginPageT<LoginPage>
    {
        LoginPage();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
        void UserViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e);
        IAsyncAction Login_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RememberPassword_Checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RememberPassword_Unchecked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        Windows::Storage::IApplicationDataContainer m_settings;   

    private:
        IAsyncAction ContentDialog(hstring title, hstring content);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
}
