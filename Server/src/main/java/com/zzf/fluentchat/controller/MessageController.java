package com.zzf.fluentchat.controller;

import com.zzf.fluentchat.component.EntityConverter;
import com.zzf.fluentchat.entity.FriendMessageEntity;
import com.zzf.fluentchat.entity.FriendRecentEntity;
import com.zzf.fluentchat.entity.GroupMessageEntity;
import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.repository.*;
import com.zzf.fluentchat.service.NotificationService;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Stream;

@Controller
public class MessageController {

    final UserRepository userRepository;
    final FriendRepository friendRepository;
    final FriendMessageRepository friendMessageRepository;
    final FriendRecentRepository friendRecentRepository;
    final GroupRepository groupRepository;
    final GroupMessageRepository groupMessageRepository;
    final GroupRecentRepository groupRecentRepository;
    final MemberRepository memberRepository;
    final EntityConverter entityConverter;
    final NotificationService notificationService;

    public MessageController(
            FriendMessageRepository friendMessageRepository,
            UserRepository userRepository,
            FriendRepository friendRepository,
            FriendRecentRepository friendRecentRepository,
            GroupRepository groupRepository,
            GroupMessageRepository groupMessageRepository,
            GroupRecentRepository groupRecentRepository,
            MemberRepository memberRepository, EntityConverter entityConverter, NotificationService notificationService) {
        this.userRepository = userRepository;
        this.friendMessageRepository = friendMessageRepository;
        this.friendRepository = friendRepository;
        this.friendRecentRepository = friendRecentRepository;
        this.groupRepository = groupRepository;
        this.groupMessageRepository = groupMessageRepository;
        this.groupRecentRepository = groupRecentRepository;
        this.memberRepository = memberRepository;
        this.entityConverter = entityConverter;
        this.notificationService = notificationService;
    }

    public Map<String, Object> route(String action, Map<String, Object> args, Map<String, Object> session) throws Exception {
        return switch (action) {
            case "getFriendMessages" -> getFriendMessages(args, session);
            case "getGroupMessages" -> getGroupMessages(args, session);
            case "getRecent" -> getRecent(args, session);
            case "sendFriendMessage" -> sendFriendMessage(args, session);
            case "sendGroupMessage" -> sendGroupMessage(args, session);
            default -> throw new Exception("action does not exist");
        };
    }

    public Map<String, Object> getFriendMessages(Map<String, Object> args, Map<String, Object> session) {
        var friend_nullable = friendRepository.findById((int) args.get("friendId"));
        if (friend_nullable.isEmpty()) return Map.of("success", false, "message", "用户ID不存在");
        var user = (UserEntity) session.get("user");
        var friend = friend_nullable.get();
        var friendUser = friend.getFriend();
        var friendInverse = friendRepository.findNormal(friendUser, user);
        var page = PageRequest.of(0, 100);
        var messages1 = friendMessageRepository.findByFromAndTo(user, friend, page).get();
        var messages2 = friendMessageRepository.findByFromAndTo(friend.getFriend(), friendInverse, page).get();
        var messages = Stream.concat(messages1, messages2).sorted((a, b) -> b.getSendDate().compareTo(a.getSendDate())).limit(page.getPageSize()).map(entityConverter::convert).toList();
        return Map.of("messages", messages, "success", true, "message", "操作成功");
    }

    public Map<String, Object> getGroupMessages(Map<String, Object> args, Map<String, Object> session) {
        var group_nullable = groupRepository.findById((int) args.get("groupId"));
        if (group_nullable.isEmpty()) return Map.of("success", false, "message", "群ID不存在");
        var user = (UserEntity) session.get("user");
        var group = group_nullable.get();
        if (memberRepository.findByGroupAndUser(group, user).isEmpty())
            return Map.of("success", false, "message", "群ID不存在");
        var page = PageRequest.of(0, 100);
        var messages = groupMessageRepository.findByGroup(group, page).get().map(entityConverter::convert).toList();
        return Map.of("messages", messages, "success", true, "message", "操作成功");
    }

