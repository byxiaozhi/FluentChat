#include "pch.h"
#include "App.xaml.h"
#include "GroupPage.xaml.h"
#if __has_include("GroupPage.g.cpp")
#include "GroupPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Data::Json;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::FluentChat::implementation
{
    GroupPage::GroupPage()
    {
        InitializeComponent();
    }
    FluentChat::AppViewModel GroupPage::AppViewModel()
    {
        return Application::Current().try_as<App>()->AppViewModel();
    }
    FluentChat::TransportService GroupPage::TransportService()
    {
        return AppViewModel().TransportService();
    }
    IAsyncAction GroupPage::ListView_Groups_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
    {
        auto response = co_await TransportService().InvokeAsync(L"group", L"list", JsonObject());
        auto results = response.GetNamedArray(L"groups");
        ListView_Groups().Items().Clear();
        for (auto& item : results) ListView_Groups().Items().Append(item.GetObjectW());
    }
    void GroupPage::ListView_Groups_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
    {
        auto item = ListView_Groups().SelectedItem().try_as<JsonObject>();
        auto chat = AppViewModel().ChatViewModel();
        if (chat.ChatType() != 1 || chat.ChatInfo() == nullptr || chat.ChatInfo().GetNamedNumber(L"groupId") != item.GetNamedNumber(L"groupId")) {
            chat.ChatType(1);
            chat.ChatInfo(item);
        }
    }
}



