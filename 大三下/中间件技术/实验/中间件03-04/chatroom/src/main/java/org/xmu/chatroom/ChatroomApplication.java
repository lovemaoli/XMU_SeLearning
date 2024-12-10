package org.xmu.chatroom;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.jms.JmsAutoConfiguration;
import org.springframework.jms.annotation.EnableJms;


@SpringBootApplication
@EnableJms
public class ChatroomApplication {


    public static void main(String[] args) {
        SpringApplication.run(ChatroomApplication.class, args);
    }

}
