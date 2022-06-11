#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Interop;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::FluentChat::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();
		sideNavView().SelectedItem(sideNavView().MenuItems().GetAt(0));
	}

	void MainPage::sideNavView_SelectionChanged(NavigationView const& sender, NavigationViewSelectionChangedEventArgs const& args)
	{
		auto pageName = sender.SelectedItem().try_as<NavigationViewItem>().Tag().try_as<hstring>();

		auto pageMap{ winrt::single_threaded_map<winrt::hstring, TypeName>(std::map<winrt::hstring, TypeName>{
			{ L"RecentPage", xaml_typename<RecentPage>() },
			{ L"FriendPage", xaml_typename<FriendPage>() },
			{ L"GroupPage", xaml_typename<GroupPage>() },
		}) };

		if (pageName.has_value() && pageMap.HasKey(pageName.value())) {
			leftColumn().Width(GridLength{ 300, GridUnitType::Pixel });
			rightColumn().Width(GridLength{ 1, GridUnitType::Star });
			sideFrame().Navigate(pageMap.Lookup(pageName.value()), nullptr, args.RecommendedNavigationTransitionInfo());
		}
		else {
			leftColumn().Width(GridLength{ 1, GridUnitType::Star });
			rightColumn().Width(GridLength{ 0, GridUnitType::Pixel });
			sideFrame().Navigate(xaml_typename<SettingsPage>(), nullptr, args.RecommendedNavigationTransitionInfo());
		}
	}
}
