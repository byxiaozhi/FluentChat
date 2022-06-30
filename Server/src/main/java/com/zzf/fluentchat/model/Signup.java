package com.zzf.fluentchat.model;

import org.hibernate.validator.constraints.Length;

import javax.validation.constraints.Email;
import javax.validation.constraints.NotBlank;

public class Signup {
    @NotBlank(message = "昵称不能为空")
    @Length(min = 2, message = "昵称长度不能小于2位")
    private String nickname;

    @NotBlank(message = "邮箱不能为空")
    @Email(message = "电子邮箱格式错误")
    private String email;

    @NotBlank(message = "密码不能为空")
    @Length(min = 6, message = "密码长度不能小于6位")
    private String password;

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }
}

