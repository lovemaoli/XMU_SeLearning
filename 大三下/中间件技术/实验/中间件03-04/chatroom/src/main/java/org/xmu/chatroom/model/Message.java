package org.xmu.chatroom.model;

import lombok.AllArgsConstructor;
import lombok.Data;


@Data
@AllArgsConstructor
public class Message {
    String sender;
    String content;
}
