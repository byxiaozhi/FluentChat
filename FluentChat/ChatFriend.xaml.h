#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "ChatFriend.g.h"

namespace winrt::FluentChat::implementation
{
    struct ChatFriend : ChatFriendT<ChatFriend>
    {
        ChatFriend();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct ChatFriend : ChatFriendT<ChatFriend, implementation::ChatFriend>
    {
    };
}
