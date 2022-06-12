#pragma once
#include "pch.h"
#include "SignupPage.g.h"
#include "StartPage.xaml.h"

using namespace winrt::Windows::Foundation;

namespace winrt::FluentChat::implementation
{
	struct SignupPage : SignupPageT<SignupPage>
	{
		SignupPage();
		FluentChat::AppViewModel AppViewModel();
		FluentChat::TransportService TransportService();
		IAsyncAction Signup_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
		virtual void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs e);
		void BackToLoginClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

	private:
		IAsyncAction ContentDialog(hstring title, hstring content);
		com_ptr<StartPage> m_startPage { nullptr };
	};
}

namespace winrt::FluentChat::factory_implementation
{
	struct SignupPage : SignupPageT<SignupPage, implementation::SignupPage>
	{
	};
}
