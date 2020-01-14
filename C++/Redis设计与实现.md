# Redis设计与实现

- Redis数据库里面的每个键值对都是由对象组成的，其中:数据库键总是一个字符串对象，而数据库键的值则可以是字符串对象、列表对象、哈希对象、集合对象、有序集合对象

### 第2章　简单动态字符串SDS

- 在Redis的数据库里面，包含字符串值的键值对在底层都是由SDS实现的

### 2.1 SDS的定义

- 每个sds.h/sdshdr结构表示一个SDS值
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 15-46-34.png)

### 2.2 SDS与C字符串的区别

- 常数复杂度获取字符串的长度
- 杜绝缓冲区溢出
  - 当SDS API需要对SDS进行修改时，会先检查SDS的空间是否满足修改所需的要求，如果不满足，自动将SDS的空间扩展
- 减少修改字符串时带来的内存重分配次数
  - 空间预分配
  - 惰性空间释放
- 二进制安全
  - C字符串中的字符必须符合某种编码
  - 所有SDS API都会以处理二进制的方式来处理SDS存放在buf数组里的数据，程序不会对其中的数据做任何限制、过滤或者假设
  - SDS使用len属性的值而不是空字符来判断字符串是否结束，使用二进制安全的SDS,使得Redis不仅可以保存文本数据，还可以保存任意格式的二进制数据
- 兼容部分C字符串函数
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-09-57.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-16-02.png)

## 第3章　链表

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-19-31.png)

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-21-16.png)

- 多态: 链表节点使用void* 指针来保存节点值，并且可以通过list结构的dup  free  match三个属性为节点值设置类型特定函数
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-24-22.png)

- 链表被广泛用于实现Redis的各种功能，比如列表键、发布与订阅、慢查询、监视器等

## 第4章　字典

- Redis的数据库使用字典作为底层实现的，对数据库的增、删、查、改操作也是构建在对字典的操作之上的
- 字典还是哈希键的底层实现之一

### 4.1 字典的实现

- Redis的字典使用哈希表作为底层实现，每个哈希表节点就保存了字典中的一个键值对

- 哈希表

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-34-59.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-35-20.png)

- 哈希表节点

  - 哈希表节点使用dictEntry结构表示，每个结构都保存着一个键值对
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-37-05.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-38-50.png)

- 字典

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-40-13.png)

  - type和privdata属性是针对不同类型的键值对，为创建多态字典而设置的
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-43-44.png)



### 4.2 哈希算法

- 当要将一个新的键值对添加到字典里面时，程序需要先根据键值对的键计算出哈希值和索引值，然后根据索引值，将包含新键值对的哈希表节点放到哈希表数组的指定索引上面
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-46-53.png)

- Redis使用MurmurHash2算法来计算键的哈希值

### 4.3 解决键冲突

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-51-06.png)

### 4.4 rehash

- 当哈希表保存的键值对数量太多或者太少时，程序需要对哈希表的大小进行相应的扩展或收缩
- rehash指的是重新计算键的哈希值和索引值，然后将键值对放置到ht[1]哈希表的指定位置
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 16-55-37.png)

### 4.5 渐进式rehash

- rehash的动作并不是一次性完成的，而是分多次、渐进式地完成的
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 17-00-07.png)

- 在进行渐进式rehash的过程中，字典会同时使用ht[0]和ht[1]

### 4.6 字典API

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-30 17-06-17.png)

