# UNP

## 第一章　简介

### 1.1 概述

- 客户和服务器通常是用户进程，而TCP和IP协议通常是内核中协议栈的一部分

### 1.2 一个简单的时间获取客户程序

- 编译时　　gcc daytimetcpcli.c -o daytimetcpcli -lunp 

- autoconf 和automake
- Makefile文件
- Linux下使用automake、autoconf生成configure文件
- 创建TCP套接字　socket
- 指定服务器的IP地址和端口
  - bzero函数
  - htons函数
  - 13 时间获取服务器的端口
  - inet_pton函数
- 建立与服务器的连接
  - connect
  - 通用套接字地址结构　struct sockaddr
- 读入并输出服务器的应答
  - read函数
  - TCP是一个没有记录边界的字节流协议
- 终止程序

### 1.3 协议无关性

- 修改部分代码即可
- 最好编写协议无关的程序

### 1.4 错误处理: 包裹函数

- 每个包裹函数完成实际的函数调用，检查返回值，并在发生错误时终止进程
- 约定包裹函数名是实际函数名的大写形式
- 只要一个Unix函数中有错误发生，全局变量errno就被设置为一个指明该错误类型的正值

### 1.5 一个简单的时间获取服务器程序

- 创建TCP套接字
- 把服务器众所周知端口绑到套接字
  - bind
- 把套接字转换成监听套接字
  - listen
- 接受客户连接，发送应答
  - accept
  - 握手完毕后accept返回，返回值是一个已连接描述符
  - write函数把结果字符串写回给客户
- 终止连接
  - 调用close关闭与客户的连接，引发正常的TCP连接终止序列
  - 并发服务器: 可使用Unix的fork函数实现，或线程技术
  - Unix守护进程: 能在后台运行且不跟任何终端关联的进程

### 1.6客户/服务器程序

- 时间获取客户程序的不同版本
- 时间获取服务器程序的不同版本
- 回射客户程序的不同版本
- 回射服务器程序的不同版本



### 1.7 OSI模型

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 13-26-57.png)

- 套接字编程接口是从顶上三层(网际协议的应用层)进入传输层的接口
- 顶上三层通常构成用户进程，底下四层通常作为操作系统内核的一部分提供
- Linux这种流行的可免费获得的Unix实现并不适合归属自Berkeley系列，因为它的网络支持代码和套接字API都是从头开始开发的

### 1.9 测试用网络及主机

- netstat -i  提供网络接口的信息　　-n 标志以输出数值地址
  - 环回(loopback)接口称为lo
  - 以太网接口称为eth0
- netstat -r 展示路由表
- ifconfig　　 enp4s0　　　执行ifconfig可获得每个接口的详细信息
- 针对本地接口的广播地址执行ping 命令可获得本地网络中众多主机的IP地址　　 ping  -b  广播地址



### 1.11 64位体系结构

- 在每个进程内部可以由此使用更长的编址长度，从而可以寻址很大的内存空间
- 套接字API对套接字地址结构的长度使用socklen_t数据类型



## 第二章　传输层: TCP UDP SCTP

- 绕过传输层直接使用IP协议称为原始套接字
- SCTP 流控制传输协议，一个可靠的传输协议

### 2.2 总图

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 14-08-58.png)

- tcpdump 使用数据链路提供者接口与数据链路进行通信
- traceroute程序使用两种套接字: IP套接字用于访问IP, ICMP套接字用于访问ICMP
- TCP套接字是一种流套接字,没有任何记录边界
- UDP套接字是一种数据报套接字

### 2.3 UDP

- 每个UDP数据报有一个长度，如果一个数据报正确到达目的地，那么该数据报的长度将随数据一道传递给接收端应用进程

### 2.4 TCP

### 2.5 SCTP

- SCTP在客户和服务器之间提供关联，并像TCP那样给应用提供可靠性、排序、流量控制以及全双工的数据传送，一个关联指代两个系统之间的一次通信，它可能因为SCTP支持多宿而涉及不止两个地址
- 面向消息的。提供各个记录的按序递送服务
- SCTP能够在所连接的端点之间提供多个流
- 多宿特性，使得单个SCTP端点能够支持多个IP地址

### 2.6 TCP连接的建立和终止

- 三路握手
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 14-29-11.png)

- TCP选项

  - MSS选项，最大分节大小
  - 窗口规模选项
  - 时间戳选项

- TCP连接终止

  - 建立一个连接需要三个分节，终止一个连接需要四个分节
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 14-37-32.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 14-37-53.png)

- TCP状态转换图
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 14-42-24.png)

- 观察分组
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 14-49-34.png)

- UDP避免了TCP连接建立和终止所需的开销

### 2.7 TIME_WAIT状态

- 最长分节生命期MSL
- TIME_WAIT状态存在的两个理由
  - 可靠地实现TCP全双工连接的终止
  - 允许老的重复分节在网络中消逝

### 2.8 SCTP关联的建立和终止

