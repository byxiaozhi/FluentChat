#include "pch.h"
#include "MainWindow.xaml.h"
#include "StartWindow.xaml.h"
#include <microsoft.ui.xaml.window.h>
#include "Common.h"
#include "App.xaml.h"
#include "dwmapi.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#pragma comment(lib, "dwmapi.lib")
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;

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
		SetConfigurationSourceTheme();
		auto atc_token = this->Content().try_as<FrameworkElement>().ActualThemeChanged([&](FrameworkElement e, IInspectable i) {SetConfigurationSourceTheme(); });
		Closed([&](IInspectable s, WindowEventArgs e) {
			m_micaController = nullptr;
			m_configurationSource = nullptr;
			AppViewModel().UserViewModel().PropertyChanged(atc_token);});
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

	void MainWindow::SetConfigurationSourceTheme()
	{
		if (m_configurationSource == nullptr)
			return;
		int darkModeValue = 0;
		switch (this->Content().try_as<FrameworkElement>().ActualTheme())
		{
		case ElementTheme::Dark:
			m_configurationSource.Theme(Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Dark);
			darkModeValue = 1;
			break;
		case ElementTheme::Light:
			m_configurationSource.Theme(Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Light);
			darkModeValue = 0;
			break;
		case ElementTheme::Default:
			m_configurationSource.Theme(Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme::Default);
			darkModeValue = Application::Current().RequestedTheme() == ApplicationTheme::Dark ? 1 : 0;
			break;
		}
		auto hWnd = Utilities::GetWindowHandle(this->try_as<::IWindowNative>());
		DwmSetWindowAttribute(hWnd, 20, (LPCVOID)&darkModeValue, sizeof(int));
	}
}

