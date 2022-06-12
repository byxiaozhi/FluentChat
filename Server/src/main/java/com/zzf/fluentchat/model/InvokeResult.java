package com.zzf.fluentchat.model;

import java.util.Map;

public class InvokeResult {

    private int id;

    private int code;

    private Map<String, Object> results;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public Map<String, Object> getResults() {
        return results;
    }

    public void setResults(Map<String, Object> results) {
        this.results = results;
    }

    public int getType() {
        return 0;
    }
}
