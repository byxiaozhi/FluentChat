package com.zzf.fluentchat.model;

import java.util.Map;

public class DispatchArgs {

    private String name;

    private Map<String, Object> args;

    public int getType() {
        return 1;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Map<String, Object> getArgs() {
        return args;
    }

    public void setArgs(Map<String, Object> args) {
        this.args = args;
    }

}
