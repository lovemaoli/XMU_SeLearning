package com.maoli.test.mapper;


import com.maoli.dbrouter.annotation.DBRouter;
import com.maoli.dbrouter.annotation.DBRouterStrategy;
import com.maoli.test.entity.Orders;
import org.apache.ibatis.annotations.Mapper;


@Mapper
@DBRouterStrategy(splitTable = true) // 分表
public interface OrdersSplitTableMapper {

    // 分库
    @DBRouter(key = "id")
    void insert(Orders order);

    // 分库
    @DBRouter(key = "id")
    Orders findById(Orders order);
}
