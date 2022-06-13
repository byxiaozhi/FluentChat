#include "pch.h"
#include "EmptyToBoolConverter.h"
#include "EmptyToBoolConverter.g.cpp"

namespace winrt::FluentChat::implementation
{
    bool EmptyToBoolConverter::IsReverse()
    {
        return m_isReverse;
    }
    void EmptyToBoolConverter::IsReverse(bool value)
    {
        m_isReverse = value;
    }
    winrt::Windows::Foundation::IInspectable EmptyToBoolConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        auto str = value.try_as<hstring>().value_or(L"");
        return box_value(m_isReverse && str == L"" || !m_isReverse && str != L"");
    }
    winrt::Windows::Foundation::IInspectable EmptyToBoolConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        throw hresult_not_implemented();
    }
}
