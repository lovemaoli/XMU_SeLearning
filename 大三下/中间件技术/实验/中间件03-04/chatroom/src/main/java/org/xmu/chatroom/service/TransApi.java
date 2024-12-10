package org.xmu.chatroom.service;

import java.net.URI;
import java.util.HashMap;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.validation.ObjectError;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.util.UriComponentsBuilder;


import org.xmu.chatroom.util.MD5;

@Service
public class TransApi {
    private static final String TRANS_API_HOST = "http://api.fanyi.baidu.com/api/trans/vip/translate";

    @Value("${baidu_translate.appid}")
    private String appid;
    @Value("${baidu_translate.securityKey}")
    private String securityKey;

    private String defaultFrom = "auto";
    private String defaultTo = "zh";

    // 添加了一个无参构造器，不然无法注入这个bean，否则需要额外的配置。
    public TransApi() {}

    @Autowired
    private RestTemplate restTemplate;

    public TransApi(String appid, String securityKey) {
        this.appid = appid;
        this.securityKey = securityKey;
    }

    public void changeTranslate(){
        if(defaultTo.equals("zh")){defaultTo = "en";}
        else {defaultTo = "zh";}
    }

    public String getDefaultTo(){
        return this.defaultTo;
    }

    public String getTransResult(String query) {
        return getTransResult(query, defaultFrom, defaultTo);
    }

    public String getTransResult(String query, String from, String to) {
        Map<String, String> params = buildParams(query, from, to);
        MultiValueMap<String, String> requestParams = new LinkedMultiValueMap<>();
        requestParams.setAll(params);
        UriComponentsBuilder builder = UriComponentsBuilder.fromHttpUrl(TRANS_API_HOST);
        URI uri = builder.queryParams(requestParams).build().encode().toUri();  //  这里不能进行 encode 了，编码就错误了
        System.out.println("uri: " + uri);
        Object returnObj = restTemplate.getForObject(uri, Object.class);
        Map entity1 = (Map)returnObj;
        String transResult = entity1.get("trans_result").toString();
        transResult = transResult.substring(2, transResult.length() - 2);
        String result = "";
        for(int i = 0, p = 0; i < transResult.length(); ++i){
            if(transResult.charAt(i) == '='){
                p++;
            }
            if(p == 2){
                result = transResult.substring(i + 1);
                break;
            }
        }
        return result;
    }

    private Map<String, String> buildParams(String query, String from, String to) {
        Map<String, String> params = new HashMap<String, String>();
        params.put("q", query);
        params.put("from", from);
        params.put("to", to);

        params.put("appid", appid);

        // 随机数
        String salt = String.valueOf(System.currentTimeMillis());
        params.put("salt", salt);

        // 签名
        String src = appid + query + salt + securityKey; // 加密前的原文
        params.put("sign", MD5.md5(src));

        return params;
    }

}