- 四路握手

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 15-02-45.png)

  - 四路握手结束后，两端各自选择一个主目的地址，当不存在网络故障时，主目的地址将用作数据要发送带的默认目的地

- 关联终止

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 15-06-50.png)

  - SCTP通过放置验证标记值就避免了TCP在TIME_WAIT状态保持整个连接的做法

- SCTP的状态转换图

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 15-09-30.png)

- 观察分组
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 15-10-01.png)

- SCTP选项

### 2.9 端口号

- 使用16位整数的端口号
- 套接字: IP地址和端口号
- 套接字对: 本地IP地址、本地TCP端口号、外地IP地址、外地TCP端口号

### 2.10 TCP端口号与并发服务器

- 并发服务器中主服务器循环通过派生一个子进程来处理每个新的连接
- 监听套接字
- TCP无法仅仅通过查看目的端口号来分离外来的分节到不同的端点，它必须查看套接字对的所有四个元素才能确定由哪个端点接收到达的分节
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 15-34-41.png)

### 2.11 缓冲区大小及其限制

- 当一个IP数据报从某个接口送出时，如果它的大小超过相应链路的MTU,将执行分片
- IPV4主机对其产生的数据报执行分片，IPV4路由器对其转发的数据报执行分片。IPV6只有主机对其产生的数据报执行分片
- 在两个主机之间的路径中最小的MTU称为路径MTU(最大传输单元)
- 最小重组缓冲区大小，IPv4和IPv6的任何实现都必须保证支持的最小数据报大小
- MSS最大分节大小
- TCP输出
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 15-51-43.png)

- UDP输出
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 15-54-42.png)
- SCTP输出
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 15-55-08.png)

### 2.12 标准因特网服务

### 2.13常见因特网应用的协议使用

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 16-06-27.png)

## 第三章　套接字编程简介

- 套接字地址结构
  - 从进程到内核和从内核到进程
- 地址转化函数在地址的文本表达和它们存放在套接字的地址结构中的二进制值之间进行转化， inet_addr和inet_ntoa函数　　inet_pton和inet_ntop函数　它们与所转换的地址类型协议相关

### 3.2 套接字地址结构

- IPV4套接字地址结构

  - 以sockaddr_in命名，定义在<netinet/in.h>头文件中

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 14-24-38.png)

  - 长度字段sin_len,不一定有，涉及路由套接字时才设置和检查它
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 14-31-50.png)

  - IPv4地址和TCP或UDP端口号在套接字地址结构中总是以网络字节序来存储
  - 套接字地址结构仅在给定主机上使用

- 通用套接字地址结构

  - 套接字地址结构以指针的方式传递给套接字函数
  - 对套接字函数的调用，必须要将指向特定于协议的套接字地址结构进行类型强制转换，变成指向某个通用套接字地址结构的指针。
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 14-41-02.png)
  - int bind(int, struct sockaddr*, socklen_t);
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 14-42-19.png)

  - 内核检查sa_family字段的值来确定这个结构的真实类型

- IPV6套接字地址结构

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 14-46-25.png)

  - IPv4的地址族是AF_INET, IPV6的地址族是AF_INET6
  - 结构中字段的先后顺序做过编排

- 新的通用套接字地址结构

  - 新的struct sockaddr_storage足以容纳系统所支持的任何套接字地址结构
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 14-51-41.png)

  - 能满足对齐要求
  - 除了ss_family和ss_len外，sockaddr_storage结构中的其他字段对用户来说是透明的，必须类型强制转换或复制到适合于ss_family字段给出地址类型的套接字地址结构中，才能访问其他字段

- 套接字地址结构的比较

  - 5种套接字地址结构: IPV4 IPV6 Unix域　数据链路　存储
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 14-58-08.png)



### 3.3 值-结果参数

- 从进程到内核传递套接字地址结构的函数有3个: bind  connect sendto
  - connect(sockfd, (SA*) &serv, sizeof(serv));
- 从内核到进程传递套接字地址结构的函数有4个: accept  recvfrom  getsockname  getpeername
  - 其中两个参数是指向某个套接字地址结构的指针和指向表示该结构大小的整数变量的指针
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 15-05-51.png)

### 3.4 字节排序函数

- 小端字节序列和大端字节序列

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 15-22-31.png)

- x86_64-unknown-linux-gnu: little-endian　小端

- 网络协议必须指定一个网络字节序，网际协议首部字段使用大端字节序传送

- 具体实现可以按主机字节序存储套接字地址结构中的各个字段，等到需要在这些字段和协议首部相应字段之间移动时，再在主机字节序和网络字节序之间进行互转

  - 以下函数实现这两种字节序之间的转换
  - htons
  - htonl   返回网络字节序的值
  - ntohs
  - ntohl　返回主机字节序的值
  - 在大端系统里，这四个函数被定义为空宏

### 3.5 字节操纵函数

