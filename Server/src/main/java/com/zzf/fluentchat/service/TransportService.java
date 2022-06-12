package com.zzf.fluentchat.service;

import com.alibaba.fastjson2.JSON;
import com.zzf.fluentchat.controller.MainController;
import com.zzf.fluentchat.controller.MessageController;
import com.zzf.fluentchat.controller.UserController;
import com.zzf.fluentchat.model.DispatchArgs;
import com.zzf.fluentchat.model.InvokeResult;
import com.zzf.fluentchat.model.RemoteInvoke;
import org.springframework.stereotype.Service;

import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;

@Service
public class TransportService {

    final MainController mainController;

    final UserController userController;

    final MessageController messageController;

    final Map<Socket, Map<String, Object>> sessions = new HashMap<>();

    public TransportService(
            MainController mainController,
            UserController userController,
            MessageController messageController) {
        this.mainController = mainController;
        this.userController = userController;
        this.messageController = messageController;
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
        var args = JSON.parseObject(msg, RemoteInvoke.class);
        try {
            resolve(socket, args.getSessionId(), route(socket, args));
        } catch (Exception ex) {
            reject(socket, args.getSessionId(), Map.of("msg", ex.getMessage()));
        }
    }

    private Map<String, Object> route(Socket socket, RemoteInvoke args) throws Exception {
        return switch (args.getController().toLowerCase()) {
            case "main" -> mainController.route(args.getArgs(), sessions.get(socket));
            case "user" -> userController.route(args.getArgs(), sessions.get(socket));
            case "message" -> messageController.route(args.getArgs(), sessions.get(socket));
            default -> throw new Exception("controller does not exist");
        };
    }

    private void resolve(Socket socket, int sessionId, Map<String, Object> results) {
        respond(socket, sessionId, 0, results);
    }

    private void reject(Socket socket, int sessionId, Map<String, Object> results) {
        respond(socket, sessionId, 1, results);
    }

    private void respond(Socket socket, int sessionId, int code, Map<String, Object> results) {
        try {
            postMessage(socket, JSON.toJSONString(new InvokeResult() {{
                setSessionId(sessionId);
                setCode(code);
                setResults(results);
            }}));
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public void Dispatch(Socket socket, String name, Map<String, Object> args) {
        try {
            postMessage(socket, JSON.toJSONString(new DispatchArgs(){{
                setName(name);
                setArgs(args);
            }}));
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void postMessage(Socket socket, String msg) throws IOException {
        var out = socket.getOutputStream();
        out.write(ByteBuffer.allocate(4).putInt(msg.length()).array());
        out.write(msg.getBytes());
    }
}
