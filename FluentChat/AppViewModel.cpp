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
		UserViewModel().PropertyChanged({ this, &AppViewModel::UserViewModel_PropertyChanged });
	}


	winrt::FluentChat::UserViewModel AppViewModel::UserViewModel()
	{
		return m_userViewModel;
	}

	FluentChat::TransportService AppViewModel::TransportService()
	{
		return m_transportService;
	}

	void AppViewModel::OpenMainWindow()
	{
		m_mainWindow = make<MainWindow>();
		m_mainWindow.Activate();
		if (m_startWindow != nullptr) {
			m_startWindow.Close();
			m_startWindow = nullptr;
		}
	}

	void AppViewModel::OpenStartWindow()
	{
		m_startWindow = make<StartWindow>();
		m_startWindow.Activate();
		if (m_mainWindow != nullptr) {
			m_mainWindow.Close();
			m_mainWindow = nullptr;
		}
	}

	void AppViewModel::UserViewModel_PropertyChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e)
	{
		if (e.PropertyName() == L"IsLogin") {
			if (UserViewModel().IsLogin()) OpenMainWindow();
			else OpenStartWindow();
		}
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