- 名字以b(表示字节)开头的第一组函数起源于4.2BSD，名字以mem(表示内存)开头的第二组函数起源于ANSI C标准
- bzero 把目标子串中指定数目的字节置为0,常使用该函数把一个套接字地址结构初始化为0
- bcopy 将指定数目的字节从源字节串移到目标字节串
- bcmp　比较
- memset  把目标字节串指定数目的字节置为０
- memcpy　复制
- memcmp 比较

### 3.6 inet_aton inet_addr inet_ntoa函数

- 地址转换函数，在ASCII字符串与网络字节序的二进制之间转换网际地址
- inet_aton inet_addr inet_ntoa在点分十进制与它长度为32位的网络字节序二进制间转换IPV4地址
- inet_aton将C字符串转换成一个32位的网络字节序二进制
- inet_addr进行相同的转换，但不能处理255.255.255.255
- inet_ntoa函数将一个32位的网络字节序二进制IPV4地址转换成相应的点分十进制数，由该函数的返回值所指向的字符串驻留在静态内存中，该函数是不可重入的

### 3.7 inet_pton和inet_ntop函数

- 对于IPv4和IPV6都适用
- inet_pton将字符串转换成二进制
- inet_ntop 从数值格式转换成表达式
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 16-31-31.png)

  

- snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));  写入到buff中，指定了缓冲区大小

### 3.8 sock_ntop和相关函数

- 自行编写的函数，以指向某个套接字地址结构的指针为参数，查看该结构的内部，然后调用适当的函数返回该地址的表达格式
- char* sock_ntop(const struct sockaddr* sockaddr, socklen_t addrlen);
- sockaddr指向一个长度为addrlen的套接字地址结构，用它自己的静态缓冲区来保存结果，而指向该缓冲区的一个指针就是它的返回值
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 16-56-07.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 16-56-55.png)

- sock_bind_wild
- sock_cmp_addr
- sock_cmp_port
- sock_get_port
- sock_ntop_host
- sock_set_addr
- sock_set_port
- sock_set_wild

### 3.9 readn wirten readline函数

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 17-01-43.png)

- 字节流套接字上调用read和write输入或输出的字节数可能比请求的数量少，原因在于内核中用于套接字的缓冲区已经到达了极限，此时需要再次调用read和write以输入或输出剩余的字节
- 提供的3个函数均返回读或写的字节数
  - readn
  - written
  - readline
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 17-07-51.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 17-09-52.png)

- ENTER错误，表示系统调用被一个捕获的信号中断
- stdio缓冲区的状态是不可见的
- 在readline.c中使用静态变量实现跨相继函数调用的状态信息维护，其结果是这些函数变得不可重入或非线程安全了



## 第四章　基本套接字编程

- 客户/服务器程序
- 并发服务器
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 09-46-53.png)

### 4.2 socket函数

- int socket(int family,int type, int protocal)
- TCP是一个字节流协议，仅支持SOCK_STREAM套接字
- 路由套接字是内核中路由表的接口
- 密钥套接字是与内核中密钥表的接口
- 套接字描述符与文件描述符类似　sockfd
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 09-48-52.png)

- type参数指明套接字类型
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 09-49-47.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 09-51-44.png)

- AF_XXX和PF_XXX
  - AF_前缀表示地址族
  - PF_前缀表示协议族

### 4.3 connect函数

- TCP客户用connect函数建立与TCP服务器的连接
- int connect(int sockfd, const struct sockaddr* servaddr, socklen_t addrlen);
- 套接字地址结构必须含有服务器的IP地址和端口号
- 客户在调用函数connect前不必非得调用bind函数，内核会确定源IP地址，并选择一个临时端口作为源端口
- 如果是TCP套接字，调用connect函数将激发TCP的三路握手过程，而且仅在连接建立成功或出错时才返回
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 10-07-19.png)

- 一个没有运行时间获取服务器程序的主机，服务器主机立即响应一个RST分节　
  - connect error: Connection refused
- 指定本地子网上并不存在的一个IP地址，当客户主机发出ARP请求时，它将永远收不到ARP响应
  - connect error: Connection timed out
- 指定一个因特网中不可到达的IP地址，用tcpdump观察分组，发现路由器返回了主机不可达的ICMP错误
  - connect error: NO route to host
- 若connect失败则该套接字不再可用，必须关闭



### 4.4 bind 函数

- bind函数把一个本地协议地址赋予一个套接字
- 对于网际协议，协议地址是IPV4或IPV6的地址与TCP或UDP端口号的组合
- 对于TCP,调用bind函数可用指定一个端口号，或指定一个IP地址，也可以两者都指定，还可以都不指定
  - 如果一个TCP客户或服务器未曾调用bind绑定一个端口，则内核就要为相应的套接字选择一个临时端口
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 14-05-03.png)



- 对于IPV4,　通配地址由常值INADDR_ANY来指定，其值一般为0,告知内核去选择IP地址
- 对于IPV6, 系统预先分配in6addr_any变量并将其初始化为常值IN6ADDR_ANY_INIT，　通配地址
- 为了得到内核所选择的临时端口值，必须调用函数getsockname来返回协议地址
- 进程捆绑非通配IP地址到套接字的常见例子是为多个组织提供Web服务器的主机上
  - 把子网的所有IP地址都定义成单个网络接口的别名(使用ifconfig命令的alias选项)
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 14-18-54.png)

