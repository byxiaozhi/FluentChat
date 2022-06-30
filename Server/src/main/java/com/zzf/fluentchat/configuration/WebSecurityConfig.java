package com.zzf.fluentchat.configuration;

import com.zzf.fluentchat.component.CommonUtil;
import com.zzf.fluentchat.component.PasswordEncoder;
import com.zzf.fluentchat.model.Resp;
import com.zzf.fluentchat.service.UserService;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.authentication.*;
import org.springframework.security.config.Customizer;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.AuthenticationException;
import org.springframework.web.cors.CorsConfiguration;
import org.springframework.web.cors.CorsConfigurationSource;
import org.springframework.web.cors.UrlBasedCorsConfigurationSource;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    String[] whiteList = {
            "/api/user/signup",
            "/api/user/forget",
            "/api/public/**",
    };

    CommonUtil commonUtil;
    UserService userService;

    public WebSecurityConfig(CommonUtil commonUtil, UserService userService) {
        this.commonUtil = commonUtil;
        this.userService = userService;
    }

    protected void configure(
            AuthenticationManagerBuilder auth,
            PasswordEncoder passwordEncoder
    ) throws Exception {
        auth.userDetailsService(userService).passwordEncoder(passwordEncoder);
    }

    protected void configure(HttpSecurity http) throws Exception {
        http
                .authorizeRequests()
                .antMatchers(whiteList).permitAll()
                .anyRequest().authenticated()
                .and()
                .formLogin()
                .loginProcessingUrl("/api/user/login")
                .usernameParameter("email")
                .successHandler(this::loginSuccessHandler)
                .failureHandler(this::loginFailureHandler)
                .permitAll()
                .and()
                .rememberMe()
                .rememberMeParameter("rememberMe")
                .key("9AgyjU8q")
                .userDetailsService(userService)
                .and()
                .logout()
                .logoutUrl("/api/user/logout")
                .logoutSuccessHandler(this::logoutSuccessHandler)
                .permitAll()
                .and()
                .exceptionHandling()
                .authenticationEntryPoint(this::failureAuthenticationHandler)
                .and()
                .csrf()
                .disable()
                .cors(Customizer.withDefaults());
    }

    private void loginSuccessHandler(HttpServletRequest req, HttpServletResponse resp, Authentication auth) throws IOException {
        commonUtil.response(resp, new Resp(Resp.Code.SUCCESS, "登录成功"));
    }

    private void logoutSuccessHandler(HttpServletRequest req, HttpServletResponse resp, Authentication auth) throws IOException {
        commonUtil.response(resp, new Resp(Resp.Code.SUCCESS, "退出登录成功"));
    }

    private void loginFailureHandler(HttpServletRequest req, HttpServletResponse resp, AuthenticationException authException) throws IOException {
        if (authException instanceof InternalAuthenticationServiceException)
            commonUtil.response(resp, new Resp(Resp.Code.FAILURE, "邮箱不存在", "email"));
        else if (authException instanceof AccountExpiredException)
            commonUtil.response(resp, new Resp(Resp.Code.FAILURE, "账号过期", "email"));
        else if (authException instanceof DisabledException)
            commonUtil.response(resp, new Resp(Resp.Code.FAILURE, "账号不可用", "email"));
        else if (authException instanceof LockedException)
            commonUtil.response(resp, new Resp(Resp.Code.FAILURE, "账号被锁定", "email"));
        else if (authException instanceof BadCredentialsException)
            commonUtil.response(resp, new Resp(Resp.Code.FAILURE, "电子邮箱或密码错误", "password"));
        else if (authException instanceof CredentialsExpiredException)
            commonUtil.response(resp, new Resp(Resp.Code.FAILURE, "密码过期", "password"));
        else
            commonUtil.response(resp, new Resp(Resp.Code.FAILURE, "未知错误", "password"));
    }

    private void failureAuthenticationHandler(HttpServletRequest req, HttpServletResponse resp, AuthenticationException authException) throws IOException {
        commonUtil.response(resp, new Resp(Resp.Code.FAILURE, "无访问权限"));
    }

    @Bean
    CorsConfigurationSource corsConfigurationSource() {
        var configuration = new CorsConfiguration();
        configuration.setAllowedOriginPatterns(List.of("*"));
        configuration.addAllowedMethod("*");
        configuration.addAllowedHeader("*");
        configuration.setAllowCredentials(true);
        configuration.setMaxAge(3600L);
        var source = new UrlBasedCorsConfigurationSource();
        source.registerCorsConfiguration("/**", configuration);
        return source;
    }
}
