#include "pch.h"
#include "ChatViewModel.h"
#include "ChatViewModel.g.cpp"

namespace winrt::FluentChat::implementation
{
    winrt::Windows::Data::Json::JsonObject ChatViewModel::ChatInfo()
    {
        return m_chatInfo;
    }
    void ChatViewModel::ChatInfo(winrt::Windows::Data::Json::JsonObject const& value)
    {
        if (m_chatInfo != value)
        {
            m_chatInfo = value;
            RaisePropertyChanged(L"ChatInfo");
        }
    }
    int32_t ChatViewModel::ChatType()
    {
        return m_chatType;
    }
    void ChatViewModel::ChatType(int32_t value)
    {
        if (m_chatType != value)
        {
            m_chatType = value;
            RaisePropertyChanged(L"ChatType");
        }
    }
    int32_t ChatViewModel::ChatView()
    {
        return m_chatView;
    }
    void ChatViewModel::ChatView(int32_t value)
    {
        if (m_chatView != value)
        {
            m_chatView = value;
            RaisePropertyChanged(L"ChatView");
        }
    }
    void ChatViewModel::RaisePropertyChanged(hstring propertyName)
    {
        m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ propertyName });
    }
    winrt::event_token ChatViewModel::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void ChatViewModel::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}
