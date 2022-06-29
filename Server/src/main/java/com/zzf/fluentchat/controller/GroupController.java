package com.zzf.fluentchat.controller;

import com.zzf.fluentchat.component.EntityConverter;
import com.zzf.fluentchat.entity.GroupEntity;
import com.zzf.fluentchat.entity.MemberEntity;
import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.repository.GroupRepository;
import com.zzf.fluentchat.repository.MemberRepository;
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
            map.put("displayName", e.getName());
            return map;
        }).toList();;
        return Map.of("groups", groups, "success", true, "message", "操作成功");
    }

    public Map<String, Object> search(Map<String, Object> args, Map<String, Object> session) {
        return null;
    }

    public Map<String, Object> join(Map<String, Object> args, Map<String, Object> session) {
        return null;
    }

    public Map<String, Object> quit(Map<String, Object> args, Map<String, Object> session) {
        return null;
    }

}
