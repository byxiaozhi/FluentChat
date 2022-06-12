﻿#include "pch.h"
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
using namespace Windows::Data::Json;

namespace winrt::FluentChat::implementation
{
	LoginPage::LoginPage()
	{
		InitializeComponent();
		m_settings = Windows::Storage::ApplicationData::Current().LocalSettings();
		AppViewModel().UserViewModel().Email(m_settings.Values().Lookup(L"Email").try_as<hstring>().value_or(L""));
		AppViewModel().UserViewModel().Password(m_settings.Values().Lookup(L"Password").try_as<hstring>().value_or(L""));
		cb_RememberPassword().IsChecked(m_settings.Values().HasKey(L"Password"));
		auto uvpc_token = AppViewModel().UserViewModel().PropertyChanged({ this, &LoginPage::UserViewModel_PropertyChanged });
		this->Unloaded([&](IInspectable s, RoutedEventArgs e) { AppViewModel().UserViewModel().PropertyChanged(uvpc_token); });
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

	FluentChat::TransportService LoginPage::TransportService()
	{
		return AppViewModel().TransportService();
	}

	IAsyncAction LoginPage::Login_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try {
			Button_Login().IsEnabled(false);
			JsonObject request;
			request.Insert(L"email", JsonValue::CreateStringValue(TextBox_Email().Text()));
			request.Insert(L"password", JsonValue::CreateStringValue(PasswordBox_Password().Password()));
			auto connected = co_await TransportService().TryConnect();
			if (!connected) {
				Button_Login().IsEnabled(true);
				co_await ContentDialog(L"登录失败", L"网络发生错误");
				co_return;
			}
			auto resp = co_await TransportService().InvokeAsync(L"user", L"login", request);
			auto str = resp.ToString();
			if (resp.GetNamedBoolean(L"success")) {
				AppViewModel().UserViewModel().IsLogin(true);
			}
			else {
				co_await ContentDialog(L"登录失败", resp.GetNamedString(L"message"));
			}
		}
		catch (winrt::hresult_error const& ex) {
			ContentDialog(L"登录失败", L"未知错误");
		}
		Button_Login().IsEnabled(true);
	}

	IAsyncAction LoginPage::ContentDialog(hstring title, hstring content)
	{
		auto dialog = Controls::ContentDialog();
		dialog.XamlRoot(this->XamlRoot());
		dialog.Title(box_value(title));
		dialog.Content(box_value(content));
		dialog.CloseButtonText(L"确定");
		co_await dialog.ShowAsync();
	}
}
