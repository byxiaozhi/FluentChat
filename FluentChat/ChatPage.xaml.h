#pragma once

#include "ChatPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct ChatPage : ChatPageT<ChatPage>
    {
        ChatPage();
        FluentChat::AppViewModel AppViewModel();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct ChatPage : ChatPageT<ChatPage, implementation::ChatPage>
    {
    };
}
