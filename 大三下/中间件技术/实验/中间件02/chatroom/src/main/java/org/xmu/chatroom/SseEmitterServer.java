package org.xmu.chatroom;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.MediaType;
import org.springframework.web.servlet.mvc.method.annotation.SseEmitter;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.Consumer;


public class SseEmitterServer {

    private static final Logger logger = LoggerFactory.getLogger(SseEmitterServer.class);

    private static AtomicInteger count = new AtomicInteger(0);

    private static Map<String, SseEmitter> sseEmitterMap = new ConcurrentHashMap<>();

    public static SseEmitter connect(String employeeCode) {
        // 设置超时时间，0表示不过期。默认30秒，超过时间未完成会抛出异常：AsyncRequestTimeoutException
        SseEmitter sseEmitter = new SseEmitter(0L);
        // 注册回调
        sseEmitter.onCompletion(completionCallBack(employeeCode));
        sseEmitter.onError(errorCallBack(employeeCode));
        sseEmitter.onTimeout(timeoutCallBack(employeeCode));
        sseEmitterMap.put(employeeCode, sseEmitter);
        // 数量+1
        count.getAndIncrement();
        logger.info("创建新的sse连接，当前用户：{}", employeeCode);
        return sseEmitter;
    }

    public static void sendMessage(String employeeCode, String jsonMsg) {
        try {
            SseEmitter emitter = sseEmitterMap.get(employeeCode);
            if (emitter == null) {
                logger.warn("sse用户[{}]不在注册表，消息推送失败", employeeCode);
                return;
            }
            emitter.send(jsonMsg, MediaType.APPLICATION_JSON);
        } catch (IOException e) {
            logger.error("sse用户[{}]推送异常:{}", employeeCode, e.getMessage());
            removeUser(employeeCode);
        }
    }

    public static void batchSendMessage(String jsonMsg, List<String> employeeCodes) {
        employeeCodes.forEach(employeeCode -> sendMessage(jsonMsg, employeeCode));
    }

    public static void batchSendMessage(String jsonMsg) {
        sseEmitterMap.forEach((k, v) -> {
            try {
                v.send(jsonMsg, MediaType.APPLICATION_JSON);
            } catch (IOException e) {
                logger.error("用户[{}]推送异常:{}", k, e.getMessage());
                removeUser(k);
            }
        });
    }

    public static void removeUser(String employeeCode) {
        SseEmitter emitter = sseEmitterMap.get(employeeCode);
        if(emitter != null){
            emitter.complete();
        }
        sseEmitterMap.remove(employeeCode);
        // 数量-1
        count.getAndDecrement();
        logger.info("移除sse用户：{}", employeeCode);
    }

    public static List<String> getIds() {
        return new ArrayList<>(sseEmitterMap.keySet());
    }

    public static int getUserCount() {
        return count.intValue();
    }

    private static Runnable completionCallBack(String employeeCode) {
        return () -> {
            logger.info("结束sse用户连接：{}", employeeCode);
            removeUser(employeeCode);
        };
    }

    private static Runnable timeoutCallBack(String employeeCode) {
        return () -> {
            logger.info("连接sse用户超时：{}", employeeCode);
            removeUser(employeeCode);
        };
    }

    private static Consumer<Throwable> errorCallBack(String employeeCode) {
        return throwable -> {
            logger.info("sse用户连接异常：{}", employeeCode);
            removeUser(employeeCode);
        };
    }

}
