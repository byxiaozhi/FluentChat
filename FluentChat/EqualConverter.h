#pragma once
#include "EqualConverter.g.h"

namespace winrt::FluentChat::implementation
{
    struct EqualConverter : EqualConverterT<EqualConverter>
    {
        EqualConverter() = default;

        bool IsReverse();
        void IsReverse(bool value);
        winrt::Windows::Foundation::IInspectable Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
        winrt::Windows::Foundation::IInspectable ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
    
    private:
        bool m_isReverse;
    };
}
namespace winrt::FluentChat::factory_implementation
{
    struct EqualConverter : EqualConverterT<EqualConverter, implementation::EqualConverter>
    {
    };
}
