package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.FriendEntity;
import com.zzf.fluentchat.entity.UserEntity;
import com.zzf.fluentchat.entity.FriendMessageEntity;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface FriendMessageRepository extends JpaRepository<FriendMessageEntity, Integer> {

    @Query(value = "select t from t_friend_message t where t.from = ?1 and t.to = ?2 order by t.sendDate desc")
    Page<FriendMessageEntity> findByFromAndTo(UserEntity from, FriendEntity to, Pageable pageable);
}
