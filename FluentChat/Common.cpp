#include "Common.h"
#include "pch.h"
#include "LoginWindow.xaml.h"
#include <microsoft.ui.xaml.window.h>

namespace winrt::FluentChat::Utilities {

	HWND GetWindowHandle(winrt::com_ptr<::IWindowNative> windowNative)
	{
		winrt::check_bool(windowNative);
		HWND hWnd{ 0 };
		windowNative->get_WindowHandle(&hWnd);
		return hWnd;
	}

	void CenterWindow(winrt::com_ptr<::IWindowNative> windowNative, int width, int height)
	{
		auto hWnd = GetWindowHandle(windowNative);
		auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
		auto screenHeight = GetSystemMetrics(SM_CYSCREEN);
		auto scale = GetDpiForWindow(hWnd) / 96.0;
		width *= scale;
		height *= scale;
		SetWindowPos(hWnd, 0, (screenWidth - width) / 2, (screenHeight - height) / 2, width, height, 0);
	}
}