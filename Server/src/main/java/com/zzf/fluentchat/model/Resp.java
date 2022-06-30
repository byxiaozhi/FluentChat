package com.zzf.fluentchat.model;

import com.alibaba.fastjson.JSON;
import org.springframework.validation.FieldError;

import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;

public class Resp {
    private Long code;
    private String message;
    private Object data;

    public enum Code {
        SUCCESS(0L), FAILURE(1L);

        private final Long value;

        Code(Long value) {
            this.value = value;
        }

        public Long getValue() {
            return value;
        }
    }

    public Resp(Code code, String message) {
        this.code = code.getValue();
        this.message = message;
    }

    public Resp(Code code, String message, Object data) {
        this.code = code.getValue();
        this.message = message;
        this.data = data;
    }

    public Resp(Code code, String message, List<FieldError> data) {
        this.code = code.getValue();
        this.message = message;
        this.data = data.stream().map(e ->
                Map.of("field", e.getField(), "message", Optional.ofNullable(e.getDefaultMessage()))
        ).collect(Collectors.toList());
    }

    public String toString() {
        return JSON.toJSONString(this);
    }

    public Long getCode() {
        return code;
    }

    public void setCode(Long code) {
        this.code = code;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public Object getData() {
        return data;
    }

    public void setData(Object data) {
        this.data = data;
    }
}
