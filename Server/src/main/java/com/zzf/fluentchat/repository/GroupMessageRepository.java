package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.GroupEntity;
import com.zzf.fluentchat.entity.GroupMessageEntity;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface GroupMessageRepository extends JpaRepository<GroupMessageEntity, Integer> {
    @Query(value = "select t from group_message t where t.to = ?1 order by t.sendDate desc")
    Page<GroupMessageEntity> findByGroup(GroupEntity group, Pageable pageable);
}
