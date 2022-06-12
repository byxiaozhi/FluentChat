#include "pch.h"
#include "StartWindow.xaml.h"
#include "MainWindow.xaml.h"
#include <microsoft.ui.xaml.window.h>
#include "Common.h"
#include "App.xaml.h"
#if __has_include("StartWindow.g.cpp")
#include "StartWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
	StartWindow::StartWindow()
	{
		InitializeComponent();
		Title(L"Fluent Chat");
		Utilities::CenterWindow(this->try_as<::IWindowNative>(), 360, 480);
		auto uvpc_token = AppViewModel().UserViewModel().PropertyChanged({ this, &StartWindow::UserViewModel_PropertyChanged });
		Closed([&](IInspectable s, WindowEventArgs e) {AppViewModel().UserViewModel().PropertyChanged(uvpc_token); });
	}

	FluentChat::AppViewModel StartWindow::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	void StartWindow::UserViewModel_PropertyChanged(IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e)
	{
		if (e.PropertyName() == L"IsLogin" && AppViewModel().UserViewModel().IsLogin()) {
			make<MainWindow>().Activate();
			this->Close();
		}
	}
}