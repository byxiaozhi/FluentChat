#include "pch.h"
#include "AppViewModel.h"
#if __has_include("AppViewModel.g.cpp")
#include "AppViewModel.g.cpp"
#endif

namespace winrt::FluentChat::implementation
{
    int32_t AppViewModel::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void AppViewModel::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }
}
