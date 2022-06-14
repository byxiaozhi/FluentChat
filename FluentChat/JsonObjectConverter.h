#pragma once
#include "JsonObjectConverter.g.h"

namespace winrt::FluentChat::implementation
{
    struct JsonObjectConverter : JsonObjectConverterT<JsonObjectConverter>
    {
        JsonObjectConverter() = default;

        winrt::Windows::Foundation::IInspectable Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
        winrt::Windows::Foundation::IInspectable ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
    };
}
namespace winrt::FluentChat::factory_implementation
{
    struct JsonObjectConverter : JsonObjectConverterT<JsonObjectConverter, implementation::JsonObjectConverter>
    {
    };
}
