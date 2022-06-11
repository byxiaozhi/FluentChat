#pragma once

#include "StartWindow.g.h"

namespace winrt::FluentChat::implementation
{
    struct StartWindow : StartWindowT<StartWindow>
    {
        StartWindow();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct StartWindow : StartWindowT<StartWindow, implementation::StartWindow>
    {
    };
}
