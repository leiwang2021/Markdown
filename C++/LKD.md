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

### 第六章　内核数据结构

### 6.1 链表

- 单向链表和双向链表

- 环形链表，Linux内核的标准链表就是采用环形双向链表形式实现的

- 沿链表移动

- Linux内核中的实现

  - 链表数据结构，将链表结点塞入数据结构
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-02 16-13-07.png)

  

  - 链表头

- 操作链表

  - 向链表中增加一个节点　list_add  list_add_tail
  - 从链表中删除一个节点　list_del
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-02 16-23-04.png)

  - 移动和合并链表节点

- 遍历链表

### 6.2 队列

- Linux内核通用队列实现称为kfifo
- kfifo
- 创建队列
- 推入队列数据
- 摘取队列数据
- 获取队列长度
- 重置和撤销队列

### 6.3 映射

- 关联数组
- Linux内核映射数据结构的目的是: 映射一个唯一的标识数(UID)到一个指针
- idr数据结构用于映射用户空间的UID
- 初始化一个idr
- 分配一个新的UID
  - idr_pre_get调整后备树的大小
  - idr_get_new 实际执行获取新的UID, 并且将其加到idr
- 查找UID
- 删除UID
- 撤销idr

### 6.4 二叉树

- 二叉搜索树
- 自平衡二叉搜索树
  - 一个自平衡二叉搜索树是指其操作都试图维持平衡的二叉搜索树
  - 红黑树，Linux主要的平衡二叉搜索树数据结构就是红黑树
  - rbtree,Linux实现的红黑树称为rbtree

### 6.5 数据结构以及选择

### 6.6 算法复杂度

- 渐近行为是指当算法的输入变得非常大或接近于无限大时算法的行为

## 第七章　中断和中断处理

- 中断机制: 让硬件在需要的时候再向内核发送信号

### 7.1 中断

- 当接收到一个中断后，中断控制器会给处理器发送一个电信号，处理器一经检测到此信号，便中断自己的当前工作转而处理中断
- 每个中断都通过一个唯一的数字标志
- 异常被称为同步中断，由处理器产生，如系统调用。

### 7.2 中断处理程序

- 产生中断的每个设备都有一个相应的中断处理程序，一个设备的中断处理程序是它设备驱动程序的一部分，设备驱动程序是用于对设备进行管理的内核代码
- 中断处理程序运行在中断上下文中，也称作原子上下文，该上下文中的执行代码不可阻塞

### 7.3 上半部与下半部的对比

- 一般把中断处理程序切分为两半，上半部接收到一个中断就立即开始执行，但只做有严格时限的工作。能够被允许稍后完成的工作会推迟到下半部

### 7.4 注册中断处理程序

- 驱动程序可以通过request_irq()函数注册一个中断处理程序，并且激活给定的中断线，以处理中断
- 中断处理程序标志
- 释放中断处理程序
  - free_irq 卸载驱动程序时，需要注销相应的中断处理程序

### 7.5 编写中断处理程序

- 重入和中断处理程序
  - Linux的中断处理程序是无须重入的，当一个给定的中断处理程序正在执行时，相应的中断线在所有处理器上都会被屏蔽掉，其他的中断都是打开的。
- 共享的中断处理程序
  - 自旋锁
  - 何谓**自旋锁**？它是为实现保护[共享资源](https://baike.baidu.com/item/%E5%85%B1%E4%BA%AB%E8%B5%84%E6%BA%90)而提出一种锁机制。其实，自旋锁与[互斥锁](https://baike.baidu.com/item/%E4%BA%92%E6%96%A5%E9%94%81)比较类似，它们都是为了解决对某项资源的互斥使用。无论是[**互斥锁**](https://baike.baidu.com/item/%E4%BA%92%E6%96%A5%E9%94%81)，还是**自旋锁**，在任何时刻，最多只能有一个保持者，也就说，在任何时刻最多只能有一个执行单元获得锁。但是两者在调度机制上略有不同。对于互斥锁，如果资源已经被占用，资源申请者只能进入睡眠状态。但是自旋锁不会引起调用者睡眠，如果自旋锁已经被别的执行单元保持，调用者就一直循环在那里看是否该自旋锁的保持者已经释放了锁，"自旋"一词就是因此而得名。

### 7.6 中断上下文

- **中断上下文不可以睡眠，中断处理程序打断了其他的代码，应该尽可能迅速执行**
- 内核栈
- 中断处理程序栈

### 7.7 中断处理机制的实现

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-03 16-31-54.png)

