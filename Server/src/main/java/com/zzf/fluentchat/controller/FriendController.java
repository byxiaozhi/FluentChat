package com.zzf.fluentchat.controller;

import com.zzf.fluentchat.component.EntityConverter;
import com.zzf.fluentchat.entity.FriendEntity;
import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.repository.FriendRepository;
import com.zzf.fluentchat.repository.UserRepository;
import com.zzf.fluentchat.service.NotificationService;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;

import java.util.Map;

@Controller
public class FriendController {

    final FriendRepository friendRepository;
    final UserRepository userRepository;
    final EntityConverter entityConverter;
    final NotificationService notificationService;

    public FriendController(
            FriendRepository friendRepository,
            UserRepository userRepository,
            EntityConverter entityConverter,
            NotificationService notificationService) {
        this.friendRepository = friendRepository;
        this.userRepository = userRepository;
        this.entityConverter = entityConverter;
        this.notificationService = notificationService;
    }

    public Map<String, Object> route(String action, Map<String, Object> args, Map<String, Object> session) throws Exception {
        return switch (action) {
            case "listRequest" -> listRequest(args, session);
            case "listNormal" -> listNormal(args, session);
            case "search" -> search(args, session);
            case "addRequest" -> addRequest(args, session);
            case "addAccept" -> addAccept(args, session);
            case "addRefuse" -> addRefuse(args, session);
            case "delete" -> delete(args, session);
            default -> throw new Exception("action does not exist");
        };
    }

    public Map<String, Object> listRequest(Map<String, Object> args, Map<String, Object> session) {
        var user = (UserEntity) session.get("user");
        var page = PageRequest.of(0, 100);
        var requests = friendRepository.findPending(user, page).get().map(entityConverter::convert).toList();
        return Map.of("requests", requests, "success", true, "message", "操作成功");
    }

    public Map<String, Object> listNormal(Map<String, Object> args, Map<String, Object> session) {
        var user = (UserEntity) session.get("user");
        var friends = friendRepository.findNormal(user, Pageable.unpaged()).get().sorted((a, b) -> {
            var str1 = a.getAlias().isEmpty() ? a.getUser().getNickname() : a.getAlias();
            var str2 = b.getAlias().isEmpty() ? b.getUser().getNickname() : b.getAlias();
            return str1.compareTo(str2);
        }).map(e -> {
            var map = entityConverter.convert(e);
            map.put("displayName", e.getAlias().isEmpty() ? e.getFriend().getNickname() : e.getAlias());
            return map;
        }).toList();
        return Map.of("friends", friends, "success", true, "message", "操作成功");
    }

    public Map<String, Object> search(Map<String, Object> args, Map<String, Object> session) {
        var user = (UserEntity) session.get("user");
        var value = args.get("value").toString();
        var page = PageRequest.of(0, 100);
        var results = userRepository.searchByEmailOrNickname(value, page).get()
                .filter(e -> !e.getId().equals(user.getId())).map(e -> {
                    var map = entityConverter.convert(e);
                    var friendDirect = friendRepository.find(user, e);
                    var friendInverse = friendRepository.find(e, user);
                    map.put("stateDirect", friendDirect == null ? -1 : friendDirect.getState());
                    map.put("friendInverse", friendInverse == null ? -1 : friendInverse.getState());
                    return map;
                }).toList();
        return Map.of("results", results, "success", true, "message", "操作成功");
    }

    public Map<String, Object> addRequest(Map<String, Object> args, Map<String, Object> session) {
        var friend_nullable = userRepository.findById((int) args.get("userId"));
        if (friend_nullable.isEmpty()) return Map.of("success", false, "message", "用户ID不存在");
        var user = (UserEntity) session.get("user");
        var friend = friend_nullable.get();
        if (user.getId().equals(friend.getId()))
            return Map.of("success", false, "message", "不能添加自己");
        var friendDirect = new FriendEntity();
        friendDirect.setState(FriendEntity.State.normal);
        friendDirect.setUser(user);
        friendDirect.setFriend(friend);
        friendRepository.save(friendDirect);
        var friendInverse = new FriendEntity();
        friendInverse.setState(FriendEntity.State.pending);
        friendInverse.setUser(friend);
        friendInverse.setFriend(user);
        friendRepository.save(friendInverse);
        var map = Map.of("from", (Object) entityConverter.convert(friend));
        notificationService.sendToUser(friend.getId(), "addRequestReceived", map);
        return Map.of("success", true, "message", "添加成功");
    }

    public Map<String, Object> addAccept(Map<String, Object> args, Map<String, Object> session) {
        var friend_nullable = userRepository.findById((int) args.get("userId"));
        if (friend_nullable.isEmpty()) return Map.of("success", false, "message", "用户ID不存在");
        var user = (UserEntity) session.get("user");
        var friend = friend_nullable.get();
        var friendDirect = friendRepository.findPending(user, friend);
        var friendInverse = friendRepository.findNormal(friend, user);
        friendDirect.setState(FriendEntity.State.normal);
        friendInverse.setState(FriendEntity.State.normal);
        friendRepository.save(friendDirect);
        friendRepository.save(friendInverse);
        var map = Map.of("from", (Object) entityConverter.convert(friend));
        notificationService.sendToUser(friend.getId(), "addRequestAccepted", map);
        return Map.of("success", true, "message", "接受成功");
    }

    public Map<String, Object> addRefuse(Map<String, Object> args, Map<String, Object> session) {
        var friend_nullable = userRepository.findById((int) args.get("userId"));
        if (friend_nullable.isEmpty()) return Map.of("success", false, "message", "用户ID不存在");
        var user = (UserEntity) session.get("user");
        var friend = friend_nullable.get();
        friendRepository.deleteFriend(user, friend);
        friendRepository.deleteFriend(friend, user);
        var map = Map.of("from", (Object) entityConverter.convert(friend));
        notificationService.sendToUser(friend.getId(), "addRequestRefuse", map);
        return Map.of("success", true, "message", "操作成功");
    }

    public Map<String, Object> delete(Map<String, Object> args, Map<String, Object> session) {
        return addRefuse(args, session);
    }
}
