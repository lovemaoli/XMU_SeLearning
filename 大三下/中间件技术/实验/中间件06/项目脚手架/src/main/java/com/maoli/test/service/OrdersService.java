package com.maoli.test.service;


import com.maoli.test.entity.Orders;
import com.maoli.test.mapper.OrdersMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class OrdersService {
    @Autowired
    private OrdersMapper ordersMapper;

    public Orders findOrderById(Integer id){
        return ordersMapper.findById(id);
    }

    public void insert(Orders order){
        ordersMapper.insert(order);
    }
}
