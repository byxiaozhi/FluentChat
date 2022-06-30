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

    @Query(value = "select t from t_friend_info t where t.user = ?1 and t.state = 1")
    Page<FriendEntity> findPending(UserEntity user, Pageable pageable);

    @Query(value = "select t from t_friend_info t where t.user = ?1 and t.friend = ?2 and t.state = 1")
    FriendEntity findPending(UserEntity user, UserEntity friend);

    @Query(value = "select t from t_friend_info t where t.user = ?1 and t.friend = ?2")
    FriendEntity find(UserEntity user, UserEntity friend);

    @Modifying
    @Transactional
    @Query(value = "delete from t_friend_info t where t.user = ?1 and t.friend = ?2")
    void deleteFriend(UserEntity user, UserEntity friend);

    @Modifying
    @Transactional
    @Query(value = "delete from t_friend_info t where t.user = ?1")
    void deleteAllFriend(UserEntity user);

    @Query(value = "select t1 from t_friend_info t1 where t1.user = ?1 and t1.state = 0 and 0 in (select t2.state from t_friend_info t2 where t2.user = t1.friend and t2.friend = ?1)")
    Page<FriendEntity> findNormal(UserEntity user, Pageable pageable);

    @Query(value = "select t from t_friend_info t where t.user = ?1 and t.friend=?2 and t.state = 0")
    FriendEntity findNormal(UserEntity user, UserEntity friendUser);
}
