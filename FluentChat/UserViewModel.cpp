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
			m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"NickName" });
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
			m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Email" });
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
			m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Password" });
		}
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