### 7.8 /proc/interrupts

- procfs是一个虚拟文件系统，它只存在于内核内存，一般安装于/proc目录

### 7.9 中断控制

- 锁提供保护机制，防止来自其他处理器的并发访问，而禁止中断提供保护机制，则是防止来自其他中断处理程序的并发访问
- 禁止和激活中断
  - 在禁止中断之前保存中断系统的状态会更加安全，在准备激活中断时，只需要把中断恢复到它们原来的状态
- 禁止指定中断线
- 中断系统的状态
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-03 17-01-47.png)

## 第八章　下半部和推后执行的工作

### 8.1 下半部

- 如何决定完全取决于驱动程序开发者自己的判断
- 上半部简单快速，执行的时候禁止一些或者全部中断，下半部分稍后执行，而且执行期间可以响应所有中断
- BH
- 任务队列
- 软中断和tasklet
- 2.6版本内核提供了三种下半部实现机制: 软中断、tasklet 和工作队列

### 8.2 软中断

- 软中断的实现
  - 软中断是在编译期间静态分配的，由softirq_action结构表示
  - 32个软中断
  - 唯一可以抢占软中断的是中断处理程序，其他的软中断可以在其他处理器上同时执行
  - 触发软中断: 中断处理程序在返回前标记它的软中断，使其在稍后执行
- 使用软中断
  - 只有两个子系统(网络和SCSI)直接使用软中断
  - 内核定时器和tasklet都是建立在软中断上的
  - 分配索引
  - 注册处理程序　
  - 引入软中断的主要原因是其可扩展性

### 8.3 tasklet

- tasklet的实现
  - 通过软中断实现
  - tasklet结构体，tasklet_struct
  - 调度tasklet
  - 使用tasklet
    - 静态创建
    - 动态创建
  - ksoftirqd 当大量软中断出现的时候，内核会唤醒一组内核线程来处理这些负载，这些线程在最低的优先级上运行

### 8.4 工作队列

- 工作队列可以把工作推后，交由一个内核线程去执行，这个下半部分总是会在进程上下文中执行，工作队列允许重新调度甚至睡眠
- 工作队列的实现
  - 工作者线程，用workqueue_struct结构表示
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-10 16-51-54.png)

- 使用工作队列

### 8.5下半部机制的选择

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-10 16-58-54.png)

### 8.6在下半部之间加锁

### 8.7 禁止下半部

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-10 17-05-59.png)

## 第9章　内核同步介绍

### 9.1 临界区和竞争条件

- 临界区就是访问和操作共享数据的代码段
- 竞争条件: 两个执行线程有可能处于同一个临界区中同时执行
- 同步: 避免并发和防止竞争条件

### 9.2 加锁

- 各种锁机制之间的区别主要在于: 当锁已经被其他线程持有，因而不可用时的行为表现

- 造成并发执行的原因

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-10 17-24-43.png)

  

- 辨认出真正需要共享的数据和相应的临界区才是最困难的地方

### 9.3 死锁

- 每个线程都在等待其他线程持有的锁，但是绝没有一个线程会释放它们一开始就持有的锁，所以没有任何锁会在释放后被其他线程使用
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-10 17-31-46.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-10 17-32-44.png)

### 9.4 争用和扩展性

- 争用的锁会成为系统的瓶颈
- 加锁粒度用来描述加锁保护的数据规模

## 第10章　内核同步方法

### 10.1 原子操作

- 原子操作就是不能被分割的指令

- 内核提供了两组原子操作接口: 一组针对整数进行操作，另一组针对单独的位进行操作

