# LKD

## 第一章　Linux内核简介

### 1.1 Unix的历史

- Unix很简洁，仅仅提供几百个系统调用
- 很多东西都被当作文件对待
- Unix的内核和相关的系统工具软件是用C语言编写而成
- 进程创建迅速，稳定的进程间通信元语

### 1.2 Linux简介

- Linux是类Unix系统，但它不是Unix
- 实现了Unix的API, 但没有直接使用Unix的源代码

### 1.3 操作系统和内核简介

- 处理器的活动
  - 运行于用户空间，执行用户进程
  - 运行于内核空间，处于进程上下文，代表某个特定的进程执行
  - 运行于内核空间，处于中断上下文，与任何进程无关，处理某个特定的中断
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-01 17-38-31.png)

### 1.4 Linux内核和传统Unix内核的比较

- Unix内核几乎都是一个不可分割的静态可执行库

- 单内核

- 微内核

- Linux内核运行在单独的内核地址空间上

- Linux与Unix的区别

  - Linux支持动态加载内核模块

  - Linux支持对称多处理SMP

  - Linux内核可以抢占

  - Linux内核并不区分线程和其他的一般进程

  - Linux提供具有设备类的面向对象的设备模型

    

### 1.5 Linux内核版本

- 稳定的和处于开发中的
- 副版本号如果是偶数就是稳定版，如果是奇数，就是开发版



## 第二章　从内核出发

### 2.1 获取内核源码

- 内核源码一般安装在/usr/src/linux目录下

  - <https://www.kernel.org/>
  - <https://github.com/torvalds/linux>
  - 建立自己的主目录，仅以root身份安装新内核，/usr/src/linux目录不要改变
- 使用补丁
  - 要应用增量补丁，从内部源码树开始，运行　patch -p1 <../patch-x.y.z
  - 一个给定版本的内核补丁总是打在前一个版本上

### 2.2 内核源码树

- 内核源码树的根目录描述

### 2.3 编译内核

- 配置内核
  - yes选项表示把代码编译进主内核映像中，而不是作为一个模块
  - make config
  - make menuconfig
  - make gconfig
  - make defconfig
- 衍生多个编译作业
- 安装新内核
  - 如何安装和体系结构以及启动引导工具相关

### 2.4 内核开发的特点

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-05 20-59-13.png)

- 无libc库和标准头文件
  - 大多数常用的C库函数在内核中都得到了实现
  - 内核代码没有实现printf函数，但提供了printk()函数

- GNU C
  - 涵盖了ISO 99标准和GNU C扩展特性
  - 内联函数
  - 内联汇编
    - gcc支持在C函数中嵌入汇编指令
    - asm指令
  - 分支声明
    - likely
    - unlikely
  - 没有内存保护机制
    - 内核中发生的内存错误会导致oops
    - 内核中的内存不分页，每用一个字节，物理内存就减少一个字节
    - 不要使用浮点数操作
    - 容积小而固定的栈
  - 同步和并发
  - 可移植

## 第三章　进程管理

- 进程管理是所有操作系统的心脏所在

### 3.1 进程

- 进程就是处于执行期的程序以及相关资源的总称

  - 线程是在进程中活动的对象，每个线程都拥有一个独立的程序计数器、进程栈和一组进程寄存器

  - 内核调度的对象是线程，而不是进程

  - 在Linux系统中，对线程和进程并不特别区分

  - 进程提供两种虚拟机制: 虚拟处理器和虚拟内存

    - 虚拟处理器让进程觉得自己独享处理器
    - 虚拟内存让进程觉得自己拥有整个系统的所有内存资源

    - 在线程之间可以共享虚拟内存，但每个都拥有各自的虚拟处理器

  - 在Linux内核中，fork实际上是由clone系统调用实现的

### 3.2 进程描述符及任务结构

- 内核把进程的列表存放在任务队列的双向循环链表中，每一项都是task_struct，称为进程描述符的结构，包含进程的所有信息
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 20-02-21.png)

  

- 分配进程描述符
  - Linux通过slab分配器分配task_struct结构，在栈底创建一个新的结构struct thread_info
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 20-06-41.png)

  

  

- 进程描述符的存放
  - 内核中大部分处理进程的代码都是直接通过task_struct进行的
  - x86的体系结构在内核栈的尾端创建thread_info结构，通过计算偏移间接地查找task_struct结构
- 进程状态
  - 进程描述符的state域描述了进程的当前状态
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 20-16-35.png)

- 设置当前进程状态
- 进程上下文
  - 当一个程序执行了系统调用或者触发了某个异常，它就陷入了内核空间，称内核代表进程执行并处于进程上下文中
  - 在中断上下文中，系统不代表进程执行，而是执行一个中断处理程序
- 进程家族树
  - 所有的进程都是PID为1的init进程的后代，内核在系统启动的最后阶段启动init进程，该进程读取系统的初始化脚本并执行其他相关程序，最终完成系统启动的整个过程
  - init进程的进程描述符是作为init_task静态分配的

