#include "pch.h"
#include "LoginWindow.xaml.h"
#include <microsoft.ui.xaml.window.h>
#include "Common.h"
#if __has_include("LoginWindow.g.cpp")
#include "LoginWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
	LoginWindow::LoginWindow()
	{
		InitializeComponent();
		Title(L"Fluent Chat");
		Utilities::CenterWindow(this->try_as<::IWindowNative>(), 360, 480);
	}
}