- 一个常见错误是EADDRINUSE(地址已使用)



### 4.5 listen函数

- 仅由TCP服务器调用

  - 当socket函数创建一个套接字时，它被假设为一个主动套接字，listen函数把一个未连接的套接字转换成一个被动套接字，指示内核应接受指向该套接字的连接请求

- int listen(int sockfd, int backlog);   backlog指示了最大连接个数

- 内核为任何一个给定的监听套接字维护两个队列:

  - 未完成连接队列
  - 已完成连接队列
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 14-27-00.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 14-29-05.png)

  - 当进程调用accept时，已完成连接队列中的队头项将返回给进程，或者如果该队列为空，那么该进程将被投入睡眠，直到TCP在该队列中放入一项才唤醒它
  - 不要把backlog定义为0
  - 允许通过环境变量LISTENQ覆写由调用者指定的值
  - 当一个客户SYN到达时，若这些队列是满的，TCP就忽略该分节
  - 在三路握手完成之后，但在服务器调用accept之前到达的数据应由服务器TCP排队，最大数据量为相应已连接套接字的接受缓冲区大小

### 4.6 accept函数

- 当进程调用accept时，已完成连接队列中的队头项将返回给进程，或者如果该队列为空，那么该进程将被投入睡眠，直到TCP在该队列中放入一项才唤醒它
- int accept(int sockfd, struct sockaddr*cliaddr,socklen_t *addrlen);
- 参数cliaddr和addrlen用来返回已连接的对端进程(客户)的协议地址，adrlen是值-结果参数。调用前，*addrlen所引用的整数值置为由cliaddr所指的套接字地址结构的长度，返回时，该整数值为由内核存放在该套接字地址结构内的确切字节数
- 如果accept成功，其返回值为由内核自动生成的一个全新描述符，代表与所返回客户的TCP连接，即已连接套接字描述符
- 一个服务器仅创建一个监听套接字，在服务器的生命期内一直存在，当服务器完成对某个给定客户的服务时，相应的已连接套接字就被关闭
- 可以把cliaddr和addrlen置为NULL
- 环回地址127.0.0.1

### 4.7 fork和exec函数

- 父进程中调用fork之前打开的所有描述符在fork返回后由子进程分享
- 父进程调用accept 之后调用fork,所接受的已连接套接字随后就在父进程与子进程之间共享，通常情况下，子进程接着读写这个已连接套接字，父进程则关闭这个已连接套接字
- 进程调用exec之前打开的描述符通常跨exec继续保持打开，本默认行为可以使用fcnt1设置FD_CLOEXEC描述符标志禁止掉，inetd服务器就利用了这个特性

### 4.8 并发服务器

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 15-14-15.png)

- 每个文件或套接字都有一个引用计数，引用计数在文件表中维护，它是当前打开着的引用该文件或套接字的描述符的个数
- fork返回后，这两个描述符就在父进程与子进程间共享(也就是被复制)，因此这两个套接字相关联的文件表项中各自的访问计数均为2
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 15-21-51.png)

### 4.9 close函数

- 用来关闭套接字，终止TCP连接
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 15-23-54.png)

### 4.10 getsockname和getpeername函数

- 返回与某个套接字关联的本地协议地址　getsockname
- 返回与某个套接字关联的外地协议地址　getpeername
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-08 15-28-25.png)

- 已连接套接字描述符跨exec继续保持开放，调用getpeername,用于获取客户的IP地址和端口号
- 大多数TCP服务器是并发的，大多数UDP服务器是迭代的



## 第五章　TCP客户/服务器程序示例

- 回射服务器

### 5.2 TCP回射服务器程序: main函数

### 5.3 TCP回射服务器程序: str_echo函数

- 接收到客户的FIN将导致服务器子进程的read函数返回0

### 5.4 TCP回射客户程序: main函数

### 5.5 TCP回射客户程序: str_cli函数

### 5.6 正常启动

- netstat -a  监听套接字的状态，netstat用*表示一个为0的IP地址或为0的端口号

- ps  -o pid,ppid,tty,stat,args,wchan 查看进程状态
- pts/6  表示伪终端号6
- STAT列为S，表明进程在为等待某些资源而睡眠，进程处于睡眠状态时WCHAN列出相应的条件
- Linux在进程阻塞于accept或connect时，输出wait_for_connect,在进程阻塞于套接字输入或输出时，输出tcp_data_wait, 在进程阻塞于终端I/O时，输出read_chan
-  netstat -a | grep 9877

### 5.7 正常终止

- Ctrl+D表示EOF字符
- 僵死状态Z表示

### 5.8 POSIX信号处理

- 通过调用sigaction函数来设定一个信号的处置
  - 提供信号处理函数
  - 可以把某个信号的处置设定为SIG_IGN来忽略它
  - 可以把某个信号的处置设定为SIG_DFL来启用它的默认处置
