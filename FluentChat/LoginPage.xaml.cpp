#include "pch.h"
#include "LoginPage.xaml.h"
#include "MainWindow.xaml.h"
#include "winrt/Windows.Storage.h"
#include "App.xaml.h"
#if __has_include("LoginPage.g.cpp")
#include "LoginPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;

namespace winrt::FluentChat::implementation
{
	LoginPage::LoginPage()
	{
		InitializeComponent();
		m_settings = Windows::Storage::ApplicationData::Current().LocalSettings();
		AppViewModel().UserViewModel().Email(m_settings.Values().Lookup(L"Email").try_as<hstring>().value_or(L""));
		AppViewModel().UserViewModel().Password(m_settings.Values().Lookup(L"Password").try_as<hstring>().value_or(L""));
		cb_RememberPassword().IsChecked(m_settings.Values().HasKey(L"Password"));
		auto m_uvpc_token = AppViewModel().UserViewModel().PropertyChanged({ this, &LoginPage::UserViewModel_PropertyChanged });
		this->Unloaded([&](IInspectable s, RoutedEventArgs e) { AppViewModel().UserViewModel().PropertyChanged(m_uvpc_token); });
	}

	void LoginPage::UserViewModel_PropertyChanged(IInspectable const& sender, PropertyChangedEventArgs const& e)
	{
		if (e.PropertyName() == L"Email") {
			m_settings.Values().Insert(L"Email", winrt::box_value(AppViewModel().UserViewModel().Email()));
		}
		if (e.PropertyName() == L"Password" && cb_RememberPassword().IsChecked().GetBoolean()) {
			m_settings.Values().Insert(L"Password", winrt::box_value(AppViewModel().UserViewModel().Password()));
		}
	}

	void LoginPage::RememberPassword_Checked(IInspectable const& sender, RoutedEventArgs const& e)
	{
		m_settings.Values().Insert(L"Password", winrt::box_value(AppViewModel().UserViewModel().Password()));
	}

	void LoginPage::RememberPassword_Unchecked(IInspectable const& sender, RoutedEventArgs const& e)
	{
		m_settings.Values().Remove(L"Password");
	}

	FluentChat::AppViewModel LoginPage::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	void LoginPage::LoginButton_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		AppViewModel().TransportService().TryConnect();
	}
}
