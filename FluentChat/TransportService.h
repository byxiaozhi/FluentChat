#pragma once
#include "TransportService.g.h"

namespace winrt::FluentChat::implementation
{
    struct TransportService : TransportServiceT<TransportService>
    {
        TransportService() = default;

    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct TransportService : TransportServiceT<TransportService, implementation::TransportService>
    {
    };
}
