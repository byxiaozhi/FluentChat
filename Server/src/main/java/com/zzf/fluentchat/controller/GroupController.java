package com.zzf.fluentchat.controller;

import com.zzf.fluentchat.component.EntityConverter;
import com.zzf.fluentchat.entity.GroupEntity;
import com.zzf.fluentchat.entity.MemberEntity;
import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.repository.GroupRepository;
import com.zzf.fluentchat.repository.MemberRepository;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;

import java.util.Map;

@Controller
public class GroupController {

    final GroupRepository groupRepository;
    final MemberRepository memberRepository;
    final EntityConverter entityConverter;

    public GroupController(GroupRepository groupRepository, MemberRepository memberRepository, EntityConverter entityConverter) {
        this.groupRepository = groupRepository;
        this.memberRepository = memberRepository;
        this.entityConverter = entityConverter;
    }

    public Map<String, Object> route(String action, Map<String, Object> args, Map<String, Object> session) throws Exception {
        return switch (action) {
            case "create" -> create(args, session);
            case "list" -> list(args, session);
            case "search" -> search(args, session);
            case "join" -> join(args, session);
            case "quit" -> quit(args, session);
            default -> throw new Exception("action does not exist");
        };
    }

    public Map<String, Object> create(Map<String, Object> args, Map<String, Object> session) {
        var group = new GroupEntity();
        group.setName(args.get("name").toString());
        group.setPassword(args.get("password").toString());
        groupRepository.save(group);
        var member = new MemberEntity();
        member.setGroup(group);
        member.setUser((UserEntity) session.get("user"));
        memberRepository.save(member);
        return Map.of("success", true, "message", "创建群聊成功");
    }

    public Map<String, Object> list(Map<String, Object> args, Map<String, Object> session) {
        var user = (UserEntity) session.get("user");
        var groups = memberRepository.findByUser(user, Pageable.unpaged()).get().sorted((a, b) -> {
            var str1 = a.getGroup().getName();
            var str2 = b.getGroup().getName();
            return str1.compareTo(str2);
        }).map(e -> {
            var map = entityConverter.convert(e);
            map.put("displayName", e.getGroup().getName());
            return map;
        }).toList();
        return Map.of("groups", groups, "success", true, "message", "操作成功");
    }

    public Map<String, Object> search(Map<String, Object> args, Map<String, Object> session) {
        var user = (UserEntity) session.get("user");
        var value = args.get("value").toString();
        var page = PageRequest.of(0, 100);
        var results = groupRepository.searchByNameOrId(value, user.getId(), page).get().map(entityConverter::convert).toList();
        return Map.of("results", results, "success", true, "message", "操作成功");
    }

    public Map<String, Object> join(Map<String, Object> args, Map<String, Object> session) {
        var user = (UserEntity) session.get("user");
        var groupId = (int)args.get("groupId");
        var password = args.get("password");
        var group = groupRepository.findById(groupId);
        if(group.isEmpty())
            return Map.of("success", false, "message", "群号不存在");
        if(!group.get().getPassword().equals(password))
            return Map.of("success", false, "message", "加群验证码错误");
        var member = new MemberEntity();
        member.setGroup(group.get());
        member.setUser(user);
        memberRepository.save(member);
        return Map.of("success", true, "message", "加入群聊成功");
    }

    public Map<String, Object> quit(Map<String, Object> args, Map<String, Object> session) {
        var user = (UserEntity) session.get("user");
        var groupId = (int)args.get("groupId");
        var group = groupRepository.findById(groupId);
        if(group.isEmpty())
            return Map.of("success", false, "message", "群号不存在");
        memberRepository.deleteMember(group.get(), user);
        if(memberRepository.findByGroup(group.get(), Pageable.unpaged()).stream().findAny().isEmpty())
            groupRepository.delete(group.get());
        return Map.of("success", true, "message", "退出群聊成功");
    }

}
