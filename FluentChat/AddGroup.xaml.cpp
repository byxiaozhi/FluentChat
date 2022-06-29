#include "pch.h"
#include "AddGroup.xaml.h"
#include "App.xaml.h"
#if __has_include("AddGroup.g.cpp")
#include "AddGroup.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
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
}



