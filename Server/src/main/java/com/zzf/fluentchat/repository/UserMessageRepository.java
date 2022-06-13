package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.UserMessageEntity;
import org.apache.catalina.User;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface UserMessageRepository extends JpaRepository<UserMessageEntity, Integer> {

    @Query(value = "select t from user_message t where t.to = ?1 or t.from = ?1 order by t.sendDate desc")
    Page<UserMessageEntity> findByUser(User user, Pageable pageable);
}
