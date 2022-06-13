package com.zzf.fluentchat.repository;

import com.zzf.fluentchat.entity.FriendEntity;
import org.springframework.data.jpa.repository.JpaRepository;

public interface MemberRepository extends JpaRepository<FriendEntity, Integer> {

}
