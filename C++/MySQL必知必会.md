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




