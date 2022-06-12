#pragma once
#include <pch.h>
#include <winrt/Windows.Networking.Sockets.h>
#include "CompletionSource.h"
#include "TransportService.g.h"
#include "AppViewModel.g.h"

using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::FluentChat::implementation
{
	struct TransportService : TransportServiceT<TransportService>
	{
		TransportService() = default;

		FluentChat::AppViewModel AppViewModel();

		Windows::Foundation::IAsyncOperation<bool> TryConnect();

		Windows::Foundation::IAsyncAction PostMessage(hstring msg);

		Windows::Foundation::IAsyncOperation<JsonObject> InvokeAsync(hstring controller, hstring action, JsonObject args);

		Windows::Foundation::IAsyncAction MessageLoop();

		void OnConnect();

		void OnConnectError(winrt::hresult_error const& ex);

		void OnMessage(hstring msg);

		void OnDisconnect();

		void EnsureClose(Windows::Networking::Sockets::StreamSocket streamSocket);

		winrt::event_token OnDispatch(Windows::Foundation::EventHandler<JsonObject> const& handler);

		void OnDispatch(winrt::event_token const& token) noexcept;

		winrt::event_token OnConnect(Windows::Foundation::EventHandler<bool> const& handler);

		void OnConnect(winrt::event_token const& token) noexcept;

		winrt::event_token OnDisconnect(Windows::Foundation::EventHandler<bool> const& handler);

		void OnDisconnect(winrt::event_token const& token) noexcept;

		winrt::event_token OnConnectError(Windows::Foundation::EventHandler<bool> const& handler);

		void OnConnectError(winrt::event_token const& token) noexcept;

	private:
		winrt::event<Windows::Foundation::EventHandler<JsonObject>> m_onDispatch;
		winrt::event<Windows::Foundation::EventHandler<bool>> m_onConnect;
		winrt::event<Windows::Foundation::EventHandler<bool>> m_onDisconnect;
		winrt::event<Windows::Foundation::EventHandler<bool>> m_onConnectError;
		Windows::Networking::Sockets::StreamSocket m_streamSocket{ nullptr };
		std::map<int, std::shared_ptr<Utilities::CompletionSource<JsonObject>>> m_sessionMap;
		int m_autoIncrementId = 0;
	};
}

namespace winrt::FluentChat::factory_implementation
{
	struct TransportService : TransportServiceT<TransportService, implementation::TransportService>
	{
	};
}
