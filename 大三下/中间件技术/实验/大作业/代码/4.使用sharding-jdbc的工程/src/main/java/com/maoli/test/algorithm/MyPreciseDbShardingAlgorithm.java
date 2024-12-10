package com.maoli.test.algorithm;

import org.apache.shardingsphere.api.sharding.standard.PreciseShardingAlgorithm;
import org.apache.shardingsphere.api.sharding.standard.PreciseShardingValue;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Collection;

public class MyPreciseDbShardingAlgorithm implements PreciseShardingAlgorithm<Integer> {
    private final Logger logger = LoggerFactory.getLogger(this.getClass());

    @Override
    public String doSharding(Collection<String> collection, PreciseShardingValue<Integer> preciseShardingValue) {
        int dbNo = preciseShardingValue.getValue() % 2;

        for (String dbName : collection) {
            if (dbName.endsWith(dbNo + "")) {
                return dbName;
            }
        }

        throw new UnsupportedOperationException();
    }
}

//    CREATE TABLE orders_000 (
//        id INT PRIMARY KEY,
//        customer VARCHAR(255),
//    price DECIMAL(10, 2)
//);
//
//        CREATE TABLE orders_001 (
//        id INT PRIMARY KEY,
//        customer VARCHAR(255),
//        price DECIMAL(10, 2)
//        );
//
//        CREATE TABLE orders_002 (
//        id INT PRIMARY KEY,
//        customer VARCHAR(255),
//        price DECIMAL(10, 2)
//        );
//
//        CREATE TABLE orders_003 (
//        id INT PRIMARY KEY,
//        customer VARCHAR(255),
//        price DECIMAL(10, 2)
//        );