package com.maoli.test.controller;


import com.maoli.test.entity.Orders;
import com.maoli.test.service.OrderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/order")
public class OrdersController {


    @Autowired
    private OrderService orderService;

    @GetMapping("/{id}")
    public Orders findOrderById(@PathVariable Integer id){
        return orderService.findOrderById(id);
    }

    @PostMapping
    public void insert(@RequestBody Orders order){
        orderService.insert(order);
    }



}