- signal函数
  - 定义自己的signal函数，只是调用POSIX的sigaction函数
  - 构造程序是指使用make工具把源程序和/或目标程序编译链接成可执行程序，构造其中各个程序的makefile文件
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 15-53-01.png)



### 5.9 处理SIGCHLD信号

- 处理僵死进程

- 在信号处理函数中调用printf这样的标准I/O函数是不合适的

- 若信号是在父进程阻塞于慢系统调用(accept)时由父进程捕获的，内核就会使accept返回一个ENTER错误(被中断的系统调用)，而父进程不处理该错误，于是终止

- 处理被中断的系统调用

  - 慢系统调用: 可能永远阻塞的系统调用
  - 当阻塞于某个慢系统调用的一个进程捕获某个信号且相应信号处理函数返回时，该系统调用可能返回一个ENTER错误，有些内核自动重启某些被中断的系统调用
  - 自己重启被中断的系统调用
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 16-26-21.png)

  - 当connect被一个捕获的信号中断而且不自动重启时，我们就必须调用select来等待连接完成

### 5.10 wait和waitpid函数

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 16-30-18.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 16-30-39.png)

- 建立一个信号处理函数并在其中调用wait并不足以防止出现僵死进程，由于Unix信号是不排队的。可以在一个循环内调用waitpid处理，以获取所有已终止子进程的状态，指定WNOHANG选项，告知waitpid在有尚未终止的子进程在运行时不要阻塞
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 16-39-13.png)

- 网络编程遇到的三种情况
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 16-41-20.png)

### 5.11 accept返回前连接终止

- 可设置SO_LINGER套接字选项以产生RST
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 16-43-44.png)

- POSIX指出返回一个错误给服务器进程，errno值是ECONNABORTED

### 5.12 服务器进程终止

- 客户TCP接收到FIN只是表示服务器进程已关闭了连接的服务器端，从而不向其中发送任何数据而已，FIN接收并没有告知客户TCP服务器进程已经终止
- 当服务器TCP接收到来自客户的数据时，既然先前打开的那个套接字的进程已经终止，于是响应一个RST
- 当FIN到达套接字时，客户正阻塞在fgets调用上，客户实际上在应对两个描述符—套接字和用户输入，它不能单纯阻塞在这两个源中某个特定源上，而是应该阻塞在其中任何一个源上，正是select和poll的编写目的之一

### 5.13 SIGPIPE信号

- 当一个进程向某一个已收到RST的套接字执行写操作时，内核向该进程发送一个SIGPIPE信号，该信号的默认行为是终止进程，因此进程必须捕获它
- 写一个已接收了FIN的套接字不成问题，但是写一个已接收了RST的套接字则是一个错误

### 5.14 服务器主机崩溃



### 5.15 服务器主机崩溃后重启

- 当服务器主机崩溃后重启时，它的TCP丢失了崩溃前的所有连接信息，因此服务器TCP对于所收到的来自客户的数据分节响应一个RST
- 当客户TCP收到该RST时，客户正阻塞于readline调用，导致该调用返回ECONNRESET错误

### 5.16 服务器主机关机

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 17-22-04.png)

### 5.17 TCP程序

### 5.18 数据格式

- 在客户和服务器之间传递文本串

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 17-26-09.png)

  - sscanf函数
  - snprintf函数

- 在客户与服务器之间传递二进制结构

  - 注意两个主机的体系结构可能不同
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-11 17-32-49.png)

## 第六章　I/O复用: select和poll函数

- 进程需要一种预先告知内核的能力，使得内核一旦发现进程指定的一个或多个I/O条件就绪，它就通知进程，这个能力称为I/O复用，是由select和poll函数支持的
- I/O复用的场合
  - 当客户使用多个描述符(如交互输入和网络套接字)
  - 一个TCP服务器既要处理监听套接字，又要处理已连接套接字
  - 一个服务器既要处理TCP,又要处理UDP
  - 一个服务器要处理多个协议或多个服务

### 6.2 I/O模型

- Unix下可用的5种I/O模型

  - 阻塞式I/O
  - 非阻塞式I/O
  - I/O复用(select和poll)
  - 信号驱动式I/O(SIGIO)
  - 异步I/O

- 一个输入操作

  - 等待数据准备好(从网络中到达)
  - 从内核向进程复制

- 阻塞式I/O模型

  - 默认情况下，所有套接字都是阻塞的
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 14-39-09.png)

  - 进程调用recvform, 其系统调用直到数据报到达且被复制到应用进程的缓冲区中或者发生错误才返回，进程在从调用recvfrom开始到它返回的整段时间内是被阻塞的，成功返回后，进程开始处理数据报

- 非阻塞式I/O模型

  - 进程把一个套接字设置成非阻塞是在通知内核: 当所请求的I/O操作非得把本进程投入睡眠才能完成时，不要把本进程投入睡眠，而是返回一个错误
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 14-48-10.png)

