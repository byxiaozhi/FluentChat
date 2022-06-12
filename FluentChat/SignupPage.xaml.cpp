﻿#include "pch.h"
#include "App.xaml.h"
#include "SignupPage.xaml.h"
#if __has_include("SignupPage.g.cpp")
#include "SignupPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;
using namespace Windows::Data::Json;


namespace winrt::FluentChat::implementation
{
    SignupPage::SignupPage()
    {
        InitializeComponent();
    }

    IAsyncAction SignupPage::Signup_Click(IInspectable const& sender, RoutedEventArgs const& e)
    {
        if (PasswordBox_Password().Password() != PasswordBox_ConfirmPassword().Password()) {
            ContentDialog(L"注册失败", L"确认密码不一致");
            return;
        }
        try {
            JsonObject request;
            request.Insert(L"nickname", JsonValue::CreateStringValue(TextBox_NickName().Text()));
            request.Insert(L"email", JsonValue::CreateStringValue(TextBox_Email().Text()));
            request.Insert(L"password", JsonValue::CreateStringValue(PasswordBox_Password().Password()));
            auto connected = co_await TransportService().TryConnect();
            if (!connected) {
                ContentDialog(L"注册失败", L"网络发生错误");
                co_return;
            }
            auto resp = co_await TransportService().InvokeAsync(L"user", L"signup", request);
            auto str = resp.ToString();
            if (resp.GetNamedBoolean(L"success")) {
                ContentDialog(L"注册成功", resp.GetNamedString(L"message"));
            }
            else {
                ContentDialog(L"注册失败", resp.GetNamedString(L"message"));
            }
        }
        catch (winrt::hresult_error const& ex) {
            ContentDialog(L"注册失败", L"未知错误");
        }
    }

    FluentChat::AppViewModel SignupPage::AppViewModel()
    {
        return Application::Current().try_as<App>()->AppViewModel();
    }

    FluentChat::TransportService SignupPage::TransportService()
    {
        return AppViewModel().TransportService();
    }

    IAsyncAction SignupPage::ContentDialog(hstring title, hstring content)
    {
        auto dialog = Controls::ContentDialog();
        dialog.XamlRoot(this->XamlRoot());
        dialog.Title(box_value(title));
        dialog.Content(box_value(content));
        dialog.CloseButtonText(L"确定");
        co_await dialog.ShowAsync();
    }
}
