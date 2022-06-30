package com.zzf.fluentchat.service;

import com.zzf.fluentchat.component.CommonUtil;
import com.zzf.fluentchat.component.PasswordEncoder;
import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.repository.UserRepository;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

@Service
public class UserService implements UserDetailsService {
    final UserRepository userRepository;
    final PasswordEncoder passwordEncoder;
    final CommonUtil commonUtil;

    public UserService(
            UserRepository userRepository,
            PasswordEncoder passwordEncoder,
            CommonUtil commonUtil
    ) {
        this.userRepository = userRepository;
        this.passwordEncoder = passwordEncoder;
        this.commonUtil = commonUtil;
    }

    // WebSecurity 需要用户名登录，但是我们需要邮箱登录
    public UserDetails loadUserByUsername(String s) throws UsernameNotFoundException {
        var user = loadUserByEmail(s);
        if (user == null)
            throw new UsernameNotFoundException(String.format("%s do not exist!", s));
        return user;
    }

    public UserEntity loadUserByEmail(String email) {
        return userRepository.findByEmail(email);
    }

    public UserEntity loadUserById(Integer id) {
        var user = userRepository.findById(id);
        return user.orElse(null);
    }

    public UserEntity saveUser(UserEntity user) {
        return userRepository.save(user);
    }
}
