#include "pch.h"
#include "MainWindow.xaml.h"
#include "StartWindow.xaml.h"
#include <microsoft.ui.xaml.window.h>
#include "Common.h"
#include "App.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        Title(L"Fluent Chat");
        Utilities::CenterWindow(this->try_as<::IWindowNative>(), 1000, 600);
        auto uvpc_token = AppViewModel().UserViewModel().PropertyChanged({ this, &MainWindow::UserViewModel_PropertyChanged });
        Closed([&](IInspectable s, WindowEventArgs e) {AppViewModel().UserViewModel().PropertyChanged(uvpc_token); });
    }

    FluentChat::AppViewModel MainWindow::AppViewModel()
    {
        return Application::Current().try_as<App>()->AppViewModel();
    }

    void MainWindow::UserViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e)
    {
        if (e.PropertyName() == L"IsLogin" && !AppViewModel().UserViewModel().IsLogin()) {
            make<StartWindow>().Activate();
            this->Close();
        }
    }
}
