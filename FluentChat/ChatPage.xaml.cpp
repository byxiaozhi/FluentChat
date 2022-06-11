#include "pch.h"
#include "ChatPage.xaml.h"
#if __has_include("ChatPage.g.cpp")
#include "ChatPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
    ChatPage::ChatPage()
    {
        InitializeComponent();
    }
}
