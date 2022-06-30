package com.zzf.fluentchat.entity;

import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import javax.persistence.*;
import java.util.Date;

@Entity(name = "group_message")
public class GroupMessageEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @OneToOne
    @JoinColumn(name = "from_user_id", nullable = false)
    @OnDelete(action = OnDeleteAction.CASCADE)
    private UserEntity from;

    @OneToOne
    @JoinColumn(name = "to_group_id", nullable = false)
    @OnDelete(action = OnDeleteAction.CASCADE)
    private GroupEntity to;

    @Column(nullable = false)
    private String message = "";

    @Column(nullable = false)
    private Date sendDate = new Date();

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public UserEntity getFrom() {
        return from;
    }

    public void setFrom(UserEntity from) {
        this.from = from;
    }

    public GroupEntity getTo() {
        return to;
    }

    public void setTo(GroupEntity to) {
        this.to = to;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public Date getSendDate() {
        return sendDate;
    }

    public void setSendDate(Date sendDate) {
        this.sendDate = sendDate;
    }
}
