#include "pch.h"
#include "ChatPage.xaml.h"
#include "App.xaml.h"
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
    FluentChat::AppViewModel ChatPage::AppViewModel()
    {
        return Application::Current().try_as<App>()->AppViewModel();
    }
}
