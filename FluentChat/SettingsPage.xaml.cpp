#include "pch.h"
#include "SettingsPage.xaml.h"
#include "App.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
    SettingsPage::SettingsPage()
    {
        InitializeComponent();
    }

    FluentChat::AppViewModel SettingsPage::AppViewModel()
    {
        return Application::Current().try_as<App>()->AppViewModel();
    }

    void SettingsPage::Logout_Click(IInspectable const& sender, RoutedEventArgs const& e)
    {
        AppViewModel().UserViewModel().IsLogin(false);
    }
}

