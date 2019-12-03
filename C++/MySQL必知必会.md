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

  



