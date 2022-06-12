#include "pch.h"
#include "EventPage.xaml.h"
#if __has_include("EventPage.g.cpp")
#include "EventPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FluentChat::implementation
{
    EventPage::EventPage()
    {
        InitializeComponent();
    }

    int32_t EventPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void EventPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void EventPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
