# MySQL必知必会

## 第一章　了解SQL

### 1.1 数据库基础

- 什么是数据库
  - 注意数据库与数据库管理系统的区别
- 表
  - 描述表的这组信息就是模式
- 列和数据类型
- 行
- 主键，其值能唯一区分表中每个行

### 1.2 什么是SQL

- 结构化查询语言的缩写，是一种专门用来与数据库通信的语言

## 附录A

- 需要什么
  - MySQL服务器
  - 客户机软件(用来实际运行MySQL命令的程序)
- 获得软件
  - http://dev.mysql.com/
- 安装软件
  - 先安装一个本地MySQL服务器

## 第二章　MySQL简介

### 2.1 什么是MySQL

- 客户机-服务器软件，客户软件需要与服务器软件进行通信
  - 服务器软件为MySQL DBMS
  - 客户机可以是MySQL提供的工具、脚本语言、程序设计语言
- MySQL版本

### 2.2 MySQL工具

- mysql命令行实用程序
  - 每个MySQL安装都有一个名为mysql的简单命令行实用程序
  -  mysql --help
  - 命令用;或\g结束
  - 是核心MySQL安装的一部分
- MySQL Administrator
  - 是一个图形交互客户机，不作为核心MySQL的组成部分安装
- MySQL Query Browser
  - 一个图形交互客户机，用来编写和执行MySQL命令，不作为核心MySQL的组成部分安装

## 第三章　使用MySQL

### 3.1 连接

- 本地MySQL服务器为localhost
- 端口，默认3306

### 3.2 选择数据库

- USE关键字
- USE crashcourse 使用crashcourse数据库

### 3.3 了解数据库和表

- SHOW　返回可用数据库的一个列表
- SHOW DATABASES显示信息
- SHOW TABLES获得一个数据库内的表的列表
- SHOW COLUMNS FROM customers显示表列
- 自动增量
- DESCRIBE语句
- SHOW STATUS
- SHOW CREATE DATABASE和SHOW CREATE TABLE
- SHOW GRANTS
- SHOW ERRORS和SHOW WARNINGS
- HELP SHOW显示允许的SHOW语句

## 第四章　检索数据

### 4.1 SELECT语句

### 4.2 检索单个列

- select User from user;
- SQL语句不区分大小写，许多开发人员喜欢对关键字大写，对所有列名和表名小写

### 4.3检索多个列

- select User,Host from user;

### 4.4 检索所有列

- SELECT * FROM user;

### 4.5 检索不同的行

- select DISTINCT User from user;
- DISTINCT应用于所有列

### 4.6限制结果

- LIMIT子句
- select DISTINCT User,Host from user LIMIT 3;  只返回不多于3行
- select DISTINCT User,Host from user LIMIT 3,3;　返回从行3开始的3行
- LIMIT 3 OFFSET 3　与上面的相同

### 第5章　排序检索数据

### 5.1 排序数据

- select  User,Host from user ORDER BY User;

### 5.2 按多个列排序

-  select  User,Host from user ORDER BY User,Host;

### 5.3 指定排序方向

- select  User,Host from user ORDER BY User,Host DESC; 降序排列

- DESC关键字只应用到直接位于其前面的列名

- ASC　默认

- 使用子句的次序不对将产生错误消息

## 第6章　过滤数据

### 6.1 使用WHERE子句

- SELECT User,Host FROM user WHERE User='root';

### 6.2 WHERE子句操作符

- 检查单个值
- 不匹配检查
  - SELECT User,Host FROM user WHERE User<>'root';    不等于
- 范围值检查
  - SELECT User,Host FROM user WHERE User BETWEEN 2 AND 3;
- 空值检查
  - SELECT User,Host FROM user WHERE User IS NULL;

## 第7章　数据过滤

### 7.1 组合WHERE子句

- AND操作符
  - SELECT User,Host FROM user WHERE User='root' and Host='%';
- OR操作符
  - SELECT User,Host FROM user WHERE User='root' OR Host='%';
- 计算次序
  - 使用圆括号明确地分组操作符

### 7.2 IN操作符

- SELECT User,Host FROM user WHERE User IN ('root','leiwang') ORDER BY Host;

### 7.3 NOT操作符

