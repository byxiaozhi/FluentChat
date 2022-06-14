#pragma once

#include "RecentPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct RecentPage : RecentPageT<RecentPage>
    {
        RecentPage();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct RecentPage : RecentPageT<RecentPage, implementation::RecentPage>
    {
    };
}
