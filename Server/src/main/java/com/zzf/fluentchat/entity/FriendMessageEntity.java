package com.zzf.fluentchat.entity;

import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import javax.persistence.*;
import java.util.Date;

@Entity(name = "t_friend_message")
public class FriendMessageEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "friend_message_seq")
    private Integer id;

    @OneToOne
    @JoinColumn(name = "from_user_id", nullable = false)
    @OnDelete(action = OnDeleteAction.CASCADE)
    private UserEntity from;

    @OneToOne
    @JoinColumn(name = "to_friend_id", nullable = false)
    @OnDelete(action = OnDeleteAction.CASCADE)
    private FriendEntity to;

    @Column(nullable = false)
    private String message = "";

    @Column(nullable = false)
    private Date sendDate = new Date();

    private Date receiveDate;

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

    public FriendEntity getTo() {
        return to;
    }

    public void setTo(FriendEntity to) {
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

    public Date getReceiveDate() {
        return receiveDate;
    }

    public void setReceiveDate(Date receiveDate) {
        this.receiveDate = receiveDate;
    }
}
