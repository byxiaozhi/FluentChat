#pragma once
#include "pch.h"
#include "SignupPage.g.h"

using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
    struct SignupPage : SignupPageT<SignupPage>
    {
        SignupPage();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
        IAsyncAction Signup_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        IAsyncAction ContentDialog(hstring title, hstring content);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct SignupPage : SignupPageT<SignupPage, implementation::SignupPage>
    {
    };
}
