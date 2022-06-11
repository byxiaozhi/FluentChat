#include "pch.h"
#include "SignupPage.xaml.h"
#if __has_include("SignupPage.g.cpp")
#include "SignupPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
    SignupPage::SignupPage()
    {
        InitializeComponent();
    }
}
