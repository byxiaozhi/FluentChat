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
        void Search_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct AddGroup : AddGroupT<AddGroup, implementation::AddGroup>
    {
    };
}
