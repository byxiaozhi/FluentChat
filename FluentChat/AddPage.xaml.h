#pragma once

#include "AddPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct AddPage : AddPageT<AddPage>
    {
        AddPage();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct AddPage : AddPageT<AddPage, implementation::AddPage>
    {
    };
}
