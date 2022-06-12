#include "pch.h"
#include "SettingItem.xaml.h"
#if __has_include("SettingItem.g.cpp")
#include "SettingItem.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::FluentChat::implementation
{
    Microsoft::UI::Xaml::DependencyProperty SettingItem::m_iconProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Icon",
            winrt::xaml_typename<Controls::IconElement>(),
            winrt::xaml_typename<FluentChat::SettingItem>(),
            nullptr);

    Microsoft::UI::Xaml::DependencyProperty SettingItem::m_titleProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Title",
            winrt::xaml_typename<IInspectable>(),
            winrt::xaml_typename<FluentChat::SettingItem>(),
            nullptr);

    Microsoft::UI::Xaml::DependencyProperty SettingItem::m_descriptionProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Description",
            winrt::xaml_typename<IInspectable>(),
            winrt::xaml_typename<FluentChat::SettingItem>(),
            nullptr);

    Microsoft::UI::Xaml::DependencyProperty SettingItem::m_operateProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"Operate",
            winrt::xaml_typename<IInspectable>(),
            winrt::xaml_typename<FluentChat::SettingItem>(),
            nullptr);
    
    SettingItem::SettingItem()
    {
        InitializeComponent();
    }
    Controls::IconElement SettingItem::Icon()
    {
        return GetValue(SettingItem::m_iconProperty).try_as<Controls::IconElement>();
    }
    void SettingItem::Icon(Microsoft::UI::Xaml::Controls::IconElement value)
    {
        SetValue(SettingItem::m_iconProperty, box_value(value));
    }
    IInspectable SettingItem::Title()
    {
        return GetValue(SettingItem::m_titleProperty);
    }
    void SettingItem::Title(IInspectable value)
    {
        SetValue(SettingItem::m_titleProperty, value);
    }
    IInspectable SettingItem::Description()
    {
        return GetValue(SettingItem::m_descriptionProperty);
    }
    void SettingItem::Description(IInspectable value)
    {
        SetValue(SettingItem::m_descriptionProperty, value);
    }
    IInspectable SettingItem::Operate()
    {
        return GetValue(SettingItem::m_operateProperty);
    }
    void SettingItem::Operate(IInspectable value)
    {
        SetValue(SettingItem::m_operateProperty, value);
    }
}
