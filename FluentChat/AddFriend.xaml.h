#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "AddFriend.g.h"

namespace winrt::FluentChat::implementation
{
    struct AddFriend : AddFriendT<AddFriend>
    {
        AddFriend();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct AddFriend : AddFriendT<AddFriend, implementation::AddFriend>
    {
    };
}
