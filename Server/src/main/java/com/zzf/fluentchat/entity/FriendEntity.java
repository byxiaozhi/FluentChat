package com.zzf.fluentchat.entity;

import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import javax.persistence.*;

@Entity(name = "t_friend_info")
@Table(uniqueConstraints = {
        @UniqueConstraint(name = "uc_friend_user", columnNames = {"user_id", "friend_id"})
})
public class FriendEntity {

    public enum State {
        normal(0),
        pending(1),
        black(2);

        final int index;

        State(int index) {
            this.index = index;
        }
    }

    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE, generator = "friend_seq")
    private Integer id;

    @ManyToOne
    @JoinColumn(name = "user_id", nullable = false)
    @OnDelete(action = OnDeleteAction.CASCADE)
    private UserEntity user;

    @OneToOne
    @JoinColumn(name = "friend_id", nullable = false)
    @OnDelete(action = OnDeleteAction.CASCADE)
    private UserEntity friend;

    @Column(nullable = true)
    private String alias = "";

    @Column(nullable = false)
    private int state;

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

    public UserEntity getFriend() {
        return friend;
    }

    public void setFriend(UserEntity friend) {
        this.friend = friend;
    }

    public String getAlias() {
        return alias == null ? "" : alias;
    }

    public void setAlias(String alias) {
        this.alias = alias;
    }

    public int getState() {
        return state;
    }

    public void setState(State state) {
        this.state = state.index;
    }

    public void setState(int state) {
        this.state = state;
    }
}