- 原子整数操作

  - 针对整数的原子操作只能对atomic_t类型的数据进行处理

  - ```c++
    typedef struct{
        volatile int counter;
    } atomic_t;
    ```

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-11 17-14-09.png)

  - 原子操作通常是内联函数，往往通过内嵌汇编指令来实现，如果某个函数本身就是原子的，那么它往往会被定义成一个宏
  - 原子操作只保证原子性，顺序性通过屏障指令来实施
  - 能使用原子操作时，就尽量不要使用复杂的加锁机制

- 64位原子操作

  - ```c++
    typedef struct{
        volatile long counter;
    }atomic64_t;
    ```

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-11 17-20-28.png)

- 原子位操作

  - 位操作函数是对普通的内存地址进行操作的，它的参数是一个指针和一个位号
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-11 17-23-32.png)

  - 非原子位操作

### 10.2 自旋锁

- 自旋锁(spin lock),最多只能被一个可执行线程持有，如果一个执行线程试图获得一个被已经持有的自旋锁，那么该线程就会一直进行忙循环-旋转-等待锁重新可用，特别浪费处理器时间

- 让请求线程睡眠，直到锁可用时再唤醒它，这样处理器不必循环等待，但是有两次明显的上下文切换，信号量提供了这种机制

- 自旋锁方法

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-11 18-42-48.png)

  - Linux内核实现的自旋锁是不可递归的
  - 自旋锁可用使用在中断处理程序中，一定要在获取锁之前，首先禁止本地中断

- 其他针对自旋锁的操作

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-11 18-53-06.png)

- 自旋锁和下半部
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-11 18-57-19.png)

### 10.3 读-写自旋锁

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-11 18-59-12.png)
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-11 19-00-49.png)
- 如果加锁时间不长并且代码不会睡眠，利用自旋锁是最佳选择。如果加锁时间可能很长或者代码在持有锁时有可能睡眠，最好使用信号量来完成加锁功能

### 10.4 信号量

- Linux中的信号量是一种睡眠锁，如果一个任务试图获得一个不可用的信号量时，信号量会将其推进一个等待队列，然后让其睡眠，当持有的信号量可用后，处于等待队列中的那个任务将被唤醒
- 信号量和自旋锁的差异
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 14-56-26.png)

- 不会禁止内核抢占，持有信号量的代码可以被抢占
- 计数信号量和二值信号量
  - 二值信号量，互斥信号量，一个时刻仅允许一个锁持有者
  - 计数信号量，一个时刻至多有count个锁持有者
- 创建和初始化信号量
  - struct semaphore类型用来表示信号量
- 使用信号量
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 15-05-02.png)

### 10.5 读-写信号量

- 读写信号量在内核中是由rw_semaphore结构表示的
- 所有读-写锁的睡眠都不会被信号打断
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 15-07-48.png)

### 10.6 互斥体

- 互斥体指的是任何可以睡眠的强制互斥锁
- mutex在内核中对应数据结构mutex,其行为和使用计数为1的信号量类似，但是操作接口更简单，实现更高效，使用限制更强
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 15-12-32.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 15-15-01.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 15-17-54.png)

### 10.7 完成变量

- 完成变量由completion表示，如果一个任务要执行一些工作时，另一个任务就会在完成变量上等待，当这个任务完成工作后，会使用完成变量去唤醒在等待的任务
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 15-22-49.png)

### 10.8 BLK:大内核锁

### 10.9 顺序锁

- seq锁，实现这种锁主要依靠一个序列计数器，当有疑义的数据被写入时，会得到一个锁，并且序列值会增加
- jiffies,该变量存储了Linux机器启动到当前的时间

### 10.10 禁止抢占

- 如果一个自旋锁被持有，内核便不能进行抢占
- 可以通过preempt_disabkl禁止内核抢占，每次调用都必须有一个相应的preempt_enbale调用
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 15-52-40.png)

### 10.11　顺序和屏障

- 编译器和处理器为了提高效率，可能对读和写重新排序
- 屏障: 可以指示编译器不要给定点周围的指令序列进行重新排序，确保顺序
- rmb提高了一个读内存屏障，在rmb之前的载入操作不会被重新排列在该调用之后，在rmb之后的载入操作不会被重新排列在该调用之前
- wmb提高了一个写内存屏障
- mb既提高了读屏障也提供了写屏障
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 16-01-20.png)

## 第11章　定时器和时间管理

