#include "pch.h"
#include "SettingsPage.xaml.h"
#include "App.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::Data::Json;

namespace winrt::FluentChat::implementation
{

	SettingsPage::SettingsPage()
	{
		InitializeComponent();
	}

	FluentChat::AppViewModel SettingsPage::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	FluentChat::TransportService SettingsPage::TransportService()
	{
		return AppViewModel().TransportService();
	}

	void SettingsPage::Logout_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		AppViewModel().UserViewModel().IsLogin(false);
	}

	IAsyncAction SettingsPage::EditNickname_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.as<Controls::Button>();
		auto jsonObject = button.Tag().as<JsonObject>();
		auto nickname = VisualTreeHelper::GetParent(button).as<StackPanel>().Children().GetAt(0).as<TextBox>().Text();
		try {
			button.IsEnabled(false);
			JsonObject request;
			request.Insert(L"nickname", JsonValue::CreateStringValue(nickname));
			auto resp = co_await TransportService().InvokeAsync(L"user", L"editNickname", request);
			auto str = resp.ToString();
			if (resp.GetNamedBoolean(L"success")) {
				co_await ContentDialog(L"修改昵称成功", resp.GetNamedString(L"message"));
				EditNickname_Flyout().Hide();
				AppViewModel().UserViewModel().NickName(nickname);
			}
			else {
				co_await ContentDialog(L"修改昵称失败", resp.GetNamedString(L"message"));
			}
		}
		catch (winrt::hresult_error const& ex) {
			ContentDialog(L"修改昵称失败", L"未知错误");
		}
		button.IsEnabled(true);
	}

	void SettingsPage::RaisePropertyChanged(hstring propertyName)
	{
		m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ propertyName });
	}

	event_token SettingsPage::PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
	{
		return m_propertyChanged.add(handler);
	}

	void SettingsPage::PropertyChanged(event_token const& token)
	{
		m_propertyChanged.remove(token);
	}
	winrt::Windows::Foundation::IAsyncAction SettingsPage::ContentDialog(hstring title, hstring content)
	{
		auto dialog = Controls::ContentDialog();
		dialog.XamlRoot(this->XamlRoot());
		dialog.Title(box_value(title));
		dialog.Content(box_value(content));
		dialog.CloseButtonText(L"确定");
		co_await dialog.ShowAsync();
	}
}
