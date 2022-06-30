package com.zzf.fluentchat.controller;

import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.model.Resp;
import com.zzf.fluentchat.model.Signup;
import com.zzf.fluentchat.repository.UserRepository;
import com.zzf.fluentchat.service.UserService;
import org.springframework.data.domain.PageRequest;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.validation.Valid;
import java.security.Principal;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

@Controller
@ResponseBody
@RequestMapping("api/user")
public class UserController {

    final UserRepository userRepository;

    final PasswordEncoder passwordEncoder;

    final UserService userService;

    public UserController(UserRepository userRepository, PasswordEncoder passwordEncoder, UserService userService) {
        this.userRepository = userRepository;
        this.passwordEncoder = passwordEncoder;
        this.userService = userService;
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
            else if (!user.isEnabled())
                map.put("message", "账号不可用");
            else if (!user.isAccountNonExpired())
                map.put("message", "账号过期");
            else if (!user.isAccountNonLocked())
                map.put("message", "账号被锁定");
            else if (!user.isCredentialsNonExpired())
                map.put("message", "密码过期");
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

    @RequestMapping(value = "signup", method = RequestMethod.POST)
    public Resp signup(@Valid Signup signup, BindingResult bindingResult) {
        if (bindingResult.hasErrors()) {
            var fieldErrors = bindingResult.getFieldErrors();
            return new Resp(Resp.Code.FAILURE, "注册失败", fieldErrors);
        }
        var newUser = new UserEntity();
        newUser.setNickname(signup.getNickname());
        newUser.setEmail(signup.getEmail());
        newUser.setPassword(passwordEncoder.encode(signup.getPassword()));
        newUser.setCreateDate(new Date());
        newUser.setUpdateDate(new Date());
        newUser.setRole("user");
        userService.saveUser(newUser);
        return new Resp(Resp.Code.SUCCESS, "注册成功");
    }

    @RequestMapping(value = "info", method = RequestMethod.GET)
    public Resp info(Principal principal) {
        if (principal == null)
            return new Resp(Resp.Code.FAILURE, "未登录");
        var user = userService.loadUserByEmail(principal.getName());
        var ret = new HashMap<String, Object>();
        ret.put("username", user.getUsername());
        ret.put("email", user.getEmail());
        ret.put("role", user.getRole());
        return new Resp(Resp.Code.SUCCESS, "获取成功", ret);
    }

    @RequestMapping(value = "list", method = RequestMethod.GET)
    public Resp list(int page, int count, String query) {
        var pageable = PageRequest.of(page, count);
        var list = userRepository.selectAll(pageable, query);
        var total = userRepository.count();
        return new Resp(Resp.Code.SUCCESS, "读取成功", Map.of("list", list, "total", total));
    }

    @RequestMapping(value = "editRole", method = RequestMethod.POST)
    public Resp editRole(int id, String role) {
        var opt = userRepository.findById(id);
        if (opt.isEmpty())
            return new Resp(Resp.Code.FAILURE, "用户不存在");
        var user = opt.get();
        user.setRole(role);
        userRepository.save(user);
        return new Resp(Resp.Code.SUCCESS, "修改成功");
    }
}
