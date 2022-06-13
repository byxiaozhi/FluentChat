package com.zzf.fluentchat.entity;

import javax.persistence.*;
import java.util.Date;

@Entity(name = "user_message")
public class UserMessageEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @OneToOne
    @JoinColumn(name = "from_user_id", nullable = false)
    private UserEntity from;

    @OneToOne
    @JoinColumn(name = "to_user_id", nullable = false)
    private UserEntity to;

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

    public UserEntity getTo() {
        return to;
    }

    public void setTo(UserEntity to) {
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
