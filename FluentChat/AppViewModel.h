#pragma once

#include "AppViewModel.g.h"
#include "TransportService.g.h"
#include "MainWindow.xaml.h"
#include "StartWindow.xaml.h"

using namespace winrt;

namespace winrt::FluentChat::implementation
{
	struct AppViewModel : AppViewModelT<AppViewModel>
	{
		AppViewModel();

		FluentChat::UserViewModel UserViewModel();

		FluentChat::TransportService TransportService();

		void OpenMainWindow();

		void OpenStartWindow();

		event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& value);
		void PropertyChanged(event_token const& token);

	private:
		void UserViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e);
		void OnDisconnect(winrt::Windows::Foundation::IInspectable const& sender, bool const& args);
		void RaisePropertyChanged(hstring propertyName);
		winrt::FluentChat::UserViewModel m_userViewModel;
		winrt::FluentChat::TransportService m_transportService;
		winrt::FluentChat::MainWindow m_mainWindow{ nullptr };
		winrt::FluentChat::StartWindow m_startWindow{ nullptr };
		event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}

namespace winrt::FluentChat::factory_implementation
{
	struct AppViewModel : AppViewModelT<AppViewModel, implementation::AppViewModel>
	{
	};
}
