#pragma once

#include "GroupPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct GroupPage : GroupPageT<GroupPage>
    {
        GroupPage();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct GroupPage : GroupPageT<GroupPage, implementation::GroupPage>
    {
    };
}
