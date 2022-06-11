#include "pch.h"
#include "LoginPage.xaml.h"
#include "MainWindow.xaml.h"
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

    void LoginPage::LoginButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
    {
        auto window = make<MainWindow>();
        window.Activate();
    }
}