- I/O复用模型

  - 调用select或poll, 阻塞在这两个系统调用中的某一个之上，而不是阻塞在真正的I/O系统调用上
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 14-51-58.png)

  - 使用select的优势在于我们可以等待多个描述符就绪
  - 在多线程中使用阻塞式I/O,　这样每个线程都可以自由地调用诸如recvfrom之类的阻塞式I/O系统调用

- 信号驱动式I/O模型

  - 让内核在描述符就绪时发送SIGIO信号通知我们
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 14-55-55.png)

  - 等待数据报期间进程不被阻塞

- 异步I/O模型

  - 告知内核启动某个操作，并让内核在整个操作完成后通知我们
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 14-59-33.png)

  - 调用aio_read函数，给内核传递描述符，缓冲区指针，大小，文件偏移，该系统调用立即返回，而且在等待I/O完成期间，进程不被阻塞

- 各种I/O模型的比较

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-03-01.png)

- 同步I/O和异步I/O
  - 同步I/O 导致请求进程阻塞，直到I/O操作完成，　前四种都为同步I/O
  - 异步I/O不导致请求进程阻塞

### 6.3 select函数

- 该函数允许进程指示内核等待多个事件中的任何一个发生，并且只有在一个或多个事件发生或经历一段指定的时间后才唤醒它
- 任何描述符都可以使用select来测试
- int select(int maxfdp1, fd_set*readset, fd_set \*writeset, fd_set \*exceptset, const struct timeval \* timeout )
- timeout参数
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-11-02.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-14-13.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-15-46.png)

- 分配一个fd_set数据类型的描述符集，并用这些宏设置或测试该集合中的每一位
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-17-28.png)

- 这三个参数都是值-结果参数，该函数返回时，结果将指示哪些描述符已就绪，使用FD_ISSET宏来测试fd_set数据类型中的描述符，任何与未就绪描述符对应的位返回时均清成0

- 描述符就绪条件

  - 一个套接字准备读
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-27-46.png)

  - 一个套接字准备写
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-30-27.png)

  - 如果一个套接字存在带外数据或者仍处于带外标记，那么它有异常条件待处理
  - 当某个套接字上发生错误时，它将由select标记为既可读又可写
  - 接收低水位标记和发送低水位标记: 允许应用进程控制在select返回可读或可写条件之前有多少数据可读或有多大空间可用于写
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-35-07.png)－

- select的最大描述符数
  - 增大描述符集大小的唯一方法是先增大FD_SETSIZE的值，再重新编译内核，不重新编译内核而改变其值是不够的

### 6.4 str_cli函数

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-40-25.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-41-40.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 15-46-22.png)

### 6.5 批量输入

- 在批量方式下，标准输入中的EOF并不意味着我们同时也完成了从套接字的读入，可能仍有请求在去往服务器的路上，或者仍有应答在返回客户的路上

- 需要一种关闭TCP连接其中一半的方法，给服务器发送一个FIN,　告诉它我们已经完成了数据发送，但是仍然保持套接字描述符打开以便读取，由shutdown函数完成

- 为了提升性能而引入缓冲机制增加了网络应用程序的复杂性

  - fgets读取输入，使可用的文本输入行被读入到stdio所用的缓冲区中，然而fgets只返回一行，其余的仍在stdio缓冲区中
  - 混合使用select和stdio容易出错
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 16-08-44.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 16-10-01.png)

### 6.6 shutdown函数

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 16-16-13.png)

- int shutdown(int sockfd, int howto)
  - howto的值
    - SHUT_RD 关闭连接的读这一半
    - SHUT_WR　关闭连接的写这一半
    - SHUT_RDWR 连接的读半部和写半部都关闭



### 6.7 str_cli函数

```c++
#include	"unp.h"

void
str_cli(FILE *fp, int sockfd)
{
	int			maxfdp1, stdineof;
	fd_set		rset;
	char		buf[MAXLINE];
	int		n;

	stdineof = 0;
	FD_ZERO(&rset);
	for ( ; ; ) {
		if (stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */
			if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
				if (stdineof == 1)
					return;		/* normal termination */
				else
					err_quit("str_cli: server terminated prematurely");
			}

			Write(fileno(stdout), buf, n);
		}

		if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
			if ( (n = Read(fileno(fp), buf, MAXLINE)) == 0) {
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR);	/* send FIN */
				FD_CLR(fileno(fp), &rset);
				continue;
			}

			Writen(sockfd, buf, n);
		}
	}
}
```



### 6.8 TCP回射服务器程序

- 重新成使用select来处理任意个客户的单进程程序

- 接收到FIN 或　EOF,  read返回的值是0

