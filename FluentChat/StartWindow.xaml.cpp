#include "pch.h"
#include "StartWindow.xaml.h"
#include "MainWindow.xaml.h"
#include <microsoft.ui.xaml.window.h>
#include "Common.h"
#include "App.xaml.h"
#include "dwmapi.h"
#if __has_include("StartWindow.g.cpp")
#include "StartWindow.g.cpp"
#endif
#pragma comment(lib, "dwmapi.lib")
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

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
		Utilities::DisableResize(this->try_as<::IWindowNative>());
		auto [micaController, configurationSource] = Utilities::SetMicaBackdrop(*this);
		m_micaController = micaController;
		m_configurationSource = configurationSource;
		SetConfigurationSourceTheme();
		auto atc_token = this->Content().try_as<FrameworkElement>().ActualThemeChanged([&](FrameworkElement e, IInspectable i) {SetConfigurationSourceTheme(); });
		auto uvpc_token = AppViewModel().UserViewModel().PropertyChanged({ this, &StartWindow::UserViewModel_PropertyChanged });
		Closed([&](IInspectable s, WindowEventArgs e) {
			m_micaController = nullptr;
			m_configurationSource = nullptr;
			AppViewModel().UserViewModel().PropertyChanged(atc_token);
			AppViewModel().UserViewModel().PropertyChanged(uvpc_token);});
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

	void StartWindow::Window_Activated(IInspectable const& sender, WindowActivatedEventArgs const& args)
	{
		if (m_configurationSource != nullptr)
			m_configurationSource.IsInputActive(args.WindowActivationState() != WindowActivationState::Deactivated);
	}

	void StartWindow::SetConfigurationSourceTheme()
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


