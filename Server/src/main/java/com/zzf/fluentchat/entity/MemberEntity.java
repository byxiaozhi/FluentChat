package com.zzf.fluentchat.entity;

import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import javax.persistence.*;

@Entity(name = "t_member")
@Table(uniqueConstraints = {
        @UniqueConstraint(name = "uc_member_group", columnNames = {"group_id", "user_id"})
})
public class MemberEntity {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "member_seq")
    private Integer id;

    @ManyToOne
    @OnDelete(action = OnDeleteAction.CASCADE)
    private GroupEntity group;

    @OneToOne
    @JoinColumn(name = "user_id", nullable = false)
    @OnDelete(action = OnDeleteAction.CASCADE)
    private UserEntity user;

    @Column(nullable = true)
    private String groupAlias = "";

    @Column(nullable = true)
    private String memberAlias = "";

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public GroupEntity getGroup() {
        return group;
    }

    public void setGroup(GroupEntity group) {
        this.group = group;
    }

    public UserEntity getUser() {
        return user;
    }

    public void setUser(UserEntity user) {
        this.user = user;
    }

    public String getGroupAlias() {
        return groupAlias == null ? "" : groupAlias;
    }

    public void setGroupAlias(String groupAlias) {
        this.groupAlias = groupAlias;
    }

    public String getMemberAlias() {
        return memberAlias == null ? "" : memberAlias;
    }

    public void setMemberAlias(String memberAlias) {
        this.memberAlias = memberAlias;
    }
}
