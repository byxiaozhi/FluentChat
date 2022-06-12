#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "SettingItem.g.h"

namespace winrt::FluentChat::implementation
{
    struct SettingItem : SettingItemT<SettingItem>
    {
        SettingItem();

        Microsoft::UI::Xaml::Controls::IconElement Icon();
        void Icon(Microsoft::UI::Xaml::Controls::IconElement value);

        IInspectable Title();
        void Title(IInspectable value);

        IInspectable Description();
        void Description(IInspectable value);

        IInspectable Operate();
        void Operate(IInspectable value);

    private:
        static Microsoft::UI::Xaml::DependencyProperty m_iconProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_titleProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_descriptionProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_operateProperty;
    };
}

namespace winrt::FluentChat::factory_implementation
{
    struct SettingItem : SettingItemT<SettingItem, implementation::SettingItem>
    {
    };
}
