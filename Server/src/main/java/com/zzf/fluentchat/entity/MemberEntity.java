package com.zzf.fluentchat.entity;

import javax.persistence.*;

@Entity(name = "member")
@Table(uniqueConstraints = {
        @UniqueConstraint(name = "uc_member_group", columnNames = {"group_id", "user_id"})
})
public class MemberEntity {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @ManyToOne
    private GroupEntity group;

    @OneToOne
    @JoinColumn(name = "user_id", nullable = false)
    private UserEntity user;

    @Column(nullable = false)
    private String groupAlias = "";

    @Column(nullable = false)
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
        return groupAlias;
    }

    public void setGroupAlias(String groupAlias) {
        this.groupAlias = groupAlias;
    }

    public String getMemberAlias() {
        return memberAlias;
    }

    public void setMemberAlias(String memberAlias) {
        this.memberAlias = memberAlias;
    }
}