- ```c++
  /* include fig01 */
  #include	"unp.h"
  
  int
  main(int argc, char **argv)
  {
  	int					i, maxi, maxfd, listenfd, connfd, sockfd;
  	int					nready, client[FD_SETSIZE];
  	ssize_t				n;
  	fd_set				rset, allset;
  	char				buf[MAXLINE];
  	socklen_t			clilen;
  	struct sockaddr_in	cliaddr, servaddr;
  
  	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
  
  	bzero(&servaddr, sizeof(servaddr));
  	servaddr.sin_family      = AF_INET;
  	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  	servaddr.sin_port        = htons(SERV_PORT);
  
  	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
  
  	Listen(listenfd, LISTENQ);
  
  	maxfd = listenfd;			/* initialize */
  	maxi = -1;					/* index into client[] array */
  	for (i = 0; i < FD_SETSIZE; i++)
  		client[i] = -1;			/* -1 indicates available entry */
  	FD_ZERO(&allset);
  	FD_SET(listenfd, &allset);
  /* end fig01 */
  
  /* include fig02 */
  	for ( ; ; ) {
  		rset = allset;		/* structure assignment */
  		nready = Select(maxfd+1, &rset, NULL, NULL, NULL);
  
  		if (FD_ISSET(listenfd, &rset)) {	/* new client connection */
  			clilen = sizeof(cliaddr);
  			connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
  #ifdef	NOTDEF
  			printf("new client: %s, port %d\n",
  					Inet_ntop(AF_INET, &cliaddr.sin_addr, 4, NULL),
  					ntohs(cliaddr.sin_port));
  #endif
  
  			for (i = 0; i < FD_SETSIZE; i++)
  				if (client[i] < 0) {
  					client[i] = connfd;	/* save descriptor */
  					break;
  				}
  			if (i == FD_SETSIZE)
  				err_quit("too many clients");
  
  			FD_SET(connfd, &allset);	/* add new descriptor to set */
  			if (connfd > maxfd)
  				maxfd = connfd;			/* for select */
  			if (i > maxi)
  				maxi = i;				/* max index in client[] array */
  
  			if (--nready <= 0)
  				continue;				/* no more readable descriptors */
  		}
  
  		for (i = 0; i <= maxi; i++) {	/* check all clients for data */
  			if ( (sockfd = client[i]) < 0)
  				continue;
  			if (FD_ISSET(sockfd, &rset)) {
  				if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
  						/*4connection closed by client */
  					Close(sockfd);
  					FD_CLR(sockfd, &allset);
  					client[i] = -1;
  				} else
  					Writen(sockfd, buf, n);
  
  				if (--nready <= 0)
  					break;				/* no more readable descriptors */
  			}
  		}
  	}
  }
  /* end fig02 */
  ```

- 当一个服务器在处理多个客户时，它不能阻塞于只与单个客户相关的函数调用，否则可能导致服务器被挂起，拒绝为所有其他客户提供服务，这就是拒绝服务型攻击。可能的解决办法

  - 使用非阻塞式I/O
  - 让每个客户由单独的控制线程提供服务
  - 对I/O操作设置一个超时

### 6.9 pselect函数

- 使用timespec结构
- 增加了第六个参数: 一个指向信号掩码的指针，该参数允许程序先禁止递交某些信号，再测试由这些当前被禁止信号的信号处理函数设置的全局变量，然后调用pselect,重新设置信号掩码
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-13 17-06-39.png)

### 6.10 poll函数

- poll函数提供的功能与select类似，不过在处理流设备时，它能够提供额外的信息
- int poll(struct pollfd* fdarray, unsigned long nfds, int timeout);
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-13 17-11-02.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-13 17-12-19.png)

- poll识别三类数据: 普通、优先级带　高优先级　出自于基于流的实现
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-13 17-15-18.png)

### 6.11 TCP回射服务器程序

```c++
/* include fig01 */
#include	"unp.h"
#include	<limits.h>		/* for OPEN_MAX */

int
main(int argc, char **argv)
{
	int					i, maxi, listenfd, connfd, sockfd;
	int					nready;
	ssize_t				n;
	char				buf[MAXLINE];
	socklen_t			clilen;
	struct pollfd		client[OPEN_MAX];
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;
	for (i = 1; i < OPEN_MAX; i++)
		client[i].fd = -1;		/* -1 indicates available entry */
	maxi = 0;					/* max index into client[] array */
/* end fig01 */

/* include fig02 */
	for ( ; ; ) {
		nready = Poll(client, maxi+1, INFTIM);

		if (client[0].revents & POLLRDNORM) {	/* new client connection */
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
#ifdef	NOTDEF
			printf("new client: %s\n", Sock_ntop((SA *) &cliaddr, clilen));
#endif

			for (i = 1; i < OPEN_MAX; i++)
				if (client[i].fd < 0) {
					client[i].fd = connfd;	/* save descriptor */
					break;
				}
			if (i == OPEN_MAX)
				err_quit("too many clients");

			client[i].events = POLLRDNORM;
			if (i > maxi)
				maxi = i;				/* max index in client[] array */

			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}

		for (i = 1; i <= maxi; i++) {	/* check all clients for data */
			if ( (sockfd = client[i].fd) < 0)
				continue;
			if (client[i].revents & (POLLRDNORM | POLLERR)) {
				if ( (n = read(sockfd, buf, MAXLINE)) < 0) {
					if (errno == ECONNRESET) {
							/*4connection reset by client */
#ifdef	NOTDEF
						printf("client[%d] aborted connection\n", i);
#endif
						Close(sockfd);
						client[i].fd = -1;
					} else
						err_sys("read error");
				} else if (n == 0) {
						/*4connection closed by client */
#ifdef	NOTDEF
					printf("client[%d] closed connection\n", i);
#endif
					Close(sockfd);
					client[i].fd = -1;
				} else
					Writen(sockfd, buf, n);

				if (--nready <= 0)
					break;				/* no more readable descriptors */
			}
		}
	}
}
/* end fig02 */
```

