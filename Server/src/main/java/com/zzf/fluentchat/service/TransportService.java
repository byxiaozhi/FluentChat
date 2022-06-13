package com.zzf.fluentchat.service;

import com.alibaba.fastjson2.JSON;
import com.zzf.fluentchat.controller.*;
import com.zzf.fluentchat.model.DispatchArgs;
import com.zzf.fluentchat.model.InvokeResult;
import com.zzf.fluentchat.model.RemoteInvoke;
import org.springframework.stereotype.Service;

import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

@Service
public class TransportService {

    final MainController mainController;

    final UserController userController;

    final MessageController messageController;

    final GroupController groupController;

    final FriendController friendController;

    final Map<Socket, Map<String, Object>> sessions = new HashMap<>();

    public TransportService(
            MainController mainController,
            UserController userController,
            MessageController messageController, GroupController groupController, FriendController friendController) {
        this.mainController = mainController;
        this.userController = userController;
        this.messageController = messageController;
        this.groupController = groupController;
        this.friendController = friendController;
    }

    public Map<String, Object> getSession(Socket socket) {
        return sessions.get(socket);
    }

    public void onConnect(Socket socket) {
        sessions.put(socket, new HashMap<>());
    }

    public void onDisconnect(Socket socket) {
        sessions.remove(socket);
    }

    public void onMessage(Socket socket, String msg) {
        System.out.println(msg);
        var args = JSON.parseObject(msg, RemoteInvoke.class);
        try {
            resolve(socket, args.getId(), route(socket, args));
        } catch (Exception ex) {
            ex.printStackTrace();
            reject(socket, args.getId(), Map.of("msg", ex.getMessage()));
        }
    }

    private Map<String, Object> route(Socket socket, RemoteInvoke args) throws Exception {
        var action = args.getAction();
        return switch (args.getController().toLowerCase()) {
            case "main" -> mainController.route(action, args.getArgs(), sessions.get(socket));
            case "user" -> userController.route(action, args.getArgs(), sessions.get(socket));
            case "message" -> messageController.route(action, args.getArgs(), sessions.get(socket));
            case "group" -> groupController.route(action, args.getArgs(), sessions.get(socket));
            case "friend" -> friendController.route(action, args.getArgs(), sessions.get(socket));
            default -> throw new Exception("controller does not exist");
        };
    }

    private void resolve(Socket socket, int id, Map<String, Object> results) {
        respond(socket, id, 0, results);
    }

    private void reject(Socket socket, int id, Map<String, Object> results) {
        respond(socket, id, 1, results);
    }

    private void respond(Socket socket, int id, int code, Map<String, Object> results) {
        try {
            postMessage(socket, JSON.toJSONString(new InvokeResult() {{
                setId(id);
                setCode(code);
                setResults(results);
            }}));
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public void dispatch(Socket socket, String name, Map<String, Object> args) {
        try {
            postMessage(socket, JSON.toJSONString(new DispatchArgs() {{
                setName(name);
                setArgs(args);
            }}));
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void postMessage(Socket socket, String msg) throws IOException {
        System.out.println(msg);
        var out = socket.getOutputStream();
        var bytes = msg.getBytes(StandardCharsets.UTF_8);
        out.write(ByteBuffer.allocate(4).putInt(bytes.length).array());
        out.write(bytes);
    }
}
