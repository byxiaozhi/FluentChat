#include "pch.h"
#include "AddGroup.xaml.h"
#include "App.xaml.h"
#if __has_include("AddGroup.g.cpp")
#include "AddGroup.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Media;
using namespace Windows::Foundation;
using namespace Windows::Data::Json;

namespace winrt::FluentChat::implementation
{
	AddGroup::AddGroup()
	{
		InitializeComponent();
	}

	FluentChat::AppViewModel AddGroup::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	FluentChat::TransportService AddGroup::TransportService()
	{
		return AppViewModel().TransportService();
	}

	IAsyncAction AddGroup::Search_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		if (TextBox_Search().Text().empty()) co_return;
		JsonObject request;
		request.SetNamedValue(L"value", JsonValue::CreateStringValue(TextBox_Search().Text()));
		auto response = co_await TransportService().InvokeAsync(L"group", L"search", request);
		auto results = response.GetNamedArray(L"results");
		ItemsControl_Search().Items().Clear();
		for (auto& item : results) ItemsControl_Search().Items().Append(item.GetObjectW());
		Panel_Search().Visibility(Visibility::Visible);
	}

	winrt::hstring AddGroup::GetGroupId(winrt::Windows::Data::Json::JsonObject jsonObject)
	{
		return winrt::to_hstring(jsonObject.GetNamedNumber(L"groupId"));
	}

	IAsyncAction AddGroup::AddGroup_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.as<Controls::Button>();
		auto jsonObject = button.Tag().as<JsonObject>();
		auto password = VisualTreeHelper::GetParent(button).as<StackPanel>().Children().GetAt(0).as<TextBox>().Text();
		try {
			button.IsEnabled(false);
			JsonObject request;
			request.Insert(L"groupId", jsonObject.GetNamedValue(L"groupId"));
			request.Insert(L"password", JsonValue::CreateStringValue(password));
			auto resp = co_await TransportService().InvokeAsync(L"group", L"join", request);
			auto str = resp.ToString();
			if (resp.GetNamedBoolean(L"success")) {
				co_await ContentDialog(L"加群成功", resp.GetNamedString(L"message"));
			}
			else {
				co_await ContentDialog(L"加群失败", resp.GetNamedString(L"message"));
			}
		}
		catch (winrt::hresult_error const& ex) {
			ContentDialog(L"加群失败", L"未知错误");
		}
		button.IsEnabled(true);
	}
	winrt::Windows::Foundation::IAsyncAction AddGroup::ContentDialog(hstring title, hstring content)
	{
		auto dialog = Controls::ContentDialog();
		dialog.XamlRoot(this->XamlRoot());
		dialog.Title(box_value(title));
		dialog.Content(box_value(content));
		dialog.CloseButtonText(L"确定");
		co_await dialog.ShowAsync();
	}
}