- 系统定时器是一种可编程芯片，它能以固定频率产生中断，该中断就是定时器中断，它所对应的中断处理程序负责更新系统时间，也负责执行需要周期性运行的任务。系统定时器和时钟中断处理程序是Linux系统内核管理机制中的中枢

### 11.1 内核中的时间概念

- 内核靠已知的时钟中断间隔来计算墙上时间和系统运行时间

### 11.2 节拍率: HZ

- 节拍率有一个HZ频率，一个周期为1/HZ秒，x86上时钟中断的频率为100HZ
- 理想的HZ值
  - 更高的时钟中断解析度可提高时间驱动时间的解析度
- 高HZ的优势
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 16-29-11.png)

- 高HZ的劣势
  - 节拍率越高，时钟中断频率越高，系统负担也越重，处理器必须花时间来执行时钟中断处理程序
- Linux内核支持"无节拍操作"选项，当编译内核时设置了CONFIG_HZ配置选项，系统就根据这个选项动态调度时钟中断

### 11.3 jiffies

- 全局变量jiffies用来记录自系统启动以来产生的节拍的总数，无符号长整型

- jiffies的内部表示

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 16-38-39.png)

- jiffies的回绕
  - 如果节拍数达到了最大值后还要继续增加的话，它的值会回绕到0
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-13 16-42-03.png)

- 用户空间和HZ

  - 内核定义了USER_HZ来代表用户空间看到的HZ值，为100,可以使用jiffies_to_clock_t()将一个由HZ表示的节拍计数器转换成一个由USER_HZ表示的节拍计数

### 11.4 硬时钟和定时器

- 实时时钟
  - 实时时钟(RTC）是用来持久存放系统时间的设备，RTC和CMOS继承在一起，通过同一个电池供电
  - 内核通过读取RTC来初始化墙上时间，该变量存放在xtime变量中
- 系统定时器
  - 提供一种周期性触发中断机制
  - 主要采用可编程中断时钟(PIT)

### 11.5 时钟中断处理程序

- 分为体系结构相关部分和体系结构无关部分
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-16 16-28-45.png)

- tick_periodic执行下面的工作
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-16 16-29-08.png)

- 内核对进程进行时间计数时，是根据中断发生时处理器所处的模式进行分类统计的

### 11.6 实际时间

- 当前实际时间(墙上时间)　xtime
- 读写xtime变量需要使用xtime_lock锁，该锁是seqlock锁

### 11.7 定时器

- 动态定时器不断地创建和撤销，而且它的运行次数也不受限制
- 指定的函数将在定时器到期时自动执行
- 使用定时器
  - 定时器由结构timer_list表示
- 定时器竞争条件
  - 因为定时器与当前执行代码是异步的，就有可能存在潜在的竞争条件
- 实现定时器
  - 定时器作为软中断在下半部上下文中执行

### 11.8 延迟执行

- 忙等待

  - 在循环中不断旋转直到希望的时钟节拍数耗尽
  - 关键字volatile指示编译器在每次访问变量时都重新从主内存中获得，而不是通过寄存器中的变量别名来访问
- 短延迟
- schedule_timeout

## 第12章　内存管理

### 12.1 页

- 内存管理单元MMU通常以页为单位管理系统中的页表
- 内存用struct page结构表示系统中的每个物理页
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-16 17-22-40.png)
  - flag域用来存放页的状态
  - _count域存放页的引用计数
  - virtual域是页的虚拟地址
  - page结构与物理页相关，而并非与虚拟页相关
  - 系统中的每个物理页都要分配一个这样的结构体

### 12.2 区

- 内核使用区对具有相似特性的页进行分组
- Linux主要使用了四种区
  - ZONE_DMA
  - ZONE_DMA32
  - ZONE_NORMAL
  - ZONE_HIGHEM

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-16 17-32-46.png)

- x86-64没有ZONE_HIGHMEM区，所有的物理内存都位于ZONE_DMA和ZONE_NORMAL
- 每个区都用struct zone表示
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-16 17-35-18.png)

### 12.3 获得页

- alloc_pages 分配2^order个连续的物理页
- page_address 指向给定物理页当前所在的逻辑地址
- 获得填充为0的页
  - get_zerod_page
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-18 15-42-30.png)

