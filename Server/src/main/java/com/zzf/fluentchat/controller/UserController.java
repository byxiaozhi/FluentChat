package com.zzf.fluentchat.controller;

import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.repository.UserRepository;
import org.springframework.stereotype.Controller;

import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import java.util.HashMap;
import java.util.Map;

@Controller
public class UserController {

    final UserRepository userRepository;

    public UserController(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    public Map<String, Object> route(String action, Map<String, Object> args, Map<String, Object> session) throws Exception {
        return switch (action) {
            case "signup" -> signup(args);
            case "login" -> login(args, session);
            default -> throw new Exception("action does not exist");
        };
    }

    public Map<String, Object> signup(Map<String, Object> args) {
        var map = new HashMap<String, Object>();
        map.put("success", false);
        var nickname = args.get("nickname").toString();
        var email = args.get("email").toString();
        var password = args.get("password").toString();
        if (nickname.isEmpty())
            map.put("message", "昵称不能为空");
        else if (nickname.length() < 2)
            map.put("message", "昵称不能小于2位");
        else if (email.isEmpty())
            map.put("message", "邮箱不能为空");
        else if (isInvalidEmailAddress(email))
            map.put("message", "邮箱格式错误");
        else if (password.isEmpty())
            map.put("message", "密码不能为空");
        else if (password.length() < 6)
            map.put("message", "密码不能小于6位");
        else {
            try {
                var user = new UserEntity();
                user.setNickname(nickname);
                user.setEmail(email);
                user.setPassword(password);
                userRepository.save(user);
                map.put("success", true);
                map.put("message", "注册成功");
            } catch (Exception ex) {
                map.put("message", "邮箱已经被注册");
            }
        }
        return map;
    }

    public Map<String, Object> login(Map<String, Object> args, Map<String, Object> session) {
        var map = new HashMap<String, Object>();
        map.put("success", false);
        var email = args.get("email").toString();
        var password = args.get("password").toString();
        if (email.isEmpty())
            map.put("message", "邮箱不能为空");
        else if (isInvalidEmailAddress(email))
            map.put("message", "邮箱格式错误");
        else if (password.isEmpty())
            map.put("message", "密码不能为空");
        else {
            var user = userRepository.findByEmail(email);
            if (user == null)
                map.put("message", "邮箱不存在");
            else if (!user.getPassword().equals(password))
                map.put("message", "密码错误");
            else {
                map.put("success", true);
                map.put("message", "登录成功");
                map.put("nickname", user.getNickname());
                session.put("email", email);
                session.put("user", user);
            }
        }
        return map;
    }

    public static boolean isInvalidEmailAddress(String email) {
        try {
            var emailAddress = new InternetAddress(email);
            emailAddress.validate();
            return false;
        } catch (AddressException ex) {
            return true;
        }
    }
}
