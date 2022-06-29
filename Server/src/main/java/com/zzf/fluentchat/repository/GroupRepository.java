package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.*;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface GroupRepository extends JpaRepository<GroupEntity, Integer> {

}
