package com.zzf.fluentchat.component;

import com.zzf.fluentchat.entity.*;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.Map;

@Component
public class EntityConverter {

    public Map<String, Object> convert(UserEntity user) {
        var map = new HashMap<String, Object>();
        map.put("userId", user.getId());
        map.put("nickName", user.getNickname());
        map.put("email", user.getEmail());
        return map;
    }

    public Map<String, Object> convert(FriendEntity friend) {
        var map = new HashMap<String, Object>();
        var user = friend.getFriend();
        map.put("userId", user.getId());
        map.put("nickName", user.getNickname());
        map.put("email", user.getEmail());
        map.put("alias", friend.getAlias());
        return map;
    }

    public Map<String, Object> convert(GroupEntity group) {
        var map = new HashMap<String, Object>();
        map.put("groupId", group.getId());
        map.put("name", group.getName());
        map.put("createDate", group.getCreateDate());
        return map;
    }

    public Map<String, Object> convert(MemberEntity member) {
        var map = new HashMap<String, Object>();
        var group = member.getGroup();
        map.put("groupId", group.getId());
        map.put("name", group.getName());
        map.put("createDate", group.getCreateDate());
        map.put("groupAlias", member.getGroupAlias());
        map.put("memberAlias", member.getMemberAlias());
        return map;
    }

    public Map<String, Object> convert(FriendMessageEntity friendMessage) {
        var map = new HashMap<String, Object>();
        map.put("from", convert(friendMessage.getFrom()));
        map.put("to", convert(friendMessage.getTo()));
        map.put("message", friendMessage.getMessage());
        map.put("sendDate", friendMessage.getSendDate());
        return map;
    }

    public Map<String, Object> convert(GroupMessageEntity groupMessage) {
        var map = new HashMap<String, Object>();
        map.put("from", convert(groupMessage.getFrom()));
        map.put("to", convert(groupMessage.getTo()));
        map.put("message", groupMessage.getMessage());
        map.put("sendDate", groupMessage.getSendDate());
        return map;
    }

    public Map<String, Object> convert(FriendRecentEntity friendRecent) {
        var map = new HashMap<String, Object>();
        map.put("to", convert(friendRecent.getTo()));
        map.put("message", friendRecent.getMessage());
        map.put("sendDate", friendRecent.getSendDate());
        return map;
    }

    public Map<String, Object> convert(GroupRecentEntity groupRecent) {
        var map = new HashMap<String, Object>();
        map.put("to", convert(groupRecent.getTo()));
        map.put("message", groupRecent.getMessage());
        map.put("sendDate", groupRecent.getSendDate());
        return map;
    }
}