- SELECT User,Host FROM user WHERE User NOT IN ('root','leiwang') ORDER BY Host;

## 第8章　用通配符进行过滤

### 8.1 LIKE操作符

- %通配符
  - %表示任何字符出现的任意次数
  - SELECT User,Host FROM user WHERE User LIKE 'my%';
  - SELECT User,Host FROM user WHERE User LIKE '%y%';
  - 不能匹配NULL
- 下划线_通配符
  - 只匹配单个字符
  - SELECT User,Host FROM user WHERE User LIKE '_ysql.sys';

### 8.2 使用通配符的技巧

- 不要过度使用
- 尽量不要放在开始处



## 第九章　用正则表达式进行搜索

- 所有种类的程序设计语言、文本编辑器、操作系统等都支持正则表达式

### 9.2 使用MySQL正则表达式

- 基本字符匹配

  - SELECT User FROM user WHERE User REGEXP 'mysql';
  - .是正则表达式语言中一个特殊的字符，表示匹配任意一个字符
  - LIKE匹配整个列，如果匹配的文本在列值中出现，LIKE将不会找到它
  - REGEXP在列值内进行匹配，使用^和$定位符可以匹配整个列
  - 为区分大小写，可使用BINARY关键字

- 进行OR匹配

  - SELECT User FROM user WHERE User REGEXP 'root|mysql';
  - 匹配几个字符之一
  - SELECT User FROM user WHERE User REGEXP 'mysql.s[dy]';　[dy]定义一组字符，匹配d或y 
  - [^123]  匹配除123的任何字符
  - SELECT User FROM user WHERE User REGEXP 'mysql.s[^dy]';
  - [a-z]匹配任意字母字符

- 匹配特殊字符

  - 加上\\\　　MySQL需要两个反斜杠
  - \\\ . 表示查找.
  - SELECT User FROM user WHERE User REGEXP '\\.';
  - SELECT User FROM user WHERE User REGEXP '\\-';
  - 空白元字符
    - \\\f换页
    - \\\n 换行

- 匹配字符类

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 19-47-57.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 19-51-25.png)

  - SELECT User FROM user WHERE User REGEXP '[[:alnum:]]{5,}';

- 定位符

  - 为了匹配特定位置的文本，需要使用定位元字符
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 19-54-19.png)

  - SELECT User FROM user WHERE User REGEXP '^[rm]';



## 第10章　创建计算字段

### 10.1 计算字段

### 10.2 拼接字段

- concat函数拼接两个字段
  - SELECT Concat(User,'(',Host,')') FROM user;      各个串之间用逗号分隔
  - RTrim函数删除数据右侧多余的空格
  - LTrim
  - Trim
- 别名是一个字段或值的替换名，别名用AS关键字赋予
  - SELECT Concat(User,' (',Host,')')  AS new_col  FROM user;

### 10.3 执行算术计算

- SELECT prod_id, quantity, item_price, quantity*item_price AS expanded_price From orderitems 
- 如何测试计算
  - 省略FROM子句以便简单地访问和处理表达式
  - SELECT 2*3;
  - SELECT Now();　Now函数返回当前日期和时间

## 第11 章　使用数据处理函数

### 11.1 函数

- 函数没有SQL的可移植性强

### 11.2 使用函数

- 文本处理函数

  - Left 返回串左边的字符
  - Right
  - Length  返回串的长度
  - Locate 找出串的一个子串
  - Lower  将串转换为小写
  - LTrim  去掉串左边的空格
  - RTrim
  - Soundex 返回串的SOUNDEX值
  - SubString  返回子串的字符
  - Upper  将串转换为大写

- 日期和时间处理函数

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 20-38-47.png)

  - 日期必须为格式   2019-12-23
  - SELECT cust_id, order_num FROM orders WHERE Year(order_date)=2005  AND  Month(order_date)=9; 检索出order_date为2005年9月的所有行

- 数值处理函数

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 20-44-48.png)

## 第12章　汇总数据

### 12.1 聚集函数

- AVG 
  - AVG函数忽略列值为NULL的行
- COUNT
  - 如果指定列名，则指定列的值为空的行被COUNT函数忽略，但如果COUNT函数中用的是星号*,则不忽略
- MAX
- MIN
- SUM

