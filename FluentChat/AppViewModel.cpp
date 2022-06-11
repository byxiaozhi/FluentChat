#include "pch.h"
#include "AppViewModel.h"
#include "UserViewModel.h"
#include "TransportService.h"
#if __has_include("AppViewModel.g.cpp")
#include "AppViewModel.g.cpp"
#endif

using namespace winrt;

namespace winrt::FluentChat::implementation
{
	AppViewModel::AppViewModel() {
		m_userViewModel = make<winrt::FluentChat::implementation::UserViewModel>();
		m_transportService = make<winrt::FluentChat::implementation::TransportService>();
	}

	winrt::FluentChat::UserViewModel AppViewModel::UserViewModel()
	{
		return m_userViewModel;
	}

	FluentChat::TransportService AppViewModel::TransportService()
	{
		return m_transportService;
	}

	event_token AppViewModel::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}

	void AppViewModel::PropertyChanged(event_token const& token)
	{
		m_propertyChanged.remove(token);
	}
}
