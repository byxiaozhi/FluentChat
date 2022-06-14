#include "pch.h"
#include "App.xaml.h"
#include "RecentPage.xaml.h"
#if __has_include("RecentPage.g.cpp")
#include "RecentPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
    RecentPage::RecentPage()
    {
        InitializeComponent();
    }
    FluentChat::AppViewModel RecentPage::AppViewModel()
    {
        return Application::Current().try_as<App>()->AppViewModel();
    }
    FluentChat::TransportService RecentPage::TransportService()
    {
        return AppViewModel().TransportService();
    }
}