### 12.2 聚集不同值

- 指定DISTINCT参数，只包含不同的值
- SELECT AVG(DISTINCT prod_price) AS avg_price FROM products

### 12.3 组合聚集函数

## 第13章　分组数据

### 13.1 数据分组

### 13.2 创建分组

- SELECT User,count(*) AS NEW_COL FROM user GROUP BY User;

### 13.3 过滤分组

- WHERE过滤行，HAVING过滤分组。
- SELECT User,count(\*) AS NEW_COL FROM user GROUP BY User HAVING count(*)>=2;
- WHERE在数据分组前进行过滤，HAVING在数据分组后进行过滤

### 13.4 分组和排序

- GROUP BY和ORDER BY的结合

## 第14章　使用子查询

### 14.1 子查询

- 嵌套在其他查询中的查询

### 14.2 利用子查询进行过滤

- SELECT cust_id FROM orders WHERE order_num IN (SELECT order_num FROM orderitems WHERE prod_id='TNT2');

### 14.3 作为计算字段使用子查询

## 第15章　联结表

### 15.1 联结

- 关系表
  - 主键和外键
- 联结
  - 联结是一种机制，用来在一条SELECT语句中关联表，联结不是物理实体

### 15.2 创建联结

- SELECT vend_name, prod_name, prod_price FROM vendors, products WHERE vendors.vend_id=products.vend_id ORDER BY vend_name, pro_name;
- 笛卡尔积: 由没有联结条件的表关系返回的结果为笛卡尔积，检索出的行的数目将是第一个表中的行数乘以第二个表中的行数

  - SELECT vend_name, prod_name, prod_price FROM  vendors, products ORDER BY vend_name, prod_name;
  - SELECT Host,name FROM user,proc ORDER BY Host,name;
  - SELECT Db FROM user,db  WHERE user.Host=db.Host ORDER BY Db;
  - SELECT Db,db.User FROM user,db  WHERE user.User=db.User ORDER BY Db;
  - 应该保证所有联结都有WHERE子句
- 内部联结
  - 等值联结，基于两个表之间的相等测试，也称为内部联结
  - SELECT vend_name, prod_name, prod_price FROM  vendors　INNER JOIN　 products ON vendors.vend_id=products.vend_id;
- 联结多个表
  - SELECT prod_name,vend_name,prod_price, quantity  FROM orderitems, products, vendors WHERE products.vend_id=vendors.vend_id AND orderitems.prod_id=products.prod_id AND order_num=20005;

## 第16章　创建高级联结

### 16.1 使用表别名

- SELECT Db FROM user AS u, db AS d WHERE u.User=d.User;
- 表别名只在查询执行中使用，与列别名不一样，表别名不返回到客户机

### 16.2 使用不同类型的联结

- 自联结
  - SELECT p1.prod_id, p1.prod_name FROM products AS p1, products AS p2 WHERE p1.vend_id=p2.vend.vend_id  AND　p2.prod_id='DTNTR';
- 自然联结
  - 标准的联结返回所有数据，自然联结排除多次出现，使每个列只返回一次
- 外部联结
  - 联结包括了那些在相关表中没有关联行的行
  - SELECT vend_name, prod_name, prod_price FROM  vendors　LEFT OUTER JOIN　 products ON vendors.vend_id=products.vend_id;

### 16.3 使用带聚集函数的联结



## 第17章　组合查询

### 17.1 组合查询

### 17.2 创建组合查询

- 可用UNION操作符来组合数条SQL查询

  - SELECT vend_id, prod_id,prod_price FROM products WHERE prod_price<=5  UNION

    SELECT vend_id, prod_id, prod_price FROM products WHERE vend_id IN (1001, 1002)

- UNION规则

  - SELECT语句之间用关键字UNION分隔
  - UNION的每个查询必须包含相同的列、表达式或聚集函数
  - 列数据类型必须兼容:不必完全相同

- 包含或取消重复的行

  - UNION默认去掉重复的行
  - UNION ALL不取消重复的行

- 对组合查询结果排序

  - 使用UNION组合查询时，只能使用一条ORDER BY 子句，必须出现在最后一条SELECT语句之后

## 第18章　全文本搜索

### 18.1 理解全文本搜索

