package com.zzf.fluentchat.component;

import com.zzf.fluentchat.service.TransportService;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.HashSet;

@Component
public class SocketListener implements CommandLineRunner {

    private boolean listen = true;

    private final HashSet<Socket> clients = new HashSet<>();

    private final TransportService transportService;

    public SocketListener(TransportService transportService) {
        this.transportService = transportService;
    }

    @Override
    public void run(String... args) {
        new Thread(this::listenLoop).start();
    }

    private void listenLoop() {
        try (var serverSocket = new ServerSocket(8000)) {
            while (listen) {
                var client = serverSocket.accept();
                transportService.onConnect(client);
                clients.add(client);
                new Thread(() -> messageLoop(client)).start();
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void messageLoop(Socket client) {
        try (client) {
            var in = client.getInputStream();
            while (true) {
                var header = in.readNBytes(8);
                var buffer = ByteBuffer.wrap(header);
                if (buffer.getInt(0) != 854749800)
                    throw new Exception("识别码不正确");
                var length = buffer.getInt(1);
                var body = new String(in.readNBytes(length));
                transportService.onMessage(client, body);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            transportService.onDisconnect(client);
            clients.remove(client);
        }
    }

    public void setListen(boolean listen) {
        this.listen = listen;
    }

    public boolean getListen() {
        return this.listen;
    }

    public HashSet<Socket> getClients() {
        return clients;
    }
}
