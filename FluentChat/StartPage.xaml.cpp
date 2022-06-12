#include "pch.h"
#include "App.xaml.h"
#include "StartPage.xaml.h"
#if __has_include("StartPage.g.cpp")
#include "StartPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;

namespace winrt::FluentChat::implementation
{
    StartPage::StartPage()
    {
        InitializeComponent();
		navView().SelectedItem(navView().MenuItems().GetAt(0));
    }

	FluentChat::AppViewModel StartPage::AppViewModel()
	{
		return Application::Current().try_as<App>()->AppViewModel();
	}

	void winrt::FluentChat::implementation::StartPage::navView_SelectionChanged(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args)
	{
		TypeName typeName;
		auto pageName = sender.SelectedItem().try_as<NavigationViewItem>().Tag().try_as<hstring>();
		if (pageName == L"LoginPage")
			typeName = xaml_typename<LoginPage>();
		if (pageName == L"SignupPage")
			typeName = xaml_typename<SignupPage>();
		contentFrame().Navigate(typeName, *this, args.RecommendedNavigationTransitionInfo());
	}

	::NavigationView StartPage::NavigationView()
	{
		return navView();
	}
}
