#include "pch.h"
#include "TransportService.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
using namespace Windows::Networking;

namespace winrt::FluentChat
{
	IAsyncAction TransportService::StartClient()
	{
		HostName hostName{ L"localhost" };
		co_await m_streamSocket.ConnectAsync(hostName, L"8000");
	}
}
