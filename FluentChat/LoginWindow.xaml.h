#pragma once

#include "LoginWindow.g.h"

namespace winrt::FluentChat::implementation
{
    struct LoginWindow : LoginWindowT<LoginWindow>
    {
        LoginWindow();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct LoginWindow : LoginWindowT<LoginWindow, implementation::LoginWindow>
    {
    };
}
