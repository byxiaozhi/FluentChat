#pragma once

#include "SignupPage.g.h"

namespace winrt::FluentChat::implementation
{
    struct SignupPage : SignupPageT<SignupPage>
    {
        SignupPage();
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct SignupPage : SignupPageT<SignupPage, implementation::SignupPage>
    {
    };
}
