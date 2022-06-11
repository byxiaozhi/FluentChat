#include "pch.h"
#include "App.xaml.h"
#include "TransportService.h"
#if __has_include("TransportService.g.cpp")
#include "TransportService.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;
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
		HostName hostName{ L"localhost" };
		co_await m_streamSocket.ConnectAsync(hostName, L"8000");
	}
}
