#include "pch.h"
#include "CreateGroup.xaml.h"
#include "App.xaml.h"
#if __has_include("CreateGroup.g.cpp")
#include "CreateGroup.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Data::Json;

namespace winrt::FluentChat::implementation
{
    CreateGroup::CreateGroup()
    {
        InitializeComponent();
    }
    FluentChat::AppViewModel CreateGroup::AppViewModel()
    {
        return Application::Current().try_as<App>()->AppViewModel();
    }
    FluentChat::TransportService CreateGroup::TransportService()
    {
        return AppViewModel().TransportService();
    }
}
