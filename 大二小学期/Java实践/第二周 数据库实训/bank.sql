CREATE TABLE manager
(
c_manager_id INT PRIMARY KEY,
c_name VARCHAR(100) NOT NULL,
c_mail CHAR(30) UNIQUE,
c_id_card CHAR(20) UNIQUE NOT NULL,
c_phone CHAR(20) UNIQUE NOT NULL,
c_password CHAR(20) NOT NULL
);

CREATE TABLE client
(
c_id INT PRIMARY KEY,
c_name VARCHAR(100) NOT NULL,
c_mail CHAR(30) UNIQUE,
c_id_card CHAR(20) UNIQUE NOT NULL,
c_phone CHAR(20) UNIQUE NOT NULL,
c_password CHAR(20) NOT NULL,
c_manager_id INT,
CONSTRAINT fk_client_manager foreign key (c_manager_id) references manager(c_manager_id)
);

insert into manager (c_manager_id,c_name,c_mail,c_id_card,c_phone,c_password) values (1,'黄勖','hx@huawei.com','123','123','gaussdb_101');
insert into manager (c_manager_id,c_name,c_mail,c_id_card,c_phone,c_password) values (2,'陈伊彬','cyb@huawei.com','456','456','gaussdb_102');
insert into manager (c_manager_id,c_name,c_mail,c_id_card,c_phone,c_password) values (3,'胡翼翔','hyx@huawei.com','789','789','gaussdb_103');

INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (1,'张一','zhangyi@huawei.com','340211199301010001','18815650001','gaussdb_001',1);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (2,'张二','zhanger@huawei.com','340211199301010002','18815650002','gaussdb_002',1);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (3,'张三','zhangsan@huawei.com','340211199301010003','18815650003','gaussdb_003',1);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (10,'李一','liyi@huawei.com','340211199301010010','18815650010','gaussdb_010',2);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (11,'李二','lier@huawei.com','340211199301010011','18815650011','gaussdb_011',2);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (12,'李三','lisan@huawei.com','340211199301010012','18815650012','gaussdb_012',2);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (19,'王一','wangyi@huawei.com','340211199301010019','18815650019','gaussdb_019',3);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (20,'王二','wanger@huawei.com','340211199301010020','18815650020','gaussdb_020',3);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (21,'王三','wangsan@huawei.com','340211199301010021','18815650021','gaussdb_021',3);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (28,'钱一','qianyi@huawei.com','340211199301010028','18815650028','gaussdb_028',1);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (29,'钱二','qianer@huawei.com','340211199301010029','18815650029','gaussdb_029',1);
INSERT INTO client(c_id,c_name,c_mail,c_id_card,c_phone,c_password,c_manager_id) VALUES (30,'钱三','qiansan@huawei.com','340211199301010030','18815650030','gaussdb_030',1);

select * from client where c_manager_id = (select c_manager_id from manager where c_name='黄勖');
select * from manager where c_manager_id in (select c_manager_id from client where c_name='张一');
