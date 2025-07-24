create table Books(
        bookId number(9,0),
        title varchar(80),
        author varchar(40),
        year integer,
        category varchar(15),
        PRIMARY KEY (bookId)
        );

create table Customers (
        cid number(9,0) PRIMARY KEY,
        cname char(40),
        age integer
        );

create table Purchases(
        cid number(9,0),
        bookId number(9,0),
        pdate date,
        pprice number(8,2),
        PRIMARY KEY (cid, bookId),
        FOREIGN KEY (bookId) REFERENCES Books,
        FOREIGN KEY (cid) REFERENCES Customers
        );

create table Pricing(
        bookId number(9,0),
        format varchar(15),
        price number(9,2),
        PRIMARY KEY (bookId)
        );


insert into Books values (101,'Introduction to Databases','David Maier',1981,'textbook');
insert into Books values (102,'Database System Concepts','Abraham Silberschatz',2004,'textbook');
insert into Books values (103,'Principles of Database and Knowledge-Base Systems','Jeffrey Ullman',1997,'textbook');
insert into Books values (104,'First Course in Database Systems','Jeffrey Ullman',2008,'textbook');
insert into Books values (105,'Promises to Keep: On Life and Politics','Joseph Biden',2008,'politics');
insert into Books values (106,'Change We Can Believe In: Barack Obama''s Plan to Renew America''s Promise','Barack Obama',2008,'politics');
insert into Books values (107,'Blindness','Jose Saramago',1999,'romance');
insert into Books values (108,'The Gospel According to Jesus Christ','Jose Saramago',1994,'romance');
insert into Books values (109,'Sauces: Classical and Contemporary Sauce Making','James Peterson',2008,'cooking');


insert into Customers values (1, 'john', 20);
insert into Customers values (2, 'mary', 18);
insert into Customers values (3, 'jane', 28);
insert into Customers values (4, 'ann', 40);
insert into Customers values (5, 'joyce', 33);
insert into Customers values (6, 'terry', 25);
insert into Customers values (7, 'claire', 80);
insert into Customers values (8, 'john', 60);

insert into Purchases values (1, 101, DATE '1999-1-10', 20);
insert into Purchases values (1, 102, DATE '2004-3-10', 60);
insert into Purchases values (1, 103, DATE '1999-1-10', 40);
insert into Purchases values (1, 104, DATE '2008-8-1', 120);
insert into Purchases values (1, 106, DATE '2008-7-1', 10.00);
insert into Purchases values (1, 107, DATE '2000-11-4', 7.49);
insert into Purchases values (1, 109, DATE '2008-7-1', 32.97);
insert into Purchases values (2, 101, DATE '1999-2-10', 20);
insert into Purchases values (2, 102, DATE '2004-03-04', 60);
insert into Purchases values (3, 103, DATE '1999-1-1', 40);
insert into Purchases values (3, 104, DATE '2008-8-1', 120);
insert into Purchases values (3, 109, DATE '2008-8-2', 32.97);
insert into Purchases values (4, 105, DATE '1999-9-3', 20);
insert into Purchases values (5, 106, DATE '2004-3-1', 60);
insert into Purchases values (6, 107, DATE '2004-7-7', 60);
insert into Purchases values (7, 109, DATE '2008-10-4', 30.45);

insert into Pricing values (101,'hardcover', 32.95);
insert into Pricing values (102,'hardcover', 120.00);
insert into Pricing values (103,'paperback', 35.00);
insert into Pricing values (104,'hardcover', 130.00);
insert into Pricing values (105,'paperback', 12.55);
insert into Pricing values (106,'paperback', 7.48);
insert into Pricing values (107,'paperback', 17.98);
insert into Pricing values (108,'paperback', 14.33);
insert into Pricing values (109,'paperback', 44.88);

commit;

