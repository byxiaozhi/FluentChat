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
        if (chat.ChatType() != 1 || chat.ChatInfo() == nullptr || item == nullptr || chat.ChatInfo().GetNamedNumber(L"groupId") != item.GetNamedNumber(L"groupId")) {
            chat.ChatType(1);
            chat.ChatView(0);
            chat.ChatInfo(item);
        }
    }
    void GroupPage::Reload_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        ListView_Groups_Loaded(ListView_Groups(), nullptr);
    }
    winrt::Windows::Foundation::IAsyncAction GroupPage::ContentDialog(hstring title, hstring content)
    {
        auto dialog = Controls::ContentDialog();
        dialog.XamlRoot(this->XamlRoot());
        dialog.Title(box_value(title));
        dialog.Content(box_value(content));
        dialog.CloseButtonText(L"确定");
        co_await dialog.ShowAsync();
    }
    void GroupPage::EditAlias_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        ContentDialog(L"改不了", L"还没写这个功能");
    }

    void GroupPage::EditGroupName_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        ContentDialog(L"改不了", L"还没写这个功能");
    }

    winrt::Windows::Foundation::IAsyncAction GroupPage::ExitGroup_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto item = sender.as<MenuFlyoutItem>().Tag().as<JsonObject>();
        auto dialog = Controls::ContentDialog();
        dialog.XamlRoot(this->XamlRoot());
        dialog.Title(box_value(L"退出群聊"));
        dialog.Content(box_value(L"确定退出群聊？"));
        dialog.PrimaryButtonText(L"退出");
        dialog.CloseButtonText(L"取消");
        dialog.DefaultButton(ContentDialogButton::Close);
        auto result = co_await dialog.ShowAsync();
        if (result == ContentDialogResult::Primary)
        {

            try {
                co_await TransportService().InvokeAsync(L"group", L"quit", item);
                co_await ListView_Groups_Loaded(ListView_Groups(), nullptr);
            }
            catch (winrt::hresult_error const& ex) {
                ContentDialog(L"退出失败", L"未知错误");
            }
        }
    }
}