- 数据库引擎，常用的: MyISAM和InnoDB

### 18.2 使用全文本搜索

- 启用全文本搜索支持

  - ```mysql
    CREATE TABLE productnotes (
    	note_id int NOT NULL AUTO_INCREMENT,
        prod_id char(10) NOT NULL,
        note_date datetime  NOT NULL,
        note_text text NULL,
        PRIMARY KEY(note_id),
        FULLTEXT(note_text)
        )ENGINE=MyISAM; 
    ```

- 进行全文本搜索

  - Match 指定被搜索的列，Against指定要使用的搜索表达式
  - SELECT note_text FROM productnotes WHERE match(note_text) against('rabbit');
  - 传递给Match的值必须与FULLTEXT定义中的相同
  - 搜索不区分大小写
  - 全文本搜索的一个重要部分就是对结果排序，具有较高等级的行先返回
  - SELECT note_text, Match(note_text) Against('rabbit') AS rank FROM productnotes; rank列包含全文本搜索计算出的等级值

- 使用查询扩展

  - 利用查询扩展，能找出可能相关的结果
  - SELECT note_text FROM productnotes WHERE Match(note_text) Against('anvils' WITH QUERY EXPANSION); 
  - 查询扩展极大地增加了返回的行数，但也增加了并不想要的行的数目

- 布尔文本搜索

  - 即使没有定义FULLTEXT索引，也可以使用它

  - SELECT note_text FROM productnotes WHERE Match(note_text) Against('heavy' IN BOOLEAN MODE);

  - SELECT note_text FROM productnotes WHERE Match(note_text) Against('heavy  -rope*' IN BOOLEAN MODE); 排除包含rope\*的行

  - SELECT User FROM user WHERE match(User) against('mysql' in boolean mode);

  - 全文本布尔操作符

    - +

    - -

    - \>

    - <

    - \()

    - ~

    - *

    - " "

## 第19章　插入数据

### 19.1 数据插入

### 19.2 插入完整的行

- INSERT INTO productnotes VALUES(1,2,'2018-01-21','first');
- INSERT INTO productnotes(note_id,prod_id,note_date,note_text) VALUES(2,3,'2019-12-11','second');

### 19.3 插入多个行

- INSERT INTO productnotes(note_id,prod_id,note_date,note_text) VALUES(4,5,'2019-12-11','fourth'),(3,4,'2019-12-12','third');

### 19.4 插入检索出的数据

- INSERT INTO productnotes2(note_id,prod_id,note_date,note_text) SELECT   note_id,prod_id,note_date,note_text FROM productnotes;

## 第20章　更新和删除数据

### 20.1 更新数据

- UPDATE productnotes SET note_id=5 WHERE note_id=2;

### 20.2 删除数据

- DELETE FROM productnotes WHERE note_id=1;
- DELETE删除整行而不是删除列，为了删除指定的列，使用UPDATE语句

## 第21章　创建和操纵表

### 21.1 创建表

- ```mysql
  CREATE TABLE productnotes2 (
  	note_id int NOT NULL AUTO_INCREMENT,
      prod_id char(10) NOT NULL,
      note_date datetime  NOT NULL,
      note_text text NULL,
      PRIMARY KEY(note_id)
      )ENGINE=InnoDB; 
  ```

- 使用NULL值

- 主键

  - 主键中只能使用不允许NULL值的列

- 使用AUTO_INCREMENT

  - 本列当增加一行时自动增量
  - SELECT last_insert_id();　返回最后一个AUTO_INCREMENT值

- 指定默认值

  - ```mysql
    CREATE TABLE productnotes3 (
    	note_id int NOT NULL AUTO_INCREMENT,
        prod_id char(10) NOT NULL  DEFAULT 1,
        note_date datetime  NOT NULL,
        note_text text NOT NULL,
        PRIMARY KEY(note_id)
        )ENGINE=InnoDB; 
    ```

- 引擎类型

  - 如果省略ENGINE=语句，则使用默认引擎，很可能是MyISAM
  - 外键不能跨引擎

### 21.2 更新表

- ALTER TABLE productnotes3 ADD vend CHAR(20);  给表添加一个列
- ALTER TABLE productnotes3 DROP COLUMN vend; 删除表的一个列
- ALTER TABLE orderitems ADD CONSTRAINT fk_orderitems_orders FOREIGN KEY(order_num) REFERENCES orders(order_num); 定义外键

