package com.zzf.fluentchat.controller;

import org.springframework.stereotype.Controller;

import java.util.Map;

@Controller
public class FriendController {
    public Map<String, Object> route(String action, Map<String, Object> args, Map<String, Object> session) {
        return Map.of("test", "test");
    }
}
