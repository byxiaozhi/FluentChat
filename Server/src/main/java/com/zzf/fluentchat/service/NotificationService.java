package com.zzf.fluentchat.service;

import com.zzf.fluentchat.entity.UserEntity;
import org.springframework.stereotype.Service;

import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

@Service
public class NotificationService {

    private final Map<Integer, Socket> onlineUsers = new HashMap<>();

    private TransportService transportService;

    public Map<Integer, Socket> getOnlineUsers() {
        return onlineUsers;
    }

    public TransportService getTransportService() {
        return transportService;
    }

    public void setTransportService(TransportService transportService) {
        this.transportService = transportService;
    }

    public void sendToUser(Integer userId, String name, Map<String, Object> args) {
        transportService.getSessions().values().stream()
                .filter(e -> e.containsKey("user"))
                .filter(e -> ((UserEntity) e.get("user")).getId().equals(userId))
                .map(e -> (Socket) e.get("socket"))
                .forEach(s -> transportService.dispatch(s, name, args));
    }
}
