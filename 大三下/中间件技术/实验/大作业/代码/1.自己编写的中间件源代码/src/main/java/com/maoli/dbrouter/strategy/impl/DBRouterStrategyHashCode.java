package com.maoli.dbrouter.strategy.impl;

import com.maoli.dbrouter.DBContextHolder;
import com.maoli.dbrouter.DBRouterConfig;
import com.maoli.dbrouter.strategy.IDBRouterStrategy;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 哈希路由
 */
public class DBRouterStrategyHashCode implements IDBRouterStrategy {

    private Logger logger = LoggerFactory.getLogger(DBRouterStrategyHashCode.class);

    private DBRouterConfig dbRouterConfig;

    public DBRouterStrategyHashCode(DBRouterConfig dbRouterConfig) {
        this.dbRouterConfig = dbRouterConfig;
    }

    /**
     * 计算方式:
     * size = 库*表的数量
     * idx : 散列到的哪张表
     * dbIdx = idx / dbRouterConfig.getTbCount() + 1;
     * dbIdx : 用于计算哪个库,idx为0-size的值，除以表的数量 = 当前是几号库，又因库是从一号库开始算的，因此需要+1
     * tbIdx : idx - dbRouterConfig.getTbCount() * (dbIdx - 1);用于计算哪个表，
     * idx 可以理解为是第X张表，但是需要落地到是第几个库的第几个表
     * 例子：假设2库8表，idx为14，因此是第二个库的第6个表才是第14张表
     * (dbIdx - 1) 因为库是从1开始算的，因此这里需要-1
     * dbRouterConfig.getTbCount() * (dbIdx - 1) 是为了算出当前库前面的多少张表，也就是要跳过前面的这些表，
     * 然后来计算当前库中的表
     * @param dbKeyAttr 路由字段
     */
    @Override
    public void doRouter(String dbKeyAttr) {

        // 获取所有表
        int size = dbRouterConfig.getDbCount() * dbRouterConfig.getTbCount();

        // 扰动函数；在 JDK 的 HashMap 中，对于一个元素的存放，需要进行哈希散列。而为了让散列更加均匀，所以添加了扰动函数。
        int idx = (size - 1) & (dbKeyAttr.hashCode() ^ (dbKeyAttr.hashCode() >>> 16));

        // 库表索引；相当于是把一个长条的桶，切割成段，对应分库分表中的库编号和表编号
        // 获取对应的库，库是从1开始算的，因此要在此基础上+1
        int dbIdx = idx / dbRouterConfig.getTbCount() + 1;

        int tbIdx = idx - dbRouterConfig.getTbCount() * (dbIdx - 1);

        // 设置库表信息到上下文,String.format("%02d", dbIdx),数据不为两位的话则在前面补0,这里的策略主要和设置的库表名称有关
        // 例如: 库名称为test_01 那就写%02d。表名称user_001 对应%03d
        DBContextHolder.setDBKey(String.format("%02d", dbIdx));
        DBContextHolder.setTBKey(String.format("%03d", tbIdx));
        logger.debug("数据库路由 dbIdx：{} tbIdx：{}",  dbIdx, tbIdx);
    }


    @Override
    public void setDBKey(int dbIdx) {
        DBContextHolder.setDBKey(String.format("%02d", dbIdx));
    }

    @Override
    public void setTBKey(int tbIdx) {
        DBContextHolder.setTBKey(String.format("%03d", tbIdx));
    }

    @Override
    public int dbCount() {
        return dbRouterConfig.getDbCount();
    }

    @Override
    public int tbCount() {
        return dbRouterConfig.getTbCount();
    }

    @Override
    public void clear(){
        DBContextHolder.clearDBKey();
        DBContextHolder.clearTBKey();
    }

}
