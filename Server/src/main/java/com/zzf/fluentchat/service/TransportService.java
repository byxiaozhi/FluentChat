package com.zzf.fluentchat.service;

import org.springframework.stereotype.Service;

import java.net.Socket;

@Service
public class TransportService {


    public void onConnect(Socket socket) {

    }

    public void onDisconnect(Socket socket) {

    }

    public void onMessage(Socket socket, String msg) {
        System.out.println(msg);
    }
}
