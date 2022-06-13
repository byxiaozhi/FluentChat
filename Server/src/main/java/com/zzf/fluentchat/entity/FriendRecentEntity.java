package com.zzf.fluentchat.entity;

import javax.persistence.*;
import java.util.Date;

@Entity(name = "friend_recent")
public class FriendRecentEntity {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @OneToOne
    @JoinColumn(name = "user_id", nullable = false)
    private UserEntity user;

    @OneToOne
    @JoinColumn(name = "friend_id", nullable = false)
    private FriendEntity to;

    @Column(nullable = false)
    private Date sendDate = new Date();

    @OneToOne
    @JoinColumn(name = "message_id", nullable = false)
    private FriendMessageEntity message;

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

    public FriendEntity getTo() {
        return to;
    }

    public void setTo(FriendEntity to) {
        this.to = to;
    }

    public FriendMessageEntity getMessage() {
        return message;
    }

    public void setMessage(FriendMessageEntity message) {
        this.message = message;
    }

    public Date getSendDate() {
        return sendDate;
    }

    public void setSendDate(Date sendDate) {
        this.sendDate = sendDate;
    }
}
