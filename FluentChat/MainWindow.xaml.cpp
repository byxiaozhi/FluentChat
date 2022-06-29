#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include "StartWindow.xaml.h"
#include <microsoft.ui.xaml.window.h>
#include "Common.h"
#include "App.xaml.h"
#include "dwmapi.h"
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <wil/cppwinrt.h>
#include <wil/cppwinrt_helpers.h>
#pragma comment(lib, "dwmapi.lib")

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;
using namespace Windows::UI::ViewManagement;

namespace winrt::FluentChat::implementation
{
	MainWindow::MainWindow()
	{
		InitializeComponent();
		Title(L"Fluent Chat");
		Utilities::CenterWindow(this->try_as<::IWindowNative>(), 1000, 600);
		auto [micaController, configurationSource] = Utilities::SetMicaBackdrop(*this);
		m_micaController = micaController;
		m_configurationSource = configurationSource;
		ColorValuesChanged(m_uiSettings, nullptr);
		m_uiSettings.ColorValuesChanged({ this, &MainWindow::ColorValuesChanged });
	}

	FluentChat::AppViewModel MainWindow::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	void MainWindow::Window_Activated(IInspectable const& sender, WindowActivatedEventArgs const& args)
	{
		if (m_configurationSource != nullptr)
			m_configurationSource.IsInputActive(args.WindowActivationState() != WindowActivationState::Deactivated);
	}

	void MainWindow::Window_Closed(IInspectable const& sender, WindowEventArgs const& args)
	{
		m_micaController = nullptr;
		m_configurationSource = nullptr;
		m_uiSettings = nullptr;
		AppViewModel().ChatViewModel().ChatView(0);
		AppViewModel().ChatViewModel().ChatType(-1);
	}

	IAsyncAction MainWindow::ColorValuesChanged(Windows::UI::ViewManagement::UISettings s, IInspectable e)
	{
		if (m_configurationSource == nullptr)
			co_return;
		co_await wil::resume_foreground(DispatcherQueue());
		int darkModeValue = Application::Current().RequestedTheme() == ApplicationTheme::Dark ? 1 : 0;
		auto hWnd = Utilities::GetWindowHandle(this->try_as<::IWindowNative>());
		DwmSetWindowAttribute(hWnd, 20, (LPCVOID)&darkModeValue, sizeof(int));
	}
}