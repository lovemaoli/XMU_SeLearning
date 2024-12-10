package com.maoli.test.algorithm;

import org.apache.shardingsphere.api.sharding.standard.PreciseShardingAlgorithm;
import org.apache.shardingsphere.api.sharding.standard.PreciseShardingValue;

import java.util.Collection;

public class MyPreciseTableShardingAlgorithm implements PreciseShardingAlgorithm<Integer> {

    @Override
    public String doSharding(Collection<String> collection, PreciseShardingValue<Integer> preciseShardingValue) {
        int tableNo = preciseShardingValue.getValue() % 4;

        for (String dbName : collection) {
            if (dbName.endsWith(tableNo + "")) {
                return dbName;
            }
        }

        throw new UnsupportedOperationException();
    }
}