### 21.3 删除表

- DROP TABLE productnotes3;

### 21.4 重命名表

- RENAME TABLE productnotes2 TO productnotes1; 

## 第22章 使用视图

### 22.1 视图

- 视图不能索引，也不能有关联的触发器或默认值

### 22.2 使用视图

- CREATE VIEW创建视图
- DROP删除
- 利用视图简化复杂的联结
  - CREATE VIEW Test AS SELECT Db,db.User FROM user,db  WHERE user.User=db.User ORDER BY Db;
  - SELECT * FROM Test WHERE Db='sys';
- 更新视图
  - 更新一个视图将更新其基表，如果MySQL不能正确地确定被更新的基数据，则不允许更新视图

## 第23章　使用存储过程

### 23.1 存储过程

- 存储过程是为以后的使用而保存的一条或多条MySQL语句的集合

### 23.2 为什么要使用存储过程

### 23.3 使用存储过程

- MySQL称存储过程的执行为调用　CALL productpricing(@pricelow,@pricehigh,@priceaverage); 执行名为productpricing的存储过程

- 创建存储过程

  - ```mysql
    CREATE PROCEDURE productpricing()
    BEGIN
    	SELECT * FROM productnotes;
    END;
    ```

  - ```mysql
    DELIMITER //
    CREATE PROCEDURE productpricing()
    BEGIN
    	SELECT * FROM productnotes;
    END //
    DELIMITER ;
    ```

  - mysql命令行客户机的分隔符

  - CALL productpricing();　　调用存储过程

- 删除存储过程

  -  DROP PROCEDURE productpricing;

- 使用参数

  - 参数类型　IN(传递给存储过程)　　out(从存储过程中传出)　INOUT(对存储过程传入和传出)
  - 通过INTO关键字保存到相应的变量
  - 所有MySQL变量都必须以@开始

- 建立智能存储过程

  - -- 是注释
  - DECLARE语句可声明局部变量
  - IF语句

## 第24章　使用游标

### 24.1 游标

- MySQL游标只能用于存储过程
- 游标是一个存储在MySQL服务器上的数据库查询，它不是一条SELECT语句，而是被该语句检索出来的结果集

### 24.2 使用游标

- 创建游标

  - DECLARE ordernumbers CURSOR FOR SELECT order_num FROM orders;

- 打开和关闭游标

  - OPEN ordernumbers; 打开
  - CLOSE ordernumbers; 关闭

- 使用游标数据

  - 在一个游标被打开以后，可以使用FETCH语句分别访问它的每一行

  - FETCH ordernumbers INTO o;

  - ```mysql
    CREATE PROCEDURE processorders()
    BEGIN
    	DECLARE done BOOLEAN DEFAULT 0;
    	DECLARE o INT;
    	DECLARE ordernumbers CURSOR
    	FOR 
    	SELECT order_num FROM orders;
    	DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET done=1;
    	OPEN ordernumbers;
    	REPEAT
    		FETCH ordernumbers INTO o;
    	UNTIL done END REPEAT;
    	CLOSE ordernumbers;
    END;
    ```

## 第25章　使用触发器

### 25.1 触发器

- 触发器是MySQL响应以下任意语句而自动执行的一条MySQL语句
  - DELETE
  - INSERT
  - UPDATE
  - 位于BEGIN和END语句之间的一组语句

### 25.2 创建触发器

- CREATE TRIGGER newproduct AFTER INSERT ON products FOR EACH ROW SELECT 'Product added'　　文本 'Product added'　将对每个插入的行显示一次

### 25.3 删除触发器

- DROP TRIGGER 

### 25.4 使用触发器

- INSERT触发器

  - 在INSERT触发器代码内，可引用一个名为NEW的虚拟表，访问被插入的行
- DELETE触发器
  - 可以引用一个名为OLD的虚拟表，访问被删除的行
- UPDATE触发器
  - OLD以前的值，NEW新的值

​      

## 第26章　管理事务处理

### 26.1 事务处理

