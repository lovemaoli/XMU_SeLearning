package com.maoli.test;

import com.maoli.test.entity.Orders;
import com.maoli.test.mapper.OrdersMapper;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class DemoApplicationTests {

    @Autowired
    OrdersMapper ordersMapper;

    @Test
    void test1() {
        for (int i = 11; i <= 100; i++) {
            Orders order = new Orders(i, "maoli", 10);
            // 不分库分表
            ordersMapper.insert(order);
        }
    }

}
