package com.maoli.dbrouter.annotation;

import java.lang.annotation.*;

/**
 * 分库分表注解
 */
@Documented
@Retention(RetentionPolicy.RUNTIME)
@Target({ElementType.TYPE, ElementType.METHOD})
public @interface DBRouter {

    /** 分库分表字段 */
    String key() default "";

}