- 释放页
  - __free_pages
  - free_pages
  - free_page
  - 只能释放自己的页

### 12.4 kmalloc

- 可以获得以字节为单位的一块内核内存
- 所分配的内存区在物理上是连续的

- gfp_mask标志

  - 分配器标志，行为修饰符表示内核应当如何分配所需的内存，区修饰符表示从哪儿分配内存，类型标志组合了行为修饰符和区修饰符
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-18 15-51-53.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-18 15-58-21.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-18 16-00-10.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-18 16-08-20.png)

- kfree
  - kfree释放由kmalloc分配出来的内存块

### 12.5 vmalloc

- vmalloc分配的内存虚拟地址是连续的，而物理地址则无需连续
- 硬件设备用到的任何内存区都必须是物理上连续的块，而供软件使用的内存块可以使用只有虚拟地址连续的内存块
- 函数可以睡眠
- vfree释放

### 12.6 slab层

- slab分配器
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-18 16-20-06.png)

- slab层的设计

  - slab由一个或多个物理上连续的页组成，每个高速缓存可以由多个slab组成，每个slab都包含一些对象成员，指的是被缓存的数据结构
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-18 16-24-06.png)

  - 每个高速缓存都使用kmeme_cache结构来表示，包含三个链表: slabs_full  slabs_partial  slabs_empty,这些链表包含高速缓存中的所有slab

- slab分配器的接口

  - kmeme_cache_create 创建一个新的高速缓存
  - kmem_cache_destroy　撤销一个高速缓存
  - 从缓存中分配
    - kmeme_cache_alloc 从给定的高速缓存cachep中返回一个指向对象的指针
    - kemem_cache_free 释放一个对象，返回给原先的slab
  - slab分配器的使用实例
    - 创建一个名为task_struct的高速缓存，存放的struct task__struct的对象
  - 如果需要创建很多相同类型的对象，那么就应该考虑使用slab高速缓存。不要自己实现空闲链表



### 12.7 在栈上的静态分配

- 每个进程的内核栈大小既依赖于体系结构，也与编译时的选项有关
- 单页内核栈
- 在栈上光明正大地工作
  - 当栈溢出时，多出的数据就会直接溢出来，覆盖掉紧邻堆栈末端的东西

### 12.8 高端内存的映射

### 12.9 每个CPU的分配

### 12.10 新的每个CPU接口

## 第13章　虚拟文件系统

- 通过虚拟文件系统，程序可以利用标准的Unix系统调用对不同的文件系统，甚至不同介质的文件系统进行读写操作

### 13.1 通用文件系统接口

- VFS把各种不同的文件系统抽象后采用统一的方式进行操作
- 块I/O层，支持各种各样的存储设备

### 13.2 文件系统抽象层

- 内核在它的底层文件系统接口上建立了一个抽象层
- VFS抽象层之所以能衔接各种各样的文件系统，是因为它定义了所有文件系统都支持的、基本的、概念上的接口和数据结构
- 实际文件系统通过编程提供VFS所期望的抽象接口和数据结构
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 10-30-26.png)

### 13.3 Unix文件系统

- Unix使用了四种抽象概念: 文件、目录项、索引节点和安装点(mount point)
- 本质上文件系统是特殊的数据分层存储结构，包含文件、目录和相关的控制信息
- Linux每个进程都指定一个唯一的命名空间，所有进程往往都只有一个全局命名空间
- 在Unix中，文件系统被安装在一个特定的安装点上，即命名空间，所有已安装文件系统都作为根文件系统树的枝叶出现在系统中
- 在Unix中，目录属于普通文件。Unix系统将文件的相关信息和文件本身这两个概念加以区分，文件相关信息，被存储在一个单独的数据结构中，称为索引节点
- 文件系统的控制信息存储在超级块中，超级块是一种包含文件系统信息的数据结构

### 13.4 VFS对象及其数据结构

- VFS其实采用的是面向对象的设计思路，使用一组数据结构来代表通用文件对象
- VFS中有四个主要的对象类型
  - 超级块对象，代表一个具体的已安装文件系统
  - 索引节点对象，代表一个具体文件
  - 目录项对象，代表一个目录项(目录项代表的是路径中的一个组成部分，它可能包含一个普通文件)
  - 文件对象，代表由进程打开的文件
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 10-49-54.png)

