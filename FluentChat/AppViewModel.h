#pragma once

#include "AppViewModel.g.h"
#include "TransportService.g.h"

using namespace winrt;

namespace winrt::FluentChat::implementation
{
	struct AppViewModel : AppViewModelT<AppViewModel>
	{
		AppViewModel();

		FluentChat::UserViewModel UserViewModel();

		FluentChat::TransportService TransportService();

		event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& value);
		void PropertyChanged(event_token const& token);

	private:
		void OnDisconnect(winrt::Windows::Foundation::IInspectable const& sender, bool const& args);
		void RaisePropertyChanged(hstring propertyName);
		winrt::FluentChat::UserViewModel m_userViewModel;
		winrt::FluentChat::TransportService m_transportService;
		event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}

namespace winrt::FluentChat::factory_implementation
{
	struct AppViewModel : AppViewModelT<AppViewModel, implementation::AppViewModel>
	{
	};
}
