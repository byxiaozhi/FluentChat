package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.GroupEntity;
import org.springframework.data.jpa.repository.JpaRepository;

public interface GroupRepository extends JpaRepository<GroupEntity, Integer> {
    
}
