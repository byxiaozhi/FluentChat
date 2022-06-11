package com.zzf.fluentchat.service;

import org.springframework.stereotype.Service;

import java.net.Socket;

@Service
public class TransportService {


    public void onConnect(Socket socket) {
        System.out.println("onConnect");
    }

    public void onDisconnect(Socket socket) {
        System.out.println("onDisconnect");
    }

    public void onMessage(Socket socket, String msg) {
        System.out.println(msg);
    }
}
