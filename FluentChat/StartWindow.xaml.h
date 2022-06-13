#pragma once
#include "pch.h"
#include "StartWindow.g.h"
#include "MicaBackdrop.h"

namespace winrt::FluentChat::implementation
{
	struct StartWindow : StartWindowT<StartWindow>
	{
		StartWindow();
		FluentChat::AppViewModel AppViewModel();
		void Window_Activated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args);
		void Window_Closed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowEventArgs const& args);
		winrt::Windows::Foundation::IAsyncAction ColorValuesChanged(Windows::UI::ViewManagement::UISettings s, IInspectable e);

	private:
		Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration m_configurationSource{ nullptr };	
		Microsoft::UI::Composition::SystemBackdrops::MicaController m_micaController{ nullptr };
		Windows::UI::ViewManagement::UISettings m_uiSettings;
	};
}

namespace winrt::FluentChat::factory_implementation
{
	struct StartWindow : StartWindowT<StartWindow, implementation::StartWindow>
	{
	};
}