    public Map<String, Object> getRecent(Map<String, Object> args, Map<String, Object> session) {
        var user = (UserEntity) session.get("user");
        var page = PageRequest.of(0, 100);
        var friendRecent = friendRecentRepository.findByUser(user, page);
        var groupRecent = groupRecentRepository.findByUser(user, page);
        var recent = new ArrayList<Map<String, Object>>();
        for (var t : friendRecent) {
            var userMap = new HashMap<String, Object>();
            var toFriend = t.getTo();
            var toUser = toFriend.getUser();
            userMap.put("alias", toFriend.getAlias());
            userMap.put("nickName", toUser.getNickname());
            userMap.put("displayName", toFriend.getAlias().isEmpty() ? toFriend.getUser().getNickname() : toFriend.getAlias());
            userMap.put("userId", toUser.getId());
            var map = new HashMap<String, Object>();
            map.put("type", 0);
            map.put("toFriend", userMap);
            map.put("updateDate", t.getSendDate());
            map.put("lastMessage", t.getMessage());
            recent.add(map);
        }
        for (var t : groupRecent) {
            var userMap = new HashMap<String, Object>();
            var toGroup = t.getTo();
            var toMember = memberRepository.findByGroupAndUser(toGroup, user);
            if (toMember.isEmpty())
                continue;
            ;
            userMap.put("alias", toMember.get().getGroupAlias());
            userMap.put("name", toGroup.getName());
            userMap.put("displayName", toMember.get().getGroupAlias().isEmpty() ? toGroup.getName() : toMember.get().getGroupAlias());
            userMap.put("groupId", toGroup.getId());
            var map = new HashMap<String, Object>();
            map.put("type", 0);
            map.put("toGroup", userMap);
            map.put("updateDate", t.getSendDate());
            map.put("lastMessage", t.getMessage());
            recent.add(map);
        }
        var sortedRecent = recent.stream().sorted((a, b) -> ((Date) b.get("updateDate")).compareTo((Date) a.get("updateDate"))).toList();
        return Map.of("recent", sortedRecent, "success", true, "message", "操作成功");
    }

    public Map<String, Object> sendFriendMessage(Map<String, Object> args, Map<String, Object> session) {
        var friend_nullable = friendRepository.findById((int) args.get("friendId"));
        if (friend_nullable.isEmpty()) return Map.of("success", false, "message", "用户ID不存在");
        var user = (UserEntity) session.get("user");
        var friend = friend_nullable.get();
        var friendUser = friend.getFriend();
        var friendInverse = friendRepository.findNormal(friendUser, user);
        if (friendInverse == null)
            return Map.of("success", false, "message", "用户ID不存在");
        var message = new FriendMessageEntity();
        message.setFrom(user);
        message.setTo(friend);
        message.setMessage(args.get("message").toString());
        message = friendMessageRepository.save(message);
        var recent = new FriendRecentEntity();
        recent.setUser(user);
        recent.setTo(friend);
        recent.setMessage(message);
        friendRecentRepository.save(recent);
        var map = Map.of("from", entityConverter.convert(friendInverse), "message", message.getMessage());
        notificationService.sendToUser(friend.getFriend().getId(), "messageReceive", map);
        return Map.of("success", true, "message", "操作成功");
    }

    public Map<String, Object> sendGroupMessage(Map<String, Object> args, Map<String, Object> session) {
        var group_nullable = groupRepository.findById((int) args.get("groupId"));
        if (group_nullable.isEmpty()) return Map.of("success", false, "message", "群ID不存在");
        var user = (UserEntity) session.get("user");
        var group = group_nullable.get();
        var member = memberRepository.findByGroupAndUser(group, user);
        if (member.isEmpty())
            return Map.of("success", false, "message", "群ID不存在");
        var message = new GroupMessageEntity();
        message.setFrom(user);
        message.setTo(group);
        message.setMessage(args.get("message").toString());
        groupMessageRepository.save(message);
        var map = Map.of("from", entityConverter.convert(member.get()), "message", message.getMessage());
        for (var otherMember : memberRepository.findByGroup(group, Pageable.unpaged()).stream().filter(x -> !x.getId().equals(member.get().getId())).toList())
            notificationService.sendToUser(otherMember.getUser().getId(), "groupMessageReceive", map);
        return Map.of("success", true, "message", "操作成功");
    }
}
