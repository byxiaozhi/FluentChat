#pragma once

#include "FriendPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct FriendPage : FriendPageT<FriendPage>
    {
        FriendPage();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct FriendPage : FriendPageT<FriendPage, implementation::FriendPage>
    {
    };
}
