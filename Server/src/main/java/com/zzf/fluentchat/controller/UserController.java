package com.zzf.fluentchat.controller;

import com.zzf.fluentchat.component.EntityConverter;
import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.model.Resp;
import com.zzf.fluentchat.model.Signup;
import com.zzf.fluentchat.repository.FriendRepository;
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

    final EntityConverter entityConverter;

    final FriendRepository friendRepository;

    public UserController(UserRepository userRepository, PasswordEncoder passwordEncoder, UserService userService, EntityConverter entityConverter, FriendRepository friendRepository) {
        this.userRepository = userRepository;
        this.passwordEncoder = passwordEncoder;
        this.userService = userService;
        this.entityConverter = entityConverter;
        this.friendRepository = friendRepository;
    }

    public Map<String, Object> route(String action, Map<String, Object> args, Map<String, Object> session) throws Exception {
        return switch (action) {
            case "signup" -> signup(args);
            case "login" -> login(args, session);
            case "editNickname" -> editNickname(args, session);
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
            map.put("message", "??????????????????");
        else if (nickname.length() < 2)
            map.put("message", "??????????????????2???");
        else if (email.isEmpty())
            map.put("message", "??????????????????");
        else if (isInvalidEmailAddress(email))
            map.put("message", "??????????????????");
        else if (password.isEmpty())
            map.put("message", "??????????????????");
        else if (password.length() < 6)
            map.put("message", "??????????????????6???");
        else {
            try {
                var user = new UserEntity();
                user.setNickname(nickname);
                user.setEmail(email);
                user.setPassword(password);
                userRepository.save(user);
                map.put("success", true);
                map.put("message", "????????????");
            } catch (Exception ex) {
                map.put("message", "?????????????????????");
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
            map.put("message", "??????????????????");
        else if (isInvalidEmailAddress(email))
            map.put("message", "??????????????????");
        else if (password.isEmpty())
            map.put("message", "??????????????????");
        else {
            var user = userRepository.findByEmail(email);
            if (user == null)
                map.put("message", "???????????????");
            else if (!user.getPassword().equals(password))
                map.put("message", "????????????");
            else if (!user.isEnabled())
                map.put("message", "???????????????");
            else if (!user.isAccountNonExpired())
                map.put("message", "????????????");
            else if (!user.isAccountNonLocked())
                map.put("message", "???????????????");
            else if (!user.isCredentialsNonExpired())
                map.put("message", "????????????");
            else {
                map.put("success", true);
                map.put("message", "????????????");
                map.put("nickname", user.getNickname());
                session.put("email", email);
                session.put("user", user);
            }
        }
        return map;
    }

    public Map<String, Object> editNickname(Map<String, Object> args, Map<String, Object> session) {
        var nickname = args.get("nickname").toString();
        var user = (UserEntity) session.get("user");
        if (nickname.isEmpty())
            return Map.of("success", false, "message", "??????????????????");
        else if (nickname.length() < 2)
            return Map.of("success", false, "message", "??????????????????2???");
        user.setNickname(nickname);
        userRepository.save(user);
        return Map.of("success", true, "message", "????????????");
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
            return new Resp(Resp.Code.FAILURE, "????????????", fieldErrors);
        }
        var newUser = new UserEntity();
        newUser.setNickname(signup.getNickname());
        newUser.setEmail(signup.getEmail());
        newUser.setPassword(passwordEncoder.encode(signup.getPassword()));
        newUser.setCreateDate(new Date());
        newUser.setUpdateDate(new Date());
        newUser.setRole("user");
        userService.saveUser(newUser);
        return new Resp(Resp.Code.SUCCESS, "????????????");
    }

    @RequestMapping(value = "info", method = RequestMethod.GET)
    public Resp info(Principal principal) {
        if (principal == null)
            return new Resp(Resp.Code.FAILURE, "?????????");
        var user = userService.loadUserByEmail(principal.getName());
        var ret = new HashMap<String, Object>();
        ret.put("username", user.getUsername());
        ret.put("email", user.getEmail());
        ret.put("role", user.getRole());
        return new Resp(Resp.Code.SUCCESS, "????????????", ret);
    }

    @RequestMapping(value = "list", method = RequestMethod.GET)
    public Resp list(int page, int count, String query) {
        var pageable = PageRequest.of(page, count);
        var list = userRepository.selectAll(pageable, query).stream().map(entityConverter::convert);
        var total = userRepository.count();
        return new Resp(Resp.Code.SUCCESS, "????????????", Map.of("list", list, "total", total));
    }

    @RequestMapping(value = "editUser", method = RequestMethod.POST)
    public Resp editRole(int id, String role, String nickName) {
        var opt = userRepository.findById(id);
        if (opt.isEmpty())
            return new Resp(Resp.Code.FAILURE, "???????????????");
        var user = opt.get();
        user.setRole(role);
        user.setNickname(nickName);
        userRepository.save(user);
        return new Resp(Resp.Code.SUCCESS, "????????????");
    }

    @RequestMapping(value = "delete", method = RequestMethod.POST)
    public Resp delete(int id) {
        var opt = userRepository.findById(id);
        if (opt.isEmpty())
            return new Resp(Resp.Code.FAILURE, "???????????????");
        var user = opt.get();
        friendRepository.deleteAllFriend(user);
        userRepository.delete(user);
        return new Resp(Resp.Code.SUCCESS, "????????????");
    }
}
