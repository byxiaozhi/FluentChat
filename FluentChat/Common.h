#pragma once
#include "pch.h"

namespace winrt::FluentChat::Utilities {

	HWND GetWindowHandle(winrt::com_ptr<::IWindowNative> windowNative);

	void CenterWindow(winrt::com_ptr<::IWindowNative> windowNative, int width, int height);

	void DisableResize(winrt::com_ptr<::IWindowNative> windowNative);
}