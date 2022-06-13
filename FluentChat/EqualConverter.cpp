#include "pch.h"
#include "EqualConverter.h"
#include "EqualConverter.g.cpp"

namespace winrt::FluentChat::implementation
{
    bool EqualConverter::IsReverse()
    {
        return m_isReverse;
    }
    void EqualConverter::IsReverse(bool value)
    {
        m_isReverse = value;
    }
    winrt::Windows::Foundation::IInspectable EqualConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        auto str1 = value.try_as<hstring>().value_or(L"");
        auto str2 = parameter.try_as<hstring>().value_or(L"");
        return box_value(m_isReverse && str1 != str2 || !m_isReverse && str1 == str2);
    }
    winrt::Windows::Foundation::IInspectable EqualConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        throw hresult_not_implemented();
    }
}