### 13.5 超级块对象

- 该对象用于存储特定文件系统的信息，通常对应于存放在磁盘特定扇区中的文件系统超级块或文件系统控制块
- 由super_block结构体表示
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 10-55-13.png)

### 13.6 超级块操作

- s_op域，指向超级块的操作函数表，由super_operations结构体表示，该结构体中的每一项都是一个指向超级块操作函数的指针
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 11-00-38.png)

### 13.7 索引节点对象

- 索引节点对象包含了内核在操作文件或目录时需要的全部信息
- 索引节点对象由inode结构体表示
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 11-07-06.png)

- 一个索引节点代表文件系统中的一个文件，它也可以是设备或管道这样的特殊文件

### 13.8 索引节点操作

- i_op　索引节点操作表，inode_operations结构体
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 11-12-53.png)

### 13.9 目录项对象

- /bin/vi     / 、bin、vi都是目录项对象，前两个是目录，最后一个是普通文件。
- 目录项对象由dentry结构体表示
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 11-18-13.png)

- 目录项对象没有对应的磁盘数据结构，VFS根据字符串形式的路径名现场创建它
- 目录项状态
  - 被使用，对应一个有效的索引节点
  - 未被使用，对应一个有效的索引节点
  - 负状态，没有对应的索引节点
- 目录项缓存
  - 内核将目录项对象缓存在目录项缓存中
  - 只有目录项被缓存，其相应的索引节点也就被缓存了

### 13.10 目录项操作

- dentry_operation结构体指明了VFS操作目录项的所有方法
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 13-10-15.png)

### 13.11 文件对象

- 文件对象表示进程已打开的文件在内存中的表示
- 只有目录项对象才表示已打开的实际文件，一个文件对应的文件对象不是唯一的，但对应的索引节点和目录项对象是唯一的
- 文件对象由file结构体表示
- 文件对象通过f_dentry指针指向相关的目录项对象，目录项会指向相关的索引节点，索引节点会记录文件是否是脏的
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 13-43-19.png)

### 13.12 文件操作

- 文件对象的操作由file_operations结构体表示
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 13-44-42.png)

### 13.13 和文件系统相关的数据结构

- file_system_type 用来描述各种特定文件系统类型，比如ext3 ext4
- vfsmount 用来描述一个安装文件系统的实例
- 每种文件系统，不管有多少个实例安装到系统中，还是根本没有安装到系统中，都只有一个file_system_type 结构
- 当文件系统被实际安装时，将有一个vfsmount结构体在安装点被创建，该结构体用来代表文件系统的实例，即代表一个安装点
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-06-34.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-06-57.png)

### 13.14 和进程相关的数据结构

- 系统中的每一个进程都有自己的一组打开的文件，像根文件系统、当前工作目录、安装点等
- files_struct结构体，由进程描述符的files目录项指向
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-12-00.png)

- fs_struct结构体，由进程描述符的fs域指向
- namespace结构体，由进程描述符的mmt_namespace域指向
- 单进程命名空间，使得每一个进程在系统中都看到唯一的安装文件系统，不仅是唯一的根目录，而且是唯一的文件系统层次结构
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-16-36.png)

## 第14章　块I/O层

- 系统中能够随机访问固定大小数据片的硬件设备称为块设备，如硬盘，闪存，它们都是以安装文件系统的方式使用的
- 字符设备，按照字符流的方式被有序访问，像串口和键盘

### 14.1 剖析一个块设备

- 块设备的最小可寻址单元是扇区，扇区是所有块设备的基本单元，常见的是512字节大小
- 最小逻辑可寻址单元-块，只能基于块来访问文件系统，必须是扇区大小的2的整数倍，并且小于页面大小
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-29-58.png)

### 14.2 缓冲区和缓冲区头

- 当一个块被调入内存时，它要存储在一个缓冲区中，每个缓冲区都有一个对应的描述符，用buffer_head结构体表示，称作缓冲区头
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-47-43.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-49-10.png)

