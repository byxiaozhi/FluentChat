#pragma once

#include "AppViewModel.g.h"

namespace winrt::FluentChat::implementation
{
    struct AppViewModel : AppViewModelT<AppViewModel>
    {
        AppViewModel() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct AppViewModel : AppViewModelT<AppViewModel, implementation::AppViewModel>
    {
    };
}
