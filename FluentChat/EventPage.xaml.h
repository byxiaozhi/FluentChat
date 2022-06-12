#pragma once

#include "EventPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct EventPage : EventPageT<EventPage>
    {
        EventPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct EventPage : EventPageT<EventPage, implementation::EventPage>
    {
    };
}
