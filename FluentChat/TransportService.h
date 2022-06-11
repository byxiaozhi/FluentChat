#pragma once
#include <winrt/Windows.Networking.Sockets.h>
#include <winrt/Windows.Storage.Streams.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;

namespace winrt::FluentChat
{
    struct TransportService : IInspectable
    {
        TransportService() = default;

        IAsyncAction StartClient();

    private:
        Windows::Networking::Sockets::StreamSocket m_streamSocket;
    };
}
