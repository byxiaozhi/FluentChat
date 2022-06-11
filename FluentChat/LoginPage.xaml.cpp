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
        m_appViewModel = Microsoft::UI::Xaml::Application::Current().try_as<winrt::FluentChat::implementation::App>()->AppViewModel();
        InitializeComponent();
    }

    FluentChat::AppViewModel LoginPage::AppViewModel()
    {
        return m_appViewModel;
    }

    void LoginPage::LoginButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
    {
        auto window = make<MainWindow>();
        window.Activate();
    }
}