## 第七章　套接字选项

- 获取和设置影响套接字的选项
  - getsockopt和setsockopt函数
  - fnct1函数
  - icot1函数

### 7.2 getsockopt和setsockopt函数

- 仅用于套接字
- 套接字选项分为两大基本类型
  - 一是启用或禁止某个特性的二元选项(标志选项)
  - 二是取得并返回我们可以设置或检查的特定值的选项(值选项)
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 14-13-53.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 14-16-35.png)

### 7.3 检查选项是否受支持并获取默认值

- 创建一个用于测试选项的套接字，测试套接字层，TCP层和IPv4层套接字选项所用的是一个IPv4的TCP套接字
- 测试IPv6层套接字选项所用的是一个IPv6的TCP套接字，测试SCTP层套接字选项所用的上一个IPv4的SCTP套接字

### 7.4 套接字状态

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 15-17-14.png)

### 7.5 通用套接字选项

- 这些选项是协议无关的

- SO_BROADCAST

  - 本选项开启或禁止进程发送广播消息

- SO_DEBUG

  - 仅由TCP支持，当给一个TCP套接字开启本选项时，内核将为TCP在该套接字发送和接收的所有分组保留详细跟踪信息，保存在内核的某个环形缓冲区汇中

- SO_DONTROUTE

  - 规定外出的分组将绕过底层协议的正常路由机制

- SO_ERROR

  - 当一个套接字发生错误时，so_error的变量，待处理错误，当进程调用read且没有数据返回时，如果so_error为非0值，那么read返回-1且errno被置为so_error的值
  - 一个套接字上出现的待处理错误一旦返回给用户进程，它的so_errnor就得复位为0

- SO_KEPPALIVE

  - 保持存活选项
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 15-37-43.png)

  - 一般由服务器使用，服务器花大部分时间阻塞在等待穿越TCP连接的输入上
  - 保持存活选项将检测出半开连接并终止它们
  - 应用进程自己也可以实现超时
  - 检测各种TCP条件的方法
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 15-45-47.png)

- SO_LINGER

  - 指定close函数对面向连接的协议如何操作，默认操作是close立即返回，但是如果有数据残留在套接字发送缓冲区，系统将试着把这些数据发送给对端
  - struct linger{ int l_onoff; int l_linger}
  - 应用进程检查close的返回值是非常重要的，因为如果在数据发送完并被确认前延迟时间到，close将返回EWOULDBLOCK错误，套接字发送缓冲区中的任何残留数据都被丢弃
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 15-56-03.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 16-02-56.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 16-03-57.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 16-04-20.png)

  - 设置SO_LINGER套接字选项后，close的成功返回只是告诉我们先前发送的数据和FIN已由对端TCP确认，而不能告诉我们对端应用进程是否已读取数据
  - 让客户知道服务器已读取数据的一个方法是改为调用shutdown,而不是调用close,并等待对端连接的当地端
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 16-10-57.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 16-12-06.png)

  - 应用级ACK
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 16-14-57.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-14 16-17-12.png)

- SO_OOBINLINE
  - 带外数据将被留在正常的输入队列中
- SO_RCVBUF和SO_SNDBUF
  - TCP套接字接收缓冲区不可能溢出，因为不允许对端发出超过本端所通告窗口大小的数据
  - 对UDP,当接收到的数据报装不进套接字接收缓冲区时，该数据报被丢弃
  - TCP的窗口规模选项是在SYN分节得到的，SO_RCVBUF必须在调用connect之前设置，对于服务器，必须在调用listen之前设置
  - 至少是MSS值的4倍
  - TCP必须为每个分节保留一个副本，直到接收到来自服务器的相应ACK
- SO_RCVLOWAT和SO_SNDLOWAT
  - 接收低水位标记
  - 发送低水位标记
  - 由select函数使用
  - UDP套接字的发送缓冲区中可用空间的字节数不变，UDP不为应用进程传递给它的数据保留副本
- SO_RCVTIMEO和SO_SNDTIMEO
  - 给套接字的接收和发送设置一个超时值
- SO_REUSEADDR和SO_REUSEPORT
  - 四个不同的功能
- SO_TYPE
  - 返回套接字的类型
- SO_USELOOPBACK
  - 仅用于路由域的套接字
  - 开启时，相应套接字将接收在其上发送的任何数据报的一个副本