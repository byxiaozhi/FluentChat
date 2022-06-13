package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.entity.FriendRecentEntity;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;

public interface FriendRecentRepository extends JpaRepository<FriendRecentEntity, Integer> {

    @Query(value = "select t from friend_recent t where t.user=?1 order by t.sendDate desc")
    Page<FriendRecentEntity> findByUser(UserEntity user, Pageable pageable);

    @Modifying
    @Query(value = "delete from friend_recent t where t.user=?1 and t.to=?2")
    void deleteByFriend(UserEntity user, UserEntity friend);
}
