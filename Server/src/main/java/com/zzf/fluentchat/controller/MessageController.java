package com.zzf.fluentchat.controller;

import org.springframework.stereotype.Controller;

import java.util.Map;

@Controller
public class MessageController {
    public Map<String, Object> route(Map<String, Object> args, Map<String, Object> session) {
        return Map.of("test", "test");
    }
}
