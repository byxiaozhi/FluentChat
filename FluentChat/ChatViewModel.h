#pragma once
#include "ChatViewModel.g.h"

namespace winrt::FluentChat::implementation
{
	struct ChatViewModel : ChatViewModelT<ChatViewModel>
	{
		ChatViewModel() = default;

		winrt::Windows::Data::Json::JsonObject ChatInfo();
		void ChatInfo(winrt::Windows::Data::Json::JsonObject const& value);
		int32_t ChatType();
		void ChatType(int32_t value);
		int32_t ChatView();
		void ChatView(int32_t value);
		winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
		void PropertyChanged(winrt::event_token const& token) noexcept;

	private:
		void RaisePropertyChanged(hstring propertyName);
		winrt::Windows::Data::Json::JsonObject m_chatInfo{ nullptr };
		int32_t m_chatType = -1;
		int32_t m_chatView = 0;
		event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
	};
}
namespace winrt::FluentChat::factory_implementation
{
	struct ChatViewModel : ChatViewModelT<ChatViewModel, implementation::ChatViewModel>
	{
	};
}
