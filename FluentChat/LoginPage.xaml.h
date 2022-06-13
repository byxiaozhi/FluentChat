#pragma once
#include "pch.h"
#include "winrt/Windows.Storage.h"
#include "LoginPage.g.h"
#include "StartPage.xaml.h"

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
        virtual void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs e);
        void GotoSignupClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        Windows::Storage::IApplicationDataContainer m_settings;
        IAsyncAction ContentDialog(hstring title, hstring content);
        weak_ref<StartPage> m_startPage{ nullptr };
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct LoginPage : LoginPageT<LoginPage, implementation::LoginPage>
    {
    };
}
