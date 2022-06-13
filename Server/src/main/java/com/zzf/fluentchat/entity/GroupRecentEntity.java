package com.zzf.fluentchat.entity;

import javax.persistence.*;
import java.util.Date;

@Entity(name = "group_recent")
public class GroupRecentEntity {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @OneToOne
    @JoinColumn(name = "user_id", nullable = false)
    private UserEntity user;

    @OneToOne
    @JoinColumn(name = "group_id", nullable = false)
    private GroupEntity to;

    @Column(nullable = false)
    private Date sendDate = new Date();

    @OneToOne
    @JoinColumn(name = "message_id", nullable = false)
    private GroupMessageEntity message;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public UserEntity getUser() {
        return user;
    }

    public void setUser(UserEntity user) {
        this.user = user;
    }

    public GroupEntity getTo() {
        return to;
    }

    public void setTo(GroupEntity to) {
        this.to = to;
    }

    public GroupMessageEntity getMessage() {
        return message;
    }

    public void setMessage(GroupMessageEntity message) {
        this.message = message;
    }

    public Date getSendDate() {
        return sendDate;
    }

    public void setSendDate(Date sendDate) {
        this.sendDate = sendDate;
    }
}
