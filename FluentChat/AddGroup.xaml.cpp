#include "pch.h"
#include "AddGroup.xaml.h"
#if __has_include("AddGroup.g.cpp")
#include "AddGroup.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
    AddGroup::AddGroup()
    {
        InitializeComponent();
    }
}
