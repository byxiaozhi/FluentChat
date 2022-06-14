package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.FriendEntity;
import com.zzf.fluentchat.entity.UserEntity;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;

import javax.transaction.Transactional;

public interface FriendRepository extends JpaRepository<FriendEntity, Integer> {

    @Query(value = "select t from friend_info t where t.user = ?1 and t.state = 1")
    Page<FriendEntity> findPending(UserEntity user, Pageable pageable);

    @Query(value = "select t from friend_info t where t.user = ?1 and t.friend = ?2 and t.state = 1")
    FriendEntity findPending(UserEntity user, UserEntity friend);

    @Query(value = "select t from friend_info t where t.user = ?1 and t.friend = ?2")
    FriendEntity find(UserEntity user, UserEntity friend);

    @Modifying
    @Transactional
    @Query(value = "delete from friend_info t where t.user = ?1 and t.friend = ?2")
    void deleteFriend(UserEntity user, UserEntity friend);

    @Query(value = "select t from friend_info t where t.user = ?1 and t.state = 0")
    Page<FriendEntity> findNormal(UserEntity user, Pageable pageable);

    @Query(value = "select t from friend_info t where t.user = ?1 and t.friend=?2 and t.state = 0")
    FriendEntity findNormal(UserEntity user, UserEntity friendUser);
}