### 3.3 进程创建

- fork  exec
- 写时拷贝
  - Linux的fork使用写时拷贝页实现，内核并不复制整个进程地址空间，而是让父进程和子进程共享同一个拷贝，只有在需要写入时，数据才会被复制。
- fork
  - Linux通过clone系统调用实现fork
  - clone调用do_fork, 又调用copy_process()
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 20-40-09.png)

- vfork
  - 除了不拷贝父进程的页表项外，vfork与fork相同

### 3.4 线程在Linux中的实现

- 线程提供了在同一程序内共享内存地址空间运行的一组线程，可以共享打开的文件和其他资源
- 在Linux中，线程仅仅被视为与其他进程共享某些资源的进程，每个线程都拥有唯一的task_struct, 在内核中，看起来像是一个普通的进程
- Windows Solaris等系统都在内核中提供了专门支持线程的机制，线程被抽象为一种耗费较少资源，运行迅速的执行单元。　但是对于Linux，线程只是一种进程间共享资源的手段
- **例如，一个包含四个线程的进程，在专门线程支持的系统中，通常会有一个包含指向四个不同线程的指针的进程描述符，负责描述共享资源，线程本身再去描述它独占的资源。在Linux中，仅仅创建四个进程描述符task_struct，指定了某些共享资源**
- 创建线程
  - 和进程创建类似，在调用clone时需要传递一些参数标志来指明需要共享的资源
    - clone(CLONE_VM | CLONE_FS | CLONE_FILES| CLONE_SIGHAND,0)  共享地址空间，文件系统资源，文件描述符，信号处理程序
  - clone(SIGCHLD,0 ) 普通的fork的实现
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 20-57-25.png)

- 内核线程
  - 独立运行在内核空间的标准进程
  - 没有独立的地址空间
  - 只在内核空间运行
  - ps -ef 可查看内核线程
  - 由kthread内核进程通过clone()系统调用而创建的
  - 内核线程启动后一直运行直到do_exit退出或调用kthread_stop退出

### 3.5 进程终结

- do_exit

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 21-06-55.png)

  - 处于EXIT_ZOMBIE退出状态，它所占用的所有内存就是内核栈、thread_info结构和task_struct结构，此时进程存在的唯一目的就是向它的父进程提供信息，父进程检索到信息后，或者通知内核那是无关的信息后，由进程所持有的剩余内存被释放

- 删除进程描述符

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-06 21-12-50.png)

- 孤儿进程
  - 试图找到进程所在的线程组内的其他进程，如果线程组内没有其他的进程，它就找到并返回的是init进程
  - init进程会例行调用wait来检查其子进程，清除所有与其相关的僵死进程

## 第四章　进程调度

### 4.1 多任务

- Linux提供了抢占式多任务系统，由调度程序决定什么时候停止一个进程的运行

### 4.2 Linux的进程调度

- O(1)调度程序
- 完全公平调度算法　CFS

### 4.3 策略

- I/O消耗型和处理器消耗型的进程
  - 多数用户图形界面程序(GUI)都属于I/O密集型
- 进程优先级
  - 第一种: Linux采用nice值，范围是-20到+19
  - 第二种: 实时优先级
  -  ps -eo state,uid,pid,rtprio     RTPRIO列为实时优先级，-表示不是实时进程
- 时间片
  - 表明进程在被抢占前所能持续运行的时间
- 调度策略的活动

### 4.4 Linux调度算法

- 调度器类
  - Linux调度器是以模块方式提供的，每个调度器都有一个优先级
  - 完全公平调度(CFS)是一个针对普通进程的调度类
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 21-04-54.png)
- Unix系统中的进程调度
  - 给定高nice值的进程往往是后台进程，且多是计算密集型的，而普通优先级的进程则更多是前台任务
  - 分配绝对的时间片引发的固定的切换频率，给公平性造成了很大变数，CFS完全摒弃时间片而是给进程一个处理器使用比重
- 公平调度
  - CFS的做法是允许每个进程运行一段时间，循环轮转，选择运行最少的进程作为下一个运行进程，而不再采用分配给每个进程时间片的做法了
  - 目标延迟
  - CFS引入每个进程获得的时间片底线，称为最小粒度

### 4.5 Linux调度的实现

- 时间记账

  - CFS不再有时间片的概念，但它必须维护每个进程运行的时间记账
  - 调度器实体结构
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 20-37-55.png)

  - 调度器实体结构作为一个名为se的成员变量，嵌入在进程描述符内
  - 虚拟实时
    - vruntime变量存放进程的虚拟运行时间，所有可运行进程总数的标准化
    - update_curr函数实现了该记账功能
    - update_curr计算了当前进程的执行时间，再讲其传给_update_curr,再根据可运行进程总数对运行时间进行加权计算，最终将权重值与当前运行进程的vruntime相加
    - update_curr是由系统定时器周期性调用的

