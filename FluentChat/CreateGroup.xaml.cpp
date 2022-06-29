#include "pch.h"
#include "CreateGroup.xaml.h"
#include "App.xaml.h"
#if __has_include("CreateGroup.g.cpp")
#include "CreateGroup.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Data::Json;

namespace winrt::FluentChat::implementation
{
	CreateGroup::CreateGroup()
	{
		InitializeComponent();
	}
	FluentChat::AppViewModel CreateGroup::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}
	FluentChat::TransportService CreateGroup::TransportService()
	{
		return AppViewModel().TransportService();
	}
	IAsyncAction CreateGroup::CreateGroup_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		if (TextBox_GroupPassword().Text() == L"") {
			ContentDialog(L"建群失败", L"进群密码不能为空");
			return;
		}
		try {
			CreateGroup_Button().IsEnabled(false);
			JsonObject request;
			request.Insert(L"name", JsonValue::CreateStringValue(TextBox_GroupName().Text()));
			request.Insert(L"password", JsonValue::CreateStringValue(TextBox_GroupPassword().Text()));
			auto resp = co_await TransportService().InvokeAsync(L"group", L"create", request);
			auto str = resp.ToString();
			if (resp.GetNamedBoolean(L"success")) {
				co_await ContentDialog(L"建群成功", resp.GetNamedString(L"message"));
			}
			else {
				co_await ContentDialog(L"建群失败", resp.GetNamedString(L"message"));
			}
		}
		catch (winrt::hresult_error const& ex) {
			ContentDialog(L"建群失败", L"未知错误");
		}
		CreateGroup_Button().IsEnabled(true);
	}
	IAsyncAction CreateGroup::ContentDialog(hstring title, hstring content)
	{
		auto dialog = Controls::ContentDialog();
		dialog.XamlRoot(this->XamlRoot());
		dialog.Title(box_value(title));
		dialog.Content(box_value(content));
		dialog.CloseButtonText(L"确定");
		co_await dialog.ShowAsync();
	}
}
