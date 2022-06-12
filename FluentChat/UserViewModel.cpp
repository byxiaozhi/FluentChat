#include "pch.h"
#include "UserViewModel.h"
#if __has_include("UserViewModel.g.cpp")
#include "UserViewModel.g.cpp"
#endif

using namespace winrt;

namespace winrt::FluentChat::implementation
{
	hstring UserViewModel::NickName()
	{
		return m_nickName;
	}

	void UserViewModel::NickName(hstring const& value)
	{
		if (m_nickName != value)
		{
			m_nickName = value;
			RaisePropertyChanged(L"NickName");
		}
	}

	hstring UserViewModel::Email()
	{
		return m_email;
	}

	void UserViewModel::Email(hstring const& value)
	{
		if (m_email != value)
		{
			m_email = value;
			RaisePropertyChanged(L"Email");
		}
	}

	hstring UserViewModel::Password()
	{
		return m_password;
	}

	void UserViewModel::Password(hstring const& value)
	{
		if (m_password != value)
		{
			m_password = value;
			RaisePropertyChanged(L"Password");
		}
	}

	void UserViewModel::RaisePropertyChanged(hstring propertyName)
	{
		m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ propertyName });
	}

	event_token UserViewModel::PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}

	void UserViewModel::PropertyChanged(event_token const& token)
	{
		m_propertyChanged.remove(token);
	}
}
