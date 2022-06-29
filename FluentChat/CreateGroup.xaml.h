#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "CreateGroup.g.h"

using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
    struct CreateGroup : CreateGroupT<CreateGroup>
    {
        CreateGroup();
        FluentChat::AppViewModel AppViewModel();
        FluentChat::TransportService TransportService();
        IAsyncAction CreateGroup_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        IAsyncAction ContentDialog(hstring title, hstring content);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct CreateGroup : CreateGroupT<CreateGroup, implementation::CreateGroup>
    {
    };
}
