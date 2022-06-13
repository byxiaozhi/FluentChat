#include "pch.h"
#include "EventPage.xaml.h"
#if __has_include("EventPage.g.cpp")
#include "EventPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;


namespace winrt::FluentChat::implementation
{
    EventPage::EventPage()
    {
        InitializeComponent();
    }
}
