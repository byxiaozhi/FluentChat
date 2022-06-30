package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.UserEntity;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface UserRepository extends JpaRepository<UserEntity, Integer> {

    UserEntity findByEmail(String email);

    @Query(value = "select t from t_user t where t.email like %?1% or t.nickname like %?1%")
    Page<UserEntity> searchByEmailOrNickname(String value, Pageable pageable);

    @Query("select u from t_user u order by u.id desc")
    List<UserEntity> selectAll(Pageable pageable);

    @Query("select u from t_user u where u.email like %?1% or u.nickname like %?1% order by u.id desc")
    List<UserEntity> selectAll(Pageable pageable, String query);
}
