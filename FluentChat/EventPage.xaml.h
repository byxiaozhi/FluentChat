#pragma once

#include "EventPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct EventPage : EventPageT<EventPage>
    {
        EventPage();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct EventPage : EventPageT<EventPage, implementation::EventPage>
    {
    };
}
