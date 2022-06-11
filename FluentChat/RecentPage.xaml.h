#pragma once

#include "RecentPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct RecentPage : RecentPageT<RecentPage>
    {
        RecentPage();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct RecentPage : RecentPageT<RecentPage, implementation::RecentPage>
    {
    };
}
