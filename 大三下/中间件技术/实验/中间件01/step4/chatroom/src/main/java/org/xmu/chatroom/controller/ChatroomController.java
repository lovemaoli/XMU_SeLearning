package org.xmu.chatroom.controller;

import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.method.annotation.SseEmitter;
import org.xmu.chatroom.SseEmitterServer;
import org.xmu.chatroom.model.Message;
import org.xmu.chatroom.service.ChatRoom;

import javax.jms.JMSException;
import java.util.ArrayList;

@RestController
@CrossOrigin
public class ChatroomController {

    ChatRoom chatRoom = new ChatRoom();

    @GetMapping("/user/list")
    @CrossOrigin
    Object listUsers() {
        return new ArrayList<>(chatRoom.getUserMap().keySet());
    }

    @PostMapping("/user/connect")
    @CrossOrigin
    Object connectWithUser(@RequestParam String sender, @RequestParam String receiver) {
        try {
            chatRoom.getUserMap().get(sender).connect(receiver);
            return "success";
        } catch (JMSException exception) {
            exception.printStackTrace();
            return null;
        }
    }

    @GetMapping("/group/list")
    @CrossOrigin
    Object listGroups() {
        return new ArrayList<>(chatRoom.getGroupMap().keySet());
    }

    @PostMapping("/group/enter")
    @CrossOrigin
    Object enterGroup(@RequestParam String user, @RequestParam String group) {
        try {
            chatRoom.getUserMap().get(user).enterGroup(group);
            return "success";
        } catch (JMSException exception) {
            exception.printStackTrace();
            return null;
        }
    }

    @PostMapping("/group/connect")
    @CrossOrigin
    Object connectWithGroup(@RequestParam String user, @RequestParam String group) {
        try {
            chatRoom.getUserMap().get(user).connectWithGroup(group);
            return "success";
        } catch (JMSException exception) {
            exception.printStackTrace();
            return null;
        }
    }

    @PostMapping("/message/send")
    @CrossOrigin
    Object sendMessage(@RequestBody Message message) {
        var userMap = chatRoom.getUserMap();
        var sender = userMap.get(message.getSender());
        try {
            sender.sendMessage(message.getContent());
            return "success";
        } catch (JMSException exception) {
            exception.printStackTrace();
            return null;
        }
    }

    @GetMapping("/sse/connect")
    @CrossOrigin
    public SseEmitter connect(@RequestParam String uname) {
        var user = chatRoom.getUserMap().get(uname);
        if (user == null) {
            try {
                chatRoom.createUser(uname);
            } catch (Exception e) {
                e.printStackTrace();
                return null;
            }
        }
        return SseEmitterServer.connect(uname);
    }

    @GetMapping("/sse/close")
    @CrossOrigin
    public void disconnect(@RequestParam String uname) {
        chatRoom.getUserMap().remove(uname);
        SseEmitterServer.removeUser(uname);
    }
}
