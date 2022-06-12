#pragma once
#include "pch.h"
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

namespace winrt::FluentChat::Utilities {

	std::tuple<winrt::Microsoft::UI::Composition::SystemBackdrops::MicaController, 
		winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration> SetMicaBackdrop(Windows::Foundation::IInspectable const& window);
}