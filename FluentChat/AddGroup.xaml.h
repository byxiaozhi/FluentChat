#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "AddGroup.g.h"

namespace winrt::FluentChat::implementation
{
    struct AddGroup : AddGroupT<AddGroup>
    {
        AddGroup();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
        winrt::Windows::Foundation::IAsyncAction Search_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        static winrt::hstring GetGroupId(winrt::Windows::Data::Json::JsonObject jsonObject);
        winrt::Windows::Foundation::IAsyncAction AddGroup_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        winrt::Windows::Foundation::IAsyncAction ContentDialog(hstring title, hstring content);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct AddGroup : AddGroupT<AddGroup, implementation::AddGroup>
    {
    };
}
