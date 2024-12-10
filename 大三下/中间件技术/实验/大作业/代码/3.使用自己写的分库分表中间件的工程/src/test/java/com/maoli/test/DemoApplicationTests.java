package com.maoli.test;

import com.maoli.dbrouter.strategy.impl.DBRouterStrategyHashCode;
import com.maoli.test.entity.Orders;
import com.maoli.test.mapper.OrdersSplitTableMapper;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.transaction.support.TransactionTemplate;

import javax.annotation.Resource;

@SpringBootTest
class DemoApplicationTests {

    @Autowired
    private OrdersSplitTableMapper ordersSplitTableMapper;

    @Test
    void test1() {
        for (int i=1;i<=10;i++){
            Orders order=new Orders(i,"hx",10);
            // 分库分表
            ordersSplitTableMapper.insert(order);
        }
    }

    @Test
    void test2() {
        Orders order=ordersSplitTableMapper.findById(new Orders(7));
        System.out.println(order.getId()==7);
        System.out.println(order.getCustomer().equals("hx"));
        System.out.println(order.getPrice()==10);
    }


    @Resource
    TransactionTemplate transactionTemplate;

    @Resource
    DBRouterStrategyHashCode dbRouterStrategyHashCode;

    /**
     * 在一个事务下切换数据源会导致事务失效,
     * 因此需要在进入事务前设置数据源，并且把调用的dao层方法去除DBRouter注解
     * @return
     */
    public int t(){
        dbRouterStrategyHashCode.doRouter("xx");
        return transactionTemplate.execute(status->{
            //User user = new User(5, "hx", "123");
            // 假设这里分库分表
            //userMapper.insert(user);

            status.setRollbackOnly();
            return 1;
        });
    }
}
