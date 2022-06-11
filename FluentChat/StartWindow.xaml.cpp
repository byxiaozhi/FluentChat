#include "pch.h"
#include "StartWindow.xaml.h"
#include <microsoft.ui.xaml.window.h>
#include "Common.h"
#if __has_include("StartWindow.g.cpp")
#include "StartWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
	StartWindow::StartWindow()
	{
		InitializeComponent();
		Title(L"Fluent Chat");
		Utilities::CenterWindow(this->try_as<::IWindowNative>(), 360, 480);
	}
}