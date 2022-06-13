#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "AddGroup.g.h"

namespace winrt::FluentChat::implementation
{
    struct AddGroup : AddGroupT<AddGroup>
    {
        AddGroup();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct AddGroup : AddGroupT<AddGroup, implementation::AddGroup>
    {
    };
}
