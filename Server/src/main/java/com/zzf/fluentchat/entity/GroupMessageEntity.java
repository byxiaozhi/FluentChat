package com.zzf.fluentchat.entity;

import javax.persistence.*;
import java.util.Date;

@Entity(name = "group_message")
public class GroupMessageEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @OneToOne
    @JoinColumn(name = "from_user_id", nullable = false)
    private UserEntity from;

    @OneToOne
    @JoinColumn(name = "to_group_id", nullable = false)
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
}
