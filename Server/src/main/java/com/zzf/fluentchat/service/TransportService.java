package com.zzf.fluentchat.service;

import org.springframework.stereotype.Service;

import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;

@Service
public class TransportService {


    public void onConnect(Socket socket) {
        System.out.println("onConnect");
    }

    public void onDisconnect(Socket socket) {
        System.out.println("onDisconnect");
    }

    public void onMessage(Socket socket, String msg) {
        // 收到信息
    }

    public void postMessage(Socket socket, String msg) throws IOException {
        var out = socket.getOutputStream();
        out.write(ByteBuffer.allocate(4).putInt(msg.length()).array());
        out.write(msg.getBytes());
    }
}
