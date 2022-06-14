#include "pch.h"
#include "ChatFriend.xaml.h"
#if __has_include("ChatFriend.g.cpp")
#include "ChatFriend.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
    ChatFriend::ChatFriend()
    {
        InitializeComponent();
    }
}
