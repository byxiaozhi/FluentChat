#include "pch.h"
#include "AddFriend.xaml.h"
#if __has_include("AddFriend.g.cpp")
#include "AddFriend.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
    AddFriend::AddFriend()
    {
        InitializeComponent();
    }

    void AddFriend::Search_Click(IInspectable const& sender, RoutedEventArgs const& e)
    {

    }
}