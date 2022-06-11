#pragma once
#include <pch.h>
#include <winrt/Windows.Networking.Sockets.h>
#include "TransportService.g.h"
#include "AppViewModel.g.h"

namespace winrt::FluentChat::implementation
{
	struct TransportService : TransportServiceT<TransportService>
	{
		TransportService() = default;

		FluentChat::AppViewModel AppViewModel();

		Windows::Foundation::IAsyncAction TryConnect();

		Windows::Foundation::IAsyncAction PostMessage(hstring msg);

		Windows::Foundation::IAsyncAction MessageLoop();

		void OnMessage(hstring msg);

	private:
		Windows::Networking::Sockets::StreamSocket m_streamSocket{ nullptr };
	};
}

namespace winrt::FluentChat::factory_implementation
{
	struct TransportService : TransportServiceT<TransportService, implementation::TransportService>
	{
	};
}
