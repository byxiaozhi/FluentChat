#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "AddFriend.g.h"

namespace winrt::FluentChat::implementation
{
	struct AddFriend : AddFriendT<AddFriend>
	{
		AddFriend();
		void Search_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
	};
}

namespace winrt::FluentChat::factory_implementation
{
	struct AddFriend : AddFriendT<AddFriend, implementation::AddFriend>
	{
	};
}
