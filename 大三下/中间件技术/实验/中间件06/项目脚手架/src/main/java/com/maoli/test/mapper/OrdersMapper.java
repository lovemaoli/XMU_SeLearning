package com.maoli.test.mapper;

import com.maoli.test.entity.Orders;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface OrdersMapper {

    void insert(Orders order);

    Orders findById(Integer id);

}
