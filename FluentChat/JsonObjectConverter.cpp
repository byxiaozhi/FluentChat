#include "pch.h"
#include "JsonObjectConverter.h"
#include "JsonObjectConverter.g.cpp"

using namespace winrt;
using namespace Windows::Data::Json;

namespace winrt::FluentChat::implementation
{
	winrt::Windows::Foundation::IInspectable JsonObjectConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
	{
		if (value == nullptr)
			return nullptr;
		auto json = value.try_as<JsonObject>();
		if(json == nullptr) json = value.try_as<JsonValue>().GetObjectW();
		auto key = parameter.try_as<hstring>();
		if (key.has_value()) return box_value(json.GetNamedString(key.value()));
		else return box_value(json.GetString());
	}
	winrt::Windows::Foundation::IInspectable JsonObjectConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
	{
		throw hresult_not_implemented();
	}
}
