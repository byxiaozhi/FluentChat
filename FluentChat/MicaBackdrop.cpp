#include "pch.h"
#include "MicaBackdrop.h"
#include <DispatcherQueue.h>
#include <MddBootstrap.h>
#include <winrt/Windows.System.h>

using namespace winrt::Microsoft::UI::Composition::SystemBackdrops;
using namespace ABI::Windows::System;

namespace winrt::FluentChat::Utilities {

	static winrt::Windows::System::DispatcherQueueController m_dispatcherQueueController{ nullptr };

	void EnsureWindowsSystemDispatcherQueueController()
	{
		if (Windows::System::DispatcherQueue::GetForCurrentThread() != nullptr)
			return;
		if (m_dispatcherQueueController == nullptr) {
			DispatcherQueueOptions options
			{
				sizeof(DispatcherQueueOptions),
				DQTYPE_THREAD_CURRENT,
				DQTAT_COM_STA
			};
			winrt::check_hresult(CreateDispatcherQueueController(options, reinterpret_cast<IDispatcherQueueController**>(winrt::put_abi(m_dispatcherQueueController))));
		}
	}

	std::tuple<MicaController, SystemBackdropConfiguration> SetMicaBackdrop(Windows::Foundation::IInspectable const& window)
	{
		EnsureWindowsSystemDispatcherQueueController();
		auto m_micaController = Microsoft::UI::Composition::SystemBackdrops::MicaController();
		if (m_micaController.IsSupported())
		{
			auto m_configurationSource = Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration();
			m_configurationSource.IsInputActive(true);
			m_micaController.AddSystemBackdropTarget(window.try_as<Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop>());
			m_micaController.SetSystemBackdropConfiguration(m_configurationSource);
			return std::make_tuple(m_micaController, m_configurationSource);
		}
		return std::make_tuple(nullptr, nullptr);
	}
}