### 14.3 bio结构体

- 目前内核中块I/O操作的基本容器由bio结构体表示
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-55-36.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-57-01.png)

- I/O向量

  - 整个bio_io_vec结构体数组表示了一个完整的缓冲区
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 14-59-43.png)

  - 每一个块I/O请求都通过一个bio结构体表示，每个请求包含一个或多个块，这些块存储在bio_vec结构体数组中，这些结构体描述了每个片段在物理页中的实际位置

- 对比

  - bio结构体代表的是I/O操作，可以包括内存中的一个或多个页，buffer_head结构体代表的是一个缓冲区，描述的仅仅是磁盘中的一个块

### 14.4 请求队列

- 块设备将它们挂起的块I/O请求保存在请求队列中，该队列由reques_queue结构体表示

### 14.5 I/O调度程序

- I/O调度程序的工作
  - 管理块设备的请求队列
  - I/O调度程序通过两种方法减少磁盘寻址时间: 合并与排序
- Linus电梯
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 15-19-24.png)

- 最终期限I/O调度程序
  - 读操作具有同步性，并且彼此之间相互依靠，所以读请求响应时间直接影响系统性能，最终期限I/O调度程序可以减少请求饥饿现象
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 15-24-19.png)

- 预测I/O调度程序
  - 预测I/O调度程序在最终期限I/O调度程序的基础上增加了预测启发能力
- 完全公正的排队I/O调度程序
  - CFQ I/O调度程序的差异在于每一个提交I/O的进程都有自己的队列
  - CFQ I/O调度程序以时间片轮转调度队列，从每个队列中选取请求数，然后进行下一轮调度
- 空操作的I/O调度程序
  - 当一个新请求提交到队列时，就把它与任一相邻的请求合并
  - 专为随机访问设备而设计的
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 15-34-28.png)

## 第15章　进程地址空间

### 15.1 地址空间

- 进程地址空间由进程可寻址的虚拟内存组成
- 可被访问的合法地址空间称为内存区域，通过内核，进程可以给自己的地址空间动态地添加或减少内存区域
- 进程只能访问有效内存区域内的内存地址，如果访问了不合法的内存区域，将返回“段错误”信息
- 内存区域可以包含各种内存对象
  - 代码段
  - 数据段
  - bss段的零页
  - 用于进程用户空间栈的零页的内存映射
  - 每一个诸如C库或动态连接程序等共享库的代码段、数据段和bss
  - 任何内存映射文件
  - 任何共享内存段
  - 任何匿名的内存映射

### 15.2 内存描述符

- 内核使用内存描述符结构体mm_struct表示进程的地址空间
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 16-04-49.png)

- 分配内存描述符
  - 进程的进程描述符中mm域存放着该进程使用的内存描述符
  - 每个进程都有唯一的mm_struct结构体，即唯一的进程地址空间
  - 是否共享地址空间几乎是进程和Linux中所谓的线程间本质上的唯一区别
- 撤销内存描述符
- mm_struct与内核线程
  - 内核线程没有进程地址空间，也没有相关的内存描述符，即没有用户上下文
  - 当一个内核线程被调度时，内核发现它的mm域为NULL,就会保留前一个进程的地址空间，随后内核更新内核线程对应的进程描述符中的active_mm域，使其指向前一个进程的内存描述符。内核线程不访问用户空间的内存，所以它们仅仅使用地址空间中和内核内存相关的信息

### 15.3 虚拟内存区域

- 内存区域由vm_area_struct结构体描述，常称作虚拟内存区域VMAs
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 16-29-20.png)

- vm_area_struct结构体描述了指定地址空间内连续区间上的一个独立内存范围，内核将每个内存区域作为一个单独的内存对象管理
- VMA标志
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 16-38-18.png)

- VMA操作
  - vm_ops域指向与指定内存区域相关的操作函数表，内核使用表中的方法操作VMA
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 16-43-41.png)

- 内存区域的树型结构和内存区域的链表结构
  - mmap域使用单独链表连接所有的内存区域对象
  - mm_rb域使用红－黑树连接所有的内存区域对象
