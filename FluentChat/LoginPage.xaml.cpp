#include "pch.h"
#include "LoginPage.xaml.h"
#include "MainWindow.xaml.h"
#include "App.xaml.h"
#if __has_include("LoginPage.g.cpp")
#include "LoginPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
    LoginPage::LoginPage()
    {
        InitializeComponent();
    }

    FluentChat::AppViewModel LoginPage::AppViewModel()
    {
        return Application::Current().try_as<App>()->AppViewModel();
    }

    void LoginPage::LoginButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
    {
        AppViewModel().TransportService().TryConnect();
    }
}