- InnoDB支持事务处理，MyISAM不支持事务处理
- 事务处理可以用来维护数据库的完整性，保证成批的MySQL操作要么完全执行，要么完全不执行
- 事务: 指一组SQL语句
- 回退: 指撤销指定SQL语句的过程
- 提交: 指将未存储的SQL语句结果写入数据库表
- 保留点: 指事务处理中设置的临时占位符

### 26.2 控制事务处理

- 标识事务的开始: START TRANSACTION

- ROLLBACK 命令用来回退MySQL语句。用一条ROLLBACK语句回退START TRANSACTION之后的所有语句，事务处理用来管理INSERT UPDATE 和DELETE语句

- ```mysql
  SELECT * FROM productnotes1;
  START transaction;
  DELETE FROM productnotes1 WHERE note_id=3;
  SELECT * FROM productnotes1;
  ROLLBACK;
  SELECT * FROM productnotes1;
  ```

- 使用COMMIT

  - 一般的MySQL语句都是直接针对数据库表执行和编写的，即提交和保存操作是自动进行的

  - 在事务处理块中，提交不会隐含地进行，为进行明确的提交，使用COMMIT语句

  - ```mysql
    START transaction;
    DELETE FROM productnotes1 WHERE note_id=3;
    COMMIT;
    ```

  - 当COMMIT或ROLLBACK语句执行后，事务会自动关闭

- 使用保留点

  - 为了支持回退部分事务处理
  - 创建占位符:  SAVEPOINT delete1;
  - 回退:  ROLLBACK TO delete1;

- SET autocommit=0;  指示MySQL不自动提交更改

## 第27章　全球化和本地化

### 27.1 字符集和校对顺序

### 27.2 使用字符集和校对顺序

- SHOW CHARACTER SET;显示所有可用的字符集以及每个字符集的描述和默认校对

- SHOW COLLATION;　查看所支持的完整列表

- ```mysql
  SHOW VARIABLES LIKE 'character%';
  SHOW VARIABLES LIKE 'collation%';
  -- 确定所用的字符集和校对
  ```

- ```mysql
  CREATE TABLE mytable(
  	column1 INT,
  	column2 VARCHAR(10)
  )DEFAULT CHARACTER SET hebrew
   COLLATE hebrew_general_ci;
  -- 指定字符集和校对顺序
  ```

## 第28章　安全管理

### 28.1 访问控制

- root对整个MySQL服务器具有完全的控制，仅在绝对需要时使用它

### 28.2 管理用户

- MySQL用户账号和信息存储在名为mysql的MySQL数据库中
- 创建用户账号
  - CREATE USER ben IDENTIFIED BY 'p@$$wOrd'
  - GRANT语句也可以创建用户账号
- RENAME USER ben TO bforta  重新命名一个用户账号
- 删除用户账号　DROP USER bforta
- 设置访问权限　　
  - SHOW GRANTS FOR bforta;  展示赋予用户账号的权限
  - USAGE ON \*.\* 表示没有任何权限
  - 用户定义为user@host   如果不指定主机名，则使用默认的主机名%(授予用户访问权限而不管主机名)
  - 为设置权限，使用GRANT
    - GRANT SELECT ON crashcourse.* TO leiwang    此GRANT允许用户在crashcourse.*(crashcourse数据库的所有表)上使用SELECT
    - REVOKE 撤销特定的权限　REVOKE SELECT ON crashcourse.* FROM leiwang
    - 整个服务器，使用GRANT ALL和REVOKE ALL
    - 整个数据库，使用　ON database.*
    - 特定的表，　使用ON database.table
    - 特定的列
    - 特定的存储过程
- 更改口令
  - SET PASSWORD FOR leiwang=Password('n3w p@$$wOrd');

## 第29章　数据库维护

### 29.1 备份数据

### 29.2 进行数据库维护

- ANALYZE TABLE用来检查表键是否正确　　ANALYZE TABLE mysql;
- CHECK TABLE productnotes;

### 29.3 诊断启动问题

- --help显示帮助
- --safe-mode装载减去某些最佳配置的服务器
- --verbose显示全文本消息
- --version 显示版本信息然后退出

### 29.4 查看日志文件

- 错误日志
- 查询日志
- 二进制日志
- 缓慢查询日志

## 第30章　改善性能





  

  

  



  

  

  

  

  