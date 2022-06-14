#pragma once

#include "GroupPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct GroupPage : GroupPageT<GroupPage>
    {
        GroupPage();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct GroupPage : GroupPageT<GroupPage, implementation::GroupPage>
    {
    };
}
