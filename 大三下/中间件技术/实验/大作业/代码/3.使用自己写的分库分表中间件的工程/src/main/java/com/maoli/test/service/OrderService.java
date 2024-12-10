package com.maoli.test.service;


import com.maoli.test.entity.Orders;
import com.maoli.test.mapper.OrdersSplitTableMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class OrderService {
    @Autowired
    private OrdersSplitTableMapper orderMapper;

    public Orders findOrderById(Integer id){
        return orderMapper.findById(new Orders(id));
    }

    public void insert(Orders order){
        orderMapper.insert(order);
    }
}
