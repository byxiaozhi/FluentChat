#include "pch.h"
#include "App.xaml.h"
#include "TransportService.h"
#include "CompletionSource.h"
#include <winrt/Windows.Storage.Streams.h>
#if __has_include("TransportService.g.cpp")
#include "TransportService.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
using namespace Windows::Networking;
using namespace Windows::Data::Json;

namespace winrt::FluentChat::implementation
{
	FluentChat::AppViewModel TransportService::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	IAsyncAction TransportService::TryConnect()
	{
		try
		{
			EnsureClose(m_streamSocket);
			m_streamSocket = Windows::Networking::Sockets::StreamSocket();
			co_await m_streamSocket.ConnectAsync(HostName{ L"localhost" }, L"8000");
			MessageLoop();
			OnConnect();
		}
		catch (winrt::hresult_error const& ex)
		{
			EnsureClose(m_streamSocket);
			OnConnectError(ex);
		}
	}

	Windows::Foundation::IAsyncAction TransportService::PostMessage(hstring msg)
	{
		auto streamSocket = m_streamSocket;
		try
		{
			DataWriter dataWriter{ streamSocket.OutputStream() };
			dataWriter.WriteInt32(854749800);
			dataWriter.WriteInt32(msg.size());
			dataWriter.WriteString(msg);
			co_await dataWriter.StoreAsync();
			dataWriter.DetachStream();
		}
		catch (winrt::hresult_error const& ex)
		{				
			EnsureClose(streamSocket);
		}
	}

	Windows::Foundation::IAsyncOperation<JsonObject> TransportService::InvokeAsync(hstring controller, hstring action, JsonObject args)
	{
		JsonObject jsonMsg;
		auto sessionId = m_autoIncrementId++;
		jsonMsg.Insert(L"controller", JsonValue::CreateStringValue(controller));
		jsonMsg.Insert(L"action", JsonValue::CreateStringValue(action));
		jsonMsg.Insert(L"sessionId", JsonValue::CreateNumberValue(sessionId));
		jsonMsg.Insert(L"args", args);
		auto completionSource = std::make_shared<Utilities::CompletionSource<JsonObject>>();
		m_sessionMap.insert(std::pair<uint32_t, std::shared_ptr<Utilities::CompletionSource<JsonObject>>>(sessionId, completionSource));
		co_await PostMessage(jsonMsg.ToString());
		auto resp = co_await *completionSource;
		winrt::check_bool(resp.GetNamedNumber(L"code") == 0);
		co_return resp.GetNamedObject(L"results");
	}

	Windows::Foundation::IAsyncAction TransportService::MessageLoop()
	{
		auto streamSocket = m_streamSocket;
		DataReader dataReader{ streamSocket.InputStream() };
		try
		{
			while (true)
			{
				co_await dataReader.LoadAsync(sizeof(int));
				auto length = dataReader.ReadInt32();
				auto loaded = co_await dataReader.LoadAsync(length);
				auto body = dataReader.ReadString(loaded);
				OnMessage(body);
			}
		}
		catch (winrt::hresult_error const& ex)
		{
			EnsureClose(streamSocket);
			OnDisconnect();
		}
	}

	void TransportService::OnConnect()
	{
		m_onConnect(*this, true);
	}

	void TransportService::OnConnectError(winrt::hresult_error const& ex)
	{
		m_onDisconnect(*this, true);
	}

	void TransportService::OnMessage(hstring msg)
	{
		auto json = JsonObject::Parse(msg);
		auto type = json.GetNamedNumber(L"type");
		if (type == 0) {
			auto sessionId = json.GetNamedNumber(L"sessionId");
			auto completionSource = m_sessionMap.find(sessionId);
			if (completionSource != m_sessionMap.end())
			{
				completionSource->second->Set(json);
				m_sessionMap.erase(sessionId);
			}
		}
		else {
			m_onDispatch(*this, json);
		}
	}

	void TransportService::OnDisconnect()
	{
		m_onConnect(*this, true);
	}

	void TransportService::EnsureClose(Windows::Networking::Sockets::StreamSocket streamSocket)
	{
		try { if(streamSocket!=nullptr) streamSocket.Close(); }
		catch (winrt::hresult_error const& ex) {}
	}
	winrt::event_token TransportService::OnDispatch(Windows::Foundation::EventHandler<JsonObject> const& handler)
	{
		return m_onDispatch.add(handler);
	}
	void TransportService::OnDispatch(winrt::event_token const& token) noexcept
	{
		m_onDispatch.remove(token);
	}
	winrt::event_token TransportService::OnConnect(Windows::Foundation::EventHandler<bool> const& handler)
	{
		return m_onConnect.add(handler);
	}
	void TransportService::OnConnect(winrt::event_token const& token) noexcept
	{
		m_onConnect.remove(token);
	}
	winrt::event_token TransportService::OnDisconnect(Windows::Foundation::EventHandler<bool> const& handler)
	{
		return m_onDisconnect.add(handler);
	}
	void TransportService::OnDisconnect(winrt::event_token const& token) noexcept
	{
		m_onDisconnect.remove(token);
	}
	winrt::event_token TransportService::OnConnectError(Windows::Foundation::EventHandler<bool> const& handler)
	{
		return m_onConnectError.add(handler);
	}
	void TransportService::OnConnectError(winrt::event_token const& token) noexcept
	{
		m_onConnectError.remove(token);
	}
}
