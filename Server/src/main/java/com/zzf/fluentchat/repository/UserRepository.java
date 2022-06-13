package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.UserEntity;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface UserRepository extends JpaRepository<UserEntity, Integer> {

    UserEntity findByEmail(String email);

    @Query(value = "select t from user t where t.email like %?1% or t.nickname like %?1%")
    Page<UserEntity> searchByEmailOrNickname(String value, Pageable pageable);
}
