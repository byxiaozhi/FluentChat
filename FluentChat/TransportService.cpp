#include "pch.h"
#include "App.xaml.h"
#include "TransportService.h"
#include <winrt/Windows.Storage.Streams.h>
#if __has_include("TransportService.g.cpp")
#include "TransportService.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
using namespace Windows::Networking;

namespace winrt::FluentChat::implementation
{
	FluentChat::AppViewModel TransportService::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	IAsyncAction TransportService::TryConnect()
	{
		m_streamSocket = Windows::Networking::Sockets::StreamSocket();
		co_await m_streamSocket.ConnectAsync(HostName{ L"localhost" }, L"8000");
		MessageLoop();
	}

	Windows::Foundation::IAsyncAction TransportService::PostMessage(hstring msg)
	{
		DataWriter dataWriter{ m_streamSocket.OutputStream() };
		dataWriter.WriteInt32(854749800);
		dataWriter.WriteInt32(msg.size());
		dataWriter.WriteString(msg);
		co_await dataWriter.StoreAsync();
		dataWriter.DetachStream();
	}

	Windows::Foundation::IAsyncAction TransportService::MessageLoop()
	{
		DataReader dataReader{ m_streamSocket.InputStream() };
		while (true)
		{
			co_await dataReader.LoadAsync(sizeof(int));
			auto length = dataReader.ReadInt32();
			auto loaded = co_await dataReader.LoadAsync(length);
			auto body = dataReader.ReadString(loaded);
			OnMessage(body);
		}
	}

	void TransportService::OnMessage(hstring msg)
	{

	}
}
