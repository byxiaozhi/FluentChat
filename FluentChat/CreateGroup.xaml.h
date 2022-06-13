#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "CreateGroup.g.h"

namespace winrt::FluentChat::implementation
{
    struct CreateGroup : CreateGroupT<CreateGroup>
    {
        CreateGroup();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct CreateGroup : CreateGroupT<CreateGroup, implementation::CreateGroup>
    {
    };
}
