#include "pch.h"
#include "JsonArrayConverter.h"
#include "JsonArrayConverter.g.cpp"

using namespace winrt;
using namespace Windows::Data::Json;

namespace winrt::FluentChat::implementation
{
    winrt::Windows::Foundation::IInspectable JsonArrayConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        auto json = value.try_as<JsonObject>();
        auto key = parameter.try_as<hstring>();
        if (key.has_value()) return box_value(json.GetNamedArray(key.value()));
        else return box_value(json.GetArray());
    }
    winrt::Windows::Foundation::IInspectable JsonArrayConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        throw hresult_not_implemented();
    }
}
