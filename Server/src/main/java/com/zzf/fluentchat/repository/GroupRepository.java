package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.*;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface GroupRepository extends JpaRepository<GroupEntity, Integer> {
    @Query(value = "select t from group_info t where (t.name like %?1% or t.id = ?1) and t not in (select t1 from member t1 where t1.user = ?2)")
    Page<GroupEntity> searchByNameOrId(String name, UserEntity user, Pageable pageable);
}
