package com.zzf.fluentchat.entity;

import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import javax.persistence.*;
import java.util.Date;

@Entity(name = "t_friend_recent")
public class FriendRecentEntity {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "friend_recent_seq")
    private Integer id;

    @OneToOne
    @JoinColumn(name = "user_id")
    @OnDelete(action = OnDeleteAction.CASCADE)
    private UserEntity user;

    @OneToOne
    @JoinColumn(name = "friend_id")
    @OnDelete(action = OnDeleteAction.CASCADE)
    private FriendEntity to;

    @Column(nullable = false)
    private Date sendDate = new Date();

    @OneToOne
    @JoinColumn(name = "message_id", nullable = false)
    @OnDelete(action = OnDeleteAction.CASCADE)
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
