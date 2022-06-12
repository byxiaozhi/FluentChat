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
		TransportService().OnDisconnect({ this,&AppViewModel::OnDisconnect });
	}


	winrt::FluentChat::UserViewModel AppViewModel::UserViewModel()
	{
		return m_userViewModel;
	}

	FluentChat::TransportService AppViewModel::TransportService()
	{
		return m_transportService;
	}

	void AppViewModel::OnDisconnect(winrt::Windows::Foundation::IInspectable const& sender, bool const& args)
	{
		if (UserViewModel().IsLogin()) {
			UserViewModel().IsLogin(false);
		}
	}

	void AppViewModel::RaisePropertyChanged(hstring propertyName)
	{
		m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ propertyName });
	}

	event_token AppViewModel::PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}

	void AppViewModel::PropertyChanged(event_token const& token)
	{
		m_propertyChanged.remove(token);
	}
}