- 实际使用中的内存区域
  - 可以使用/proc文件系统和pmap工具查看给定进程的内存空间和其中所含的内存区域
  - /proc/pid/maps显示了该进程地址空间中的全部内存区域　cat /proc/1425/maps
  - pmap工具将上述信息以更方便的形式输出:   pmap  1425

### 15.4 操作内存区域

- find_vma()
  - 为了找到一个给定的内存地址属于哪一个内存区域
  - 搜索通过红黑树进行
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 17-00-53.png)

- find_vma_prev
- find_vma_intersection

### 15.5 mmap和do_mmap:创建地址区间

- do_mmap函数将一个地址区间加入到进程的地址空间中－无论是扩展已存在的内存区域还是创建一个新的区域

### 15.6 munmap和do_munmap: 删除地址区间

- do_munmap从特定的进程地址空间中删除指定地址区间

### 15.7 页表

- 虚拟地址转换成物理地址
- Linux中使用三级页表完成地址转换
- 顶级页表是页全局目录PGD, 二级页表是中间页目录PMD, 最后一级的页表简称页表
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-23 17-15-13.png)
- 每个进程都有自己的页表，线程会共享页表
- 为了加快搜索，多数体系结构都实现了一个翻译后缓冲器TLB, TLB作为一个将虚拟地址映射到物理地址的硬件缓存



## 第16章　页高速缓存和页回写

- 页高速缓存(cache)是Linux内核实现磁盘缓存，主要用来减少对磁盘的I/O操作

### 16.1 缓存手段

- 页高速缓存是由内存中的物理页面组成的，其内容对应磁盘上的物理块，页高速缓存大小能动态调整
- 写缓存
  - 回写，程序执行写操作直接写到缓存中，后端存储不会立刻直接更新，而是将页高速缓存中被写入的页面标记成脏，且加入到脏页链表中，然后由一个进程周期性地将脏页链表中的页写回到磁盘，从而让磁盘上的数据和内存中一致
- 缓存回收
  - Linux的缓存回收是通过选择干净页进行简单替换
    - LRU回收
    - 双链策略，活跃链表和非活跃链表

### 16.2 Linux页高速缓存

- address_space对象　

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-24 13-15-05.png)

  - 一个被缓存的文件只和一个address_space结构体相关联，但它可以有多个vm_area_struct结构体

- address_space操作

  - a_ops域指向地址空间对象中的操作函数表
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-24 13-19-56.png)



### 16.3 缓冲区高速缓存

### 16.4 flusher线程

- 脏页被写回磁盘
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-24 13-24-30.png)

- flusher线程在系统中的空闲内存低于一个特定的阈值时，将脏页刷新写回磁盘



## 第17章　设备与模块

### 17.1 设备类型

- 块设备
  - 通过块设备节点的特殊文件来访问，通常挂载为文件系统
- 字符设备
  - 是不可寻址的，仅提供数据的流式访问，通过字符设备节点的特殊文件来访问，应用程序通过直接访问设备节点与字符设备交互
- 网络设备
  - 以太网设备，打破了Unix的所有东西都是文件的设计原则，不是通过设备节点来访问，而是通过套接字API的特殊接口访问
- 伪设备
  - 设备驱动是虚拟的，仅提供访问内核功能而已，如/dev/null, 不表示物理设备

### 17.2 模块

- Linux内核是模块化组成的，允许内核在运行时动态地向其中插入或从中删除代码
- Hello World
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-12-24 14-06-34.png)

- 构建模块
  - 放在内核源代码树中
    - obj-$(CONFIG_FISHING_POLE)+=fishing/   添加到Makefile文件中
    - obj-m+=fishing.o 添加到Makefile文件中
  - 放在内核代码外
    - 加入Makefile文件
    - 必须告诉make如何找到内核源代码文件和基础Makefile文件
- 安装模块
  - 编译后的模块被装入到目录/lib/modules/version/kernel/
  - make modules_install 
- 产生模块依赖性
- 载入模块
  - insmod module.ko
  - rmmod fishing.ko 卸载模块
  - modprobe自动安装卸载有关的依赖模块
- 管理配置选项
  - kconfig文件
- 模块参数

### 17.3 设备模型

### 17.4 sysfs

## 第18章　调试

