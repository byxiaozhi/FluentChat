#include "pch.h"
#include "AddFriend.xaml.h"
#include "App.xaml.h"
#if __has_include("AddFriend.g.cpp")
#include "AddFriend.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Data::Json;
using namespace Controls;

namespace winrt::FluentChat::implementation
{
	AddFriend::AddFriend()
	{
		InitializeComponent();
	}

	FluentChat::AppViewModel AddFriend::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	FluentChat::TransportService AddFriend::TransportService()
	{
		return AppViewModel().TransportService();
	}

	IAsyncAction AddFriend::Search_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		if (TextBox_Search().Text().empty()) co_return;
		JsonObject request;
		request.SetNamedValue(L"value", JsonValue::CreateStringValue(TextBox_Search().Text()));
		auto response = co_await TransportService().InvokeAsync(L"friend", L"search", request);
		auto results = response.GetNamedArray(L"results");
		ItemsControl_Search().Items().Clear();
		for (auto& item : results) ItemsControl_Search().Items().Append(item.GetObjectW());
		Panel_Search().Visibility(Visibility::Visible);
	}

	void AddFriend::TextBox_Search_TextChanged(IInspectable const& sender, Controls::TextChangedEventArgs const& e)
	{
		ItemsControl_Search().Items().Clear();
		Panel_Search().Visibility(Visibility::Collapsed);
	}

	void AddFriend::Button_Add_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.try_as<Button>();
		auto json = button.Tag().try_as<JsonObject>();
		auto stateDirect = json.GetNamedNumber(L"stateDirect");
		auto friendInverse = json.GetNamedNumber(L"friendInverse");
		button.IsEnabled(stateDirect == -1 || stateDirect == 1 && friendInverse == 0);
		if (stateDirect == 0 && friendInverse == 1) button.Content(box_value(L"已发送请求"));
		if (stateDirect == 0 && friendInverse == 0) button.Content(box_value(L"已添加"));
		if (stateDirect == 2 || stateDirect == 2) button.Content(box_value(L"无法添加"));
	}

	IAsyncAction AddFriend::Button_Add_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.try_as<Button>();
		auto json = button.Tag().try_as<JsonObject>();
		auto stateDirect = json.GetNamedNumber(L"stateDirect");
		auto friendInverse = json.GetNamedNumber(L"friendInverse");
		if (stateDirect == -1)
		{
			JsonObject response = co_await TransportService().InvokeAsync(L"friend", L"addRequest", json);
			if (response.GetNamedBoolean(L"success")) {
				button.IsEnabled(false);
				button.Content(box_value(L"已发送请求"));
			}
		}
		else {
			JsonObject response = co_await TransportService().InvokeAsync(L"friend", L"addAccept", json);
			if (response.GetNamedBoolean(L"success")) {
				button.IsEnabled(false);
				button.Content(box_value(L"已添加"));
			}
		}
	}

	IAsyncAction AddFriend::ItemsControl_Request_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto response = co_await TransportService().InvokeAsync(L"friend", L"listRequest", JsonObject());
		auto results = response.GetNamedArray(L"requests");
		ItemsControl_Request().Items().Clear();
		if (results.Size() > 0) {
			for (auto& item : results) ItemsControl_Request().Items().Append(item.GetObjectW());
			ItemsControl_Request().Visibility(Visibility::Visible);
		}
	}

	IAsyncAction AddFriend::Accept_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.try_as<Button>();
		auto json = button.Tag().try_as<JsonObject>();
		JsonObject response = co_await TransportService().InvokeAsync(L"friend", L"addAccept", json);
		if (response.GetNamedBoolean(L"success")) {
			ItemsControl_Request_Loaded(*this, nullptr);
		}
	}

	IAsyncAction AddFriend::Refuse_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		auto button = sender.try_as<Button>();
		auto json = button.Tag().try_as<JsonObject>();
		JsonObject response = co_await TransportService().InvokeAsync(L"friend", L"addRefuse", json);
		if (response.GetNamedBoolean(L"success")) {
			ItemsControl_Request_Loaded(*this, nullptr);
		}
	}
}


