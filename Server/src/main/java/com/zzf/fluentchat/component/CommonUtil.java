package com.zzf.fluentchat.component;

import com.alibaba.fastjson.JSON;
import org.springframework.stereotype.Component;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Random;

@Component
public class CommonUtil {
    public String randomString(int length) {
        var chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        var random = new Random();
        var sb = new StringBuilder();
        for (var i = 0; i < length; i++)
            sb.append(chars.charAt(random.nextInt(chars.length())));
        return sb.toString();
    }

    public void response(HttpServletResponse resp, Object data) throws IOException {
        var text = JSON.toJSONString(data);
        resp.setContentType("application/json;charset=utf-8");
        var out = resp.getWriter();
        out.write(text);
        out.flush();
        out.close();
    }
}
