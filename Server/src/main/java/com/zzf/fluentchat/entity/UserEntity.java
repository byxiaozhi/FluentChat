package com.zzf.fluentchat.entity;

import javax.persistence.*;
import java.util.Date;

@Entity(name = "user")
public class UserEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @Column(nullable = false)
    private String nickname;

    @Column(unique = true, nullable = false)
    private String email;

    @Column(nullable = false)
    private String password;

    @Column(nullable = false)
    private String role = "user";

    @Column(nullable = false)
    private Date createDate = new Date();

    @Column(nullable = false)
    private Date updateDate;
}