- 进程选择

  - 当CFS需要选择下一个运行进程时，它会挑一个具有最小vruntime的进程
  - CFS使用红黑树来组织可运行进队列，并利用其迅速找到最小vruntime值的进程
  - 挑选下一个任务
    - _pick_next_entity
    - 红黑树最左边叶子结点对应的进程
  - 向树中加入进程
    - CFS如何将进程加入rbtree中，以及如何缓存最左叶子结点，发生在进程变为可运行状态或通过fork调用第一次创建进程时
    - enqueue_entity函数
    - _enqueue_entity函数进行插入操作
  - 从树中删除进程
    - CFS从红黑树删除进程，发生在进程阻塞或者终止时
    - dequeue_entity
    - _dequeue_entity

- 调度器入口

  - 进程调度的主要入口点是函数schedule(),该函数会找到一个最高优先级的调度类(有一个可运行队列)，问它谁才是下一个该运行的进程
  - pick_next_task会以优先级为序，从高到低，检查每一调度器类，并从最高优先级的调度器类，选择最高的优先级的进程
  - CFS是普通进程的调度类，系统运行的绝大多数进程都是普通进程

- 睡眠和唤醒

  - 进程把自己标记为休眠状态，从可执行红黑树中移除，放入等待队列，然后调用schedule选择和执行下一个进程
  - 进程把自己设为可执行状态，加入到可执行红黑树中
  - 等待队列
    - 等待队列是由等待某些时间发生的进程组成的简单链表
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 21-15-00.png)


  - 唤醒
    - wake_up函数会唤醒指定的等待队列上的所有进程
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-07 21-18-35.png)

### 4.6 抢占和上下文切换

- 上下文切换: 从一个可执行进程切换到另一个可执行进程

  - contex_switch()函数负责处理，schedule调用该函数
  - switch_MM()负责把虚拟内存从上一个进程映射切换到新进程
  - switch_to() 负责从上一个进程的处理器状态切换到新进程的处理器状态，包括保存、恢复栈信息和寄存器信息等
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 20-10-20.png)

  - 每个进程都包含一个need_resched标志

- 用户抢占

  - 内核无论是在中断处理程序还是在系统调用后返回，都会检查need_resched程序，如果它被设置了，那么内核会选择一个其他(更合适的)进程投入运行

- 内核抢占

  - 只要重新调度是安全的，内核就可以在任何时间抢占正在执行的任务
  - 只要没有持有锁，内核就可以进行抢占
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 20-18-07.png)

### 4.7 实时调度策略

- 实时调度策略SCHED_FIFO和SCHED_RR
- 普通的、非实时的调度策略: SCHED_NORMAL

### 4.8 与调度相关的系统调用

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 20-23-40.png)



### 第五章　系统调用

- 内核提供了用户进程与内核进行交互的一组接口

### 5.1 与内核通信

- 在Linux中，系统调用是用户空间访问内核的唯一手段，除陷入和异常外，它们是内核唯一的合法入口

### 5.2 API POSIX和C库

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 20-35-31.png)

### 5.3 系统调用

- 系统调用在出现错误的时候C库会把错误码写入errno全局变量，通过调用perror库函数，可以把该变量翻译成用户可以理解的错误字符串
- 对于普通进程来说，TGID(线程组ID)和PID相等，对于线程来说，同一线程组的所有线程其TGID都相等
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 20-44-04.png)

- 系统调用号
  - 每个系统调用被赋予一个系统调用号
  - 内核记录了系统调用表中的所有已注册过的系统调用的列表，存储在sys_call_table中
- 系统调用的性能
- 系统调用处理程序
  - 通知内核的机制是靠软中断实现的: 通过引发一个异常来促使系统切换到内核态取执行异常处理程序，此时的异常处理程序实际上就是系统调用处理程序
- 指定恰当的系统调用
  - 在x86上，系统调用号是通过eax寄存器传递给内核的
- 参数传递
  - 系统调用的参数输入，存放在寄存器中
  - 给用户空间的返回值也通过寄存器传递
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 20-54-15.png)

### 5.5 系统调用的实现

- 实现系统调用

  - 设计接口
  - 越通用越好
  - 提供机制而不是策略
  - 可移植性
  - 健壮性
  - 为将来考虑

- 参数验证

  - 参数是否合法
  - 指针是否有效
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 20-59-48.png)

  - 检查是否有合法权限，使用capable函数来检查是否有权能对指定的资源进行操作　

### 5.6 系统调用上下文

- 内核在执行系统调用的时候处于进程上下文，current指针指向当前任务，即引发系统调用的那个进程
- 在进程上下文中，内核可以休眠并且可被抢占
- 中断处理程序不能休眠
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 21-08-02.png)

- 绑定一个系统调用的最后步骤
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 21-09-28.png)

- 从用户空间访问系统调用

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 21-14-16.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 21-15-59.png)

- 为什么不通过系统调用的方式实现
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-11-12 21-19-34.png)
