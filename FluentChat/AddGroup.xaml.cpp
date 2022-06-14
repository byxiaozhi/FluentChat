#include "pch.h"
#include "AddGroup.xaml.h"
#include "App.xaml.h"
#if __has_include("AddGroup.g.cpp")
#include "AddGroup.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Data::Json;

namespace winrt::FluentChat::implementation
{
    AddGroup::AddGroup()
    {
        InitializeComponent();
    }

    FluentChat::AppViewModel AddGroup::AppViewModel()
    {
        return Application::Current().try_as<App>()->AppViewModel();
    }

    FluentChat::TransportService AddGroup::TransportService()
    {
        return AppViewModel().TransportService();
    }

    void AddGroup::Search_Click(IInspectable const& sender, RoutedEventArgs const& e)
    {

    }
}



