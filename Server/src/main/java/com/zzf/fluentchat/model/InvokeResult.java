package com.zzf.fluentchat.model;

import java.util.Map;

public class InvokeResult {

    private int sessionId;

    private int code;

    private Map<String, Object> results;

    public int getSessionId() {
        return sessionId;
    }

    public void setSessionId(int sessionId) {
        this.sessionId = sessionId;
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
