#include "pch.h"
#include "ChatGroup.xaml.h"
#if __has_include("ChatGroup.g.cpp")
#include "ChatGroup.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::FluentChat::implementation
{
    ChatGroup::ChatGroup()
    {
        InitializeComponent();
    }

    int32_t ChatGroup::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ChatGroup::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ChatGroup::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
