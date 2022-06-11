#include "pch.h"
#include "FriendPage.xaml.h"
#if __has_include("FriendPage.g.cpp")
#include "FriendPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
    FriendPage::FriendPage()
    {
        InitializeComponent();
    }
}
