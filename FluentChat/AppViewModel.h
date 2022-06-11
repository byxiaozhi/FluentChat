#pragma once

#include "AppViewModel.g.h"

using namespace winrt;

namespace winrt::FluentChat::implementation
{
	struct AppViewModel : AppViewModelT<AppViewModel>
	{
		AppViewModel();

		FluentChat::UserViewModel UserViewModel();

		event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
		void PropertyChanged(event_token const& token);

	private:
		winrt::FluentChat::UserViewModel m_userViewModel{ nullptr };
		event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}

namespace winrt::FluentChat::factory_implementation
{
	struct AppViewModel : AppViewModelT<AppViewModel, implementation::AppViewModel>
	{
	};
}
