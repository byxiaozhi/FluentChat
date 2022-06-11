#include "pch.h"
#include "GroupPage.xaml.h"
#if __has_include("GroupPage.g.cpp")
#include "GroupPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
    GroupPage::GroupPage()
    {
        InitializeComponent();
    }
}
