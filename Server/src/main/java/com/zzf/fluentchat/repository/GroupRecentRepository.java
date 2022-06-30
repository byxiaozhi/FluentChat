package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.GroupRecentEntity;
import com.zzf.fluentchat.entity.UserEntity;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface GroupRecentRepository extends JpaRepository<GroupRecentEntity, Integer> {
    @Query(value = "select t from t_group_recent t where t.user=?1 order by t.sendDate desc")
    Page<GroupRecentEntity> findByUser(UserEntity user, Pageable pageable);
}
