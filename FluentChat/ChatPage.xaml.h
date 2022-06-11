#pragma once

#include "ChatPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct ChatPage : ChatPageT<ChatPage>
    {
        ChatPage();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct ChatPage : ChatPageT<ChatPage, implementation::ChatPage>
    {
    };
}
