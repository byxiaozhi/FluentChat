#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "CreateGroup.g.h"

namespace winrt::FluentChat::implementation
{
    struct CreateGroup : CreateGroupT<CreateGroup>
    {
        CreateGroup();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct CreateGroup : CreateGroupT<CreateGroup, implementation::CreateGroup>
    {
    };
}
