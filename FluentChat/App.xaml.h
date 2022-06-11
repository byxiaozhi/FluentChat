#pragma once

#include "App.xaml.g.h"

namespace winrt::FluentChat::implementation
{
	struct App : AppT<App>
	{
		App();

		void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

		FluentChat::AppViewModel AppViewModel();

	private:
		FluentChat::AppViewModel m_appViewModel{ nullptr };
	};
}
