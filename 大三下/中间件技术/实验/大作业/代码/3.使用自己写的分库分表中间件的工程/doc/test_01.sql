/*
Navicat MySQL Data Transfer

Source Server         : 本地数据库
Source Server Version : 50536
Source Host           : 127.0.0.1:3306
Source Database       : test_01

Target Server Type    : MYSQL
Target Server Version : 50536
File Encoding         : 65001

Date: 2023-04-19 18:36:29
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for orders_000
-- ----------------------------
DROP TABLE IF EXISTS `orders_000`;
CREATE TABLE `orders_000` (
  `id` int(11) NOT NULL,
  `customer` varchar(255) DEFAULT NULL,
  `price` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of orders_000
-- ----------------------------

-- ----------------------------
-- Table structure for orders_001
-- ----------------------------
DROP TABLE IF EXISTS `orders_001`;
CREATE TABLE `orders_001` (
  `id` int(11) NOT NULL,
  `customer` varchar(255) DEFAULT NULL,
  `price` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of orders_001
-- ----------------------------


-- ----------------------------
-- Table structure for orders_002
-- ----------------------------
DROP TABLE IF EXISTS `orders_002`;
CREATE TABLE `orders_002` (
  `id` int(11) NOT NULL,
  `customer` varchar(255) DEFAULT NULL,
  `price` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of orders_002
-- ----------------------------

-- ----------------------------
-- Table structure for orders_003
-- ----------------------------
DROP TABLE IF EXISTS `orders_003`;
CREATE TABLE `orders_003` (
  `id` int(11) NOT NULL,
  `customer` varchar(255) DEFAULT NULL,
  `price` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of orders_003
-- ----------------------------
