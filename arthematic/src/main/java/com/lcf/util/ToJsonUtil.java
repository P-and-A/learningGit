package com.lcf.util;

import com.google.gson.Gson;

/**
 * @author liaochaofan
 * @date 2018/10/18 20:39
 */
public class ToJsonUtil {
    private static ToJsonUtil toJsonUtil = null;

    private ToJsonUtil() {
    }

    public String objectToJson(Object object){
        Gson gson = new Gson();
        return gson.toJson(object);
    }

    public static ToJsonUtil getToJsonUtil() {
        if(toJsonUtil != null){
            return toJsonUtil;
        }
        return new ToJsonUtil();
    }
}
