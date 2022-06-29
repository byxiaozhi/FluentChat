package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.*;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.Optional;

public interface MemberRepository extends JpaRepository<MemberEntity, Integer> {

    @Query(value = "select t from member t where t.group = ?1")
    Page<MemberEntity> findByGroup(GroupEntity group, Pageable pageable);

    @Query(value = "select t from member t where t.group = ?1 and t.user=?2")
    MemberEntity findByGroupAndUser(GroupEntity group, UserEntity user);

    @Query(value = "select t from member t where t.group = ?1 and t.user = ?2")
    Optional<MemberEntity> memberExist(GroupEntity group, UserEntity user);

    @Query(value = "select t from member t where t.user = ?1")
    Page<MemberEntity> findByUser(UserEntity user, Pageable pageable);
}
