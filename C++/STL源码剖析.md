# STL源码剖析

## 第一章　STL概论

### 1.1 STL概论

- STL所实现的是依据泛型思维架设起来的一个概念结构
- STL历史
- STL与标准程序库

### 1.2 STL六大组件　

- 容器
- 算法
- 迭代器：　泛型指针
- 仿函数：一种重载了operator()的class或class template,一般函数指针可视为狭义的仿函数
- 配接器(adapters)
- 配置器

### 1.3 GNU

### 1.4 HP实现版本

### 1.5 P.J.Plauger实现版本

### 1.6 Rouge Wave 实现版本

### 1.7 STLport实现版本

### 1.8 SGI STL实现版本

- /usr/include/ C标准头文件，/usr/include/c++　　C++标准头文件

- GNU C++ headers文件分布

  - C++标准规范下的C头文件，无扩展名

  - C++标准程序库中不属于STL的

  - STL标准头文件，如vector

  - C++ Standard定案前，HP所规范的STL头文件，如vector.h

  - SGI STL内部文件(STL真正实现于此)，如stl_vector.h

- SGI STL的编译器组态设置

  - 环境组态文件　<stl_config.h>,标示某些组态成立与否，所有STL头文件都会直接或间接包含这个组态文件,不同的编译器对C++语言的支持程度不尽相同


### 1.9 

- 组态常量，用来区分编译器对C++ standard的支持程度

- stl_config.h中的各种组态
  - 组态3: __STL_STATIC_TEMPLATE_MEMBER_BUG
  - 组态5: __STL_CLASS_PARTIAL_SPECIALIZATION
  - 组态6: __STL_FUNTION_TMPL_PARTIAL_ORDER
  - 组态7: __STL_EXPLICIT_FUNTION_TMPL_ARGS
  - 组态8: __STL_MEMBER_TEMPLATES
  - 组态10: __STL_LIMITED_DEFAULT_TEMPLATES
  - 组态11: __STLNON_TYPE_TMPL_PARAM_BUG
  - 组态:  __STL_NULL_TMPL_ARGS
  - 组态: __STL_TEMPLATE_NULL

- 临时对象的产生与运用

  - 任何pass by value操作都会引发copy操作，于是形成一个临时对象，造成效率上的负担
  - 刻意制造临时对象的方法:  Shape(3) 在型别名称之后加一对小括号，并指定初值，STL常将此技巧用于仿函数与算法的搭配上

- 静态常量整数成员在class内部直接初始化

- increment/decrement/dereference操作符

  - 迭代器的功能实现

  - increment和decrement分为前置式和后置式两种　

  - C++规定后缀形式有一个int类型参数，当函数被调用时，编译器传递一个0做为int参数的值给该函数　

    ```c++
    class UPInt { // "unlimited precision int"
    public:
    　UPInt& operator++(); // ++ 前缀
    　const UPInt operator++(int); // ++ 后缀
    　UPInt& operator--(); // -- 前缀
    　const UPInt operator--(int); // -- 后缀
    　UPInt& operator+=(int); // += 操作符，UPInts
    　// 与ints 相运算
    　...
    };
    
    UPInt i;
    
    ++i; // 调用 i.operator++();
    i++; // 调用 i.operator++(0);
    --i; // 调用 i.operator--();
    i--; // 调用 i.operator--(0);
    ```

    　

  - dereference取值

- 前闭后开区间表示法

  - [first last)  实际范围从first开始　直到last-1

- function call操作符

  - 函数指针存在缺陷: 无法持有自己的状态，无法达到组件技术中的可适配性
  - 仿函数：使用起来像函数一样的东西，对某个类class进行operator()重载



## 第二章　空间配置器allocator

### 2.1 空间配置器的标准接口

- 设计一个简单的空间配置器

  - size_t是一个unsigned类型的数值类型
  - ptrdiff_t通常用来保存两个指针减法操作的结果　　通常为long int 类型

### 2.2 具备次配置力的SGI空间配置器

- SGI STL的配置器名称是alloc

  ```c++
  vector<int, std::allooc> iv;
  //SGI STL的每一个容器都已经指定缺省的空间配置器为alloc
  ```

- SGI标准的空间配置器　std::allocator  效率不佳，SGI未使用

- SGI特殊的空间配置器　std::alloc

  - C++内存配置和释放操作

    ```
    class Foo{....};
    Foo* pf=new Foo;   //调用operator new 配置内存，调用Foo::Foo()构造对象内容
    delete pf;　　　//调用Foo::~Foo()将对象析构，　调用operator delete释放内存
    ```

  - 内存配置操作：　alloc::alocate()

  - 内存释放操作:    alloc::deallocate()

  - 对象构造操作:    ::construct()

  - 对象析构操作:    ::destroy()

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-06 11-20-29.png)

  

- 构造和析构基本工具: construct和destroy

  - new、operator new、placement new

    - new和delete操作符我们应该都用过，它们是对堆中的内存进行申请和释放，而这两个都是不能被重载的。要实现不同的内存分配行为，需要重载operator new，而不是new和delete。

    - operator new就像operator+一样，是可以重载的，但是不能在全局对原型为void operator new(size_t size)这个原型进行重载，一般只能在类中进行重载。如果类中没有重载operator new，那么调用的就是全局的::operator new来完成堆的分配。同理，operator new[]、operator delete、operator delete[]也是可以重载的，一般你重载了其中一个，那么最好把其余三个都重载一遍。

    - placement new是operator new的一个重载版本，只是我们很少用到它。如果你想在已经分配的内存中创建一个对象，使用new是不行的。也就是说placement new允许你在一个已经分配好的内存中（栈或堆中）构造一个新的对象。原型中void*p实际上就是指向一个已经分配好的内存缓冲区的的首地址。

    - 我们知道使用new操作符分配内存需要在堆中查找足够大的剩余空间，这个操作速度是很慢的，而且有可能出现无法分配内存的异常（空间不够）。placement new就可以解决这个问题。我们构造对象都是在一个预先准备好了的内存缓冲区中进行，不需要查找内存，内存分配的时间是常数；而且不会出现在程序运行中途出现内存不足的异常。所以，placement new非常适合那些对时间要求比较高，长时间运行不希望被打断的应用程序。

      ```c++
      class MyClass {…}; 
      char *buf=new char[N*sizeof(MyClass)+ sizeof(int) ] ; 
      //或者char buf[N*sizeof(MyClass)+ sizeof(int) ];
      //缓冲区提前分配可以使用堆的空间，也可以使用栈的空间
      MyClass * pClass=new(buf) MyClass;
      //对象的构造
      pClass->~MyClass();
      //对象的销毁
      //如果缓冲区在堆中，那么调用delete[] buf;进行内存的释放；如果在栈中，那么在其作用域内有效，跳出作用域，内存自动释放。
      ```

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-06 12-21-46.png)

  -  首先利用value_type()获得迭代器所指对象的型别，再利用__type__traits<T>判断该型别的析构函数是否trivial

- 空间的配置与释放  std::aloc

  - 双层配置器设置

    - 当配置区块超过128bytes时，视为足够大，采用第一级配置器，否则，采用复杂的memory pool整理方式

    - 第一级配置器直接使用malloc()和free()
    - 第二级配置器则视情况采用不同的策略
    - 无论alloc被定义为第一级或第二级配置器，SGI还为它再包装一个接口
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-06 13-57-16.png)



​				  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-06 14-02-29.png)



- 第一级配置器__malloc_alloc_template剖析

  - new handler机制，就是可以要求系统在内存配置需求无法被满足时，调用一个由用户指定的函数。具体说来，一旦::operator new 无法完成任务，在抛出std::bad_alloc异常状态之前，会先调用由用户指定的处理程序，该处理程序就是 new-handler
  - SGI以malloc而非::operator new来配置内存，SGI不能直接使用C++的set_new_handler(),必须仿真一个类似的set_malloc_handler()
  - ​       realloc(void *ptr,size_t size);realloc是在已经分配好内存块的重新分配，如果开始指针分配为NULL，则和malloc用法一致，否则如果开始内存块小，保存原内存块，再次基础新增，如果是开始内存块大，则在此基础减去尾部内存块。返回值是分配好内存块的头指针。

  - malloc(zise_t size);malloc是对没有分配过内存块的直接进行分配，返回值是分配好内存块的返回值是分配好内存块的头指针。通过malloc分配好的内存块一般要用free(size_t size)来释放内存块。
  - 通过realloc和malloc来申请的内存块是返回的指针是无符号类型的，所以在返回后程序员可以定义为任意类型的指针

- 第二级配置器　__default_alloc_template剖析

  - 每次配置一大块内存，并维护对应之自由链表，下次若再有相同大小的内存需求，直接从fre-list中拨出，若客端释还小额区块，则由配置器回收到free-list中

  - free-list的实现

    ```c++
    union obj{
        union obj* free_list_link;
        char client_data[1];
    };
    ```

  - 空间配置器函数allocate()

    - 首先判断区块大小，大于128bytes就调用第一级配置器，小于就检查对应的free list,如果free list内有可用的区域，就直接使用，否则将区块大小上调到8的倍数边界，调用refill(),准备为free list重新填充空间

  - 空间释放函数deallocate()

    - 大于128bytes就调用第一级配置器，小于则找出对应的free list，将区块回收

  - 重新填充free lists

    - 为free list重新填充空间，新的空间将取自内存池

  - 内存池

    - 从内存池中取空间给free list使用，是chunk_alloc()的工作

### 2.3 内存基本处理工具

- memset函数及其用法
  - void *memset(void *s, int c, unsigned long n);
  - #include <string.h>
  - 函数的功能是：将指针变量 s 所指向的前 n 字节的内存单元用一个“整数” c 替换，注意 c 是 int 型。s 是 void* 型的指针变量，所以它可以为任何类型的数据进行初始化。
  - memset() 的作用是在一段内存块中填充某个给定的值。因为它只能填充一个值，所以该函数的初始化为原始初始化，无法将变量初始化为程序中需要的数据。用memset初始化完后，后面程序中再向该内存空间中存放需要的数据。
  - memset 一般使用“0”初始化内存单元，而且通常是给数组或结构体进行初始化。
- memcpy函数
  - void *memcpy(void *dest, const void *src, size_t n);
  - 从src的开始位置拷贝n个字节的数据到dest。如果dest存在数据，将会被覆盖。memcpy函数的返回值是dest的指针。memcpy函数定义在string.h头文件里。
- memmove函数
  - void *memmove( void* dest, const void* src, size_tcount );
  - 由src所指内存区域复制count个字节到dest所指内存区域。
  - memcpy只是简单的将两块内存区域当作没有关系的相互独立内存区域进行内存的拷贝，而memmove则考虑了当两块内存区域有重叠时所采用不同方向的拷贝模式进行处理。
  - memcpy()函数是从前往后拷贝；假入出现内存重叠的现象；拷贝结果可能出错； memmove()函数在memcpy()函数的基础上加入了对内存重叠拷贝的处理；引入了倒序拷贝的方式处理内存重叠的某些情况；保证拷贝的正确性；
- uninitializaed_copy

  - 能够将内存的配置与对象的构造行为分离开来
- uninitialized_fill 
  - 也能能够将内存的配置与对象的构造行为分离开来
- uninitialized_fill_n
  - 为指定范围内的元素设定相同的值
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-09 14-00-16.png)

- POD指Plain Old Data,即标量型别或传统的C struct 型别，POD型别必然拥有trivial ctor/dtor/copy/assignment函数，对POD型别采用最有效的初值填写手法，对non-POD型别采取最保险安全的做法



## 第三章　迭代器概念与traits编程技法

- iterator模式定义：提供一种方法，使之能够依序巡防某个聚合物(容器)所含的各个元素，而又无需暴露该聚合物的内部表述方式

### 3.1 迭代器设计思维

- STL的中心思想:将数据容器和算法分开，彼此独立设计，最后再以一贴胶着剂(迭代器)将它们撮合在一起

### 3.2 迭代器是一种smart pointer

- 迭代器是一种行为类似指针的对象
- 迭代器最重要的工作是对operator* 和operator->进行重载
- auto_ptr的源代码在头文件<memory>中
- 每一种STL容器都提供有专属迭代器

### 3.3 迭代器相应型别

- 利用function template的参数推导机制

### 3.4 Traits编程技法-STL源代码门钥

- 迭代器所指对象的型别，称为该迭代器的value type

- 对于用于模板定义的依赖于模板参数的名称，只有在实例化的参数中存在这个类型名，或者这个名称前使用了`typename`关键字来修饰，编译器才会将该名称当成是类型。除了以上这两种情况，绝不会被当成是类型。

  因此，如果你想直接告诉编译器`T::iterator`是类型而不是变量，只需用`typename`修饰：

- template partial specialization

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-10 15-10-23.png)

- 最常用的迭代器相应型别有五种: value type, difference type, pointer, reference,iterator catagoly

  ```c++
  template<class T>
  struct iterator_traits{
      typedef typename I::iterator_category iterator_category    ;
      typedef typename I::value_type  value_type;
        typedef typename I::difference_type  difference_type;
         typedef typename I::pointer  pointer;
          typedef typename I::refereance  refereance;
      
  };
  ```

  - iterator_traits必须针对传入之型别为pointer及pointer-to-const者，设计特化版本

  

- 迭代器型别之一: value type,即迭代器所指对象的型别

- 迭代器型别之二：difference type

  - 表示两个迭代器之间的距离，也可以表示一个容器的最大容量
  - 针对原生指针的偏特化版本
  - 针对pointer-to-const的偏特化版本

- 迭代器相应型别之三: reference type

  - 函数如果要传回左值，都是以by reference的方式进行

- 迭代器相应型别之四: pointer type

- 迭代器相应型别之五:iterator_category

  - 五种迭代器:![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-11 11-28-44.png)
  - 最好能够在编译期就选择正确的版本，重载函数机制可以达到这个目标
  - 原生指针是一种Random Access Iterator
  - int()  会产生一个int临时对象
  - 任何一个迭代器，其类型应该落在该迭代器所属之各种类型中，最强化的那个
  - STL算法的命令规则: 以算法所能接受之最低阶迭代器类型，来为迭代器型别参数命名
  - 消除单纯传递调用函数:　利用继承关系

### 3.5 std::iterator的保证

- 任何迭代器都应该提供五个内嵌相应型别，以利于traits萃取
- STL提供了一个iterator class，若每个新设计的迭代器都继承它，就可保证符合STL规范
- 设计适当的相应型别，是迭代器的责任，设计适当的迭代器，则是容器的责任
- **traits 编程技法大量运用于STL实现品中，它利用内嵌型别的编程技巧与编译器的tempalte参数推导功能，增强C++未能提供的关于型别认证方面的能力，弥补C++不为强型别语言的遗憾**

### 3.6 iteraotr源代码完整重列

### 3.7 SGI STL的私房菜: __type_traits

- \__type__traits负责萃取型别的特性，这个型别是否具有non-trival的构造、析构、拷贝、赋值，如果没有，直接采用最有效率的措施，内存直接处理操作

- 编译器只有面对class object形式的参数，才会做参数推导

- 对所有C++标量型别定义\__type_traits的特化版本

- 一个class什么时候该有自己的non-trival default constructor, copy constructor,assignment constructor, destructor?   如果class内含有指针，并且对它进行内存动态配置，那么这个class就需要实现出自己的non-trival-xxx



## 第四章　序列式容器

### 4.1 容器的概观与分类

- STL容器即是将运用最广的一些数据结构实现出来
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-16 15-03-18.png)

- 序列式容器
  - 其中的元素都可序，但未必有序

### 4.2 vector

- 概述

  - 扩充空间是:  配置新空间/ 数据移动/ 释还旧空间的大工程
  - array是静态空间，一旦配置了就不能改变
  - vector是动态空间，随着元素的加入，它的内部机制会自行扩充空间以容纳新元素

- vector定义

- vector的迭代器

  - vector维护的是一个连续线性空间，提供的是　Random Access
  - vector的迭代器是普通指针

- vector的数据结构

  - 连续线性空间
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-16 15-26-20.png)
    - begin()
    - end()
    - size()
    - capacity()
    - empty()
    - operator[]
    - front()
    - back()

- vector的构造与内存管理

  - vector缺省使用alloc作为空间配置器
  - 如果原大小为0，则配置1,如果不为0，则配置原大小的两倍，前半段用来放置原数据，后半段用来放置新数据
  - 所谓动态增加大小，并不是在原空间之后接续新空间，而是以原空间大小两倍另外配置一块较大空间，然后将原内容拷贝过来，然后在原内容之后构造新元素，并释放原空间，因此，对vector的任何操作，一旦引起空间重新配置，指向原vector的所有迭代器就都失效了

- vector的元素操作
  - pop_back()
  - erase()
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-16 15-52-22.png)
  - insert()  插入完成后，新节点将位于哨兵迭代器所指之节点的前方
  - 三种情况

### 4.3 list

- 概述

  - 每次插入或删除一个元素，就配置或释放一个元素空间
  - 对于任何位置的元素插入或移除，list永远是常数时间

- list的节点

   - 是一个双向链表

- list的迭代器

  - list的节点不保证在存储空间连续存在，不能使用普通指针
  - list提供的是Bidirectional Iterators
  - 插入和接合操作都不会造成原来的list迭代器失效
  - 迭代器内部有一个普通指针，指向list的节点

- list的数据结构

   - SGI list是一个环状双向链表，只需要一个指针，就可以完整表现整个链表
   - **只要在环状链表的尾端加上一个空白节点，让node指针指向该节点，就能够符合STL的前闭后开区间**

- list的构造与内存管理

   - insert插入，插入之后新节点将位于哨兵迭代器所指之节点的前方，这是STL对于插入操作的标准规范
   - 插入前的所有迭代器在插入后仍然有效

- list的元素操作

   - push_front()
   - push_back()
   - erase()
   - pop_front()
   - pop_back()
   - clear
   - remove 
   - unique
   - transfer  将某连续范围内的元素迁移到某个特定位置之前
   - splice
   - reverse
   - sort
   - merge
   - STL算法sort()只接受RandomAccessIterator


### 4.4 deque

- 概述
  - deuqe是一种双向开口的连续线性空间，可以在头尾两端分别做元素的插入和删除操作
  - 没有容量的概念，动态地以分段连续空间组合而成
  - deque 也提供Random Access Iterator,不是普通指针
- deque的中控器
  - dueque由一段一段的定量连续空间构成，一旦有必要在deque的前端或尾端增加新空间，便配置一段定量连续新空间，串接在deque的头端或尾端
  - map是一个T**,所指之物又是一个指针，指向缓冲区
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-18 14-20-02.png)

 

- deque的迭代器

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-18 14-30-30.png)

  -   一旦行进遇到缓冲区边缘，要特别小心，视前进或后退而定，可能需要调用set_node()跳一个缓冲区

- deque的数据结构

    - map是块连续空间，每个元素都是指针，指向一个缓冲区

- deque的构造与内存管理

    ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-19 14-40-03.png)

    - 如果map的节点备用空间不足，则配置更大的，拷贝原来的，释放原来的

- deque的元素操作　pop_back, pop_front,clear, erase, insert

    - deque的最初状态(无任何元素时)保有一个缓冲区



### 4.5 stack

- 概述

  - stack是一种先进后出(FILO)的数据结构
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-19 15-01-58.png)

- stack定义

    - 以某种既有容器作为底部结构，将其接口改变，使之符合"先进后出"的特性，形成一个stack,SGI STL以deque作为缺省情况下的stack底部结构。具有这种修改某物接口，形成另一种风貌之性质者，称为adapter(配接器)

- stack没有迭代器

    - stack所有元素都必须符合先进后出的条件，只有stack顶端的元素，才有机会被外界取用，stack不提供走访功能，也不提供迭代器

- 以list 作为stack的底层容器

    - list也是双口开向的容器
    - 以list为底部结构并封闭其头端开口，能形成stack


### 4.6 queue

- 概述
  - queue是一种FIFO的数据结构，queue有两个出口，不允许遍历
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-23 14-14-44.png)
- queue定义完整列表
  - queue以deque作为缺省情况下的queue底部结构
- queue没有迭代器
- 以list作为queue的底层容器

### 4.7 heap

- 概述
  - heap并不归属于STL容器组件，扮演priority queue的助手
  - binary heap是一种完全二叉树
  - array可以轻易实现完全二叉树，为隐式表述法，实际实现是以vector为底部容器
  - max-heap  和min-heap,  STL供应的是max-heap
- heap算法
  - push_heap算法
    - 执行上溯程序，将新结点与其父节点比较
  - pop_heap算法
    - 执行下溯程序，将空间节点与其较大子节点对调，并持续下放，直至叶节点为止，然后将前述被割舍元素值设定给这个已到达叶层的空洞结点，再对它执行一次上溯程序
  - sort_heap算法
    - 不断对heap进行pop操作，便可获得排序操作
  - make_heap算法
    - 用来将一段现有的数据转化为一个heap
- heap没有迭代器

### 4.8 priority_queue

- 概述

  - 一个拥有权值概念的queue

  - priority_queue完全以底部容器为根据，再加上heap处理规则，缺省情况下以vector为底部容器

  - priority_queue没有迭代器

  - less与greater

    - ```c++
      
      template<class _Ty>
      struct greater : public binary_function<_Ty, _Ty, bool>
      {	// functor for operator>
      	bool operator()(const _Ty& _Left, const _Ty& _Right) const
      	{	// apply operator> to operands
      		return (_Left > _Right);
      	}
      };
       
      // TEMPLATE STRUCT less
      template<class _Ty> 
      struct less : public binary_function<_Ty, _Ty, bool>
      {	// functor for operator<
      	bool operator()(const _Ty& _Left, const _Ty& _Right) const
      	{	// apply operator< to operands
      		return (_Left < _Right);
      	}
      };
      ```

    - ```c++
      
      #include <iostream>
      #include <algorithm>
      #include <functional>
       
      using namespace std;
       
      int main()
      {
      	int nums[] = {5, 3, 1, 2, 4};
          int length = sizeof(nums)/sizeof(int);	
      	std::cout << "nums length is " << length << std::endl;
      	sort(nums, nums + length, greater<int>());
      	for (int i = 0; i < length; ++i)
      	{
      		std::cout << nums[i] << "\t";	
      	}
      	std::cout << std::endl;
      	sort(nums, nums + length, less<int>());
      	for (int i = 0; i < length; ++i)
      	{
      		std::cout << nums[i] << "\t";	
      	}
      	std::cout << std::endl;
      	return 0;
      }
      ```





### 4.9 slist

- 概述

  - SGI STL提供了一个单向链表
  - slist的迭代器属于单向的Forward Iterator
  - 插入、接合、移除等操作不会造成原有的迭代器失效
  - 除了slist起点附近的区域之外，在其他位置上采用insert或erase操作函数，都属于不智之举，提供insert_after()和erase_after()
  - slist不提供push_back,只提供push_front

- slist的节点

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-24 18-42-11.png)

- slist的迭代器

- slist的数据结构

- slist的元素操作

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-24 19-08-41.png)




## 第五章　关联式容器

- 标准的STL关联式容器分为set和map，以及这两大类的衍生体multiset和multimap.这些容器底层机制均以RB-tree(红黑树)完成，RB-tree也是一个独立容器，并不开放给外界使用
- 不在标准规格之列的: hash table(散列表)
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-25 16-43-08.png)

- 每笔数据都有一个键值(key)和一个实值(value)，当元素被插入到关联式容器中时，容器内部结构(可能是RB-tree或hash-table)便依照其键值大小，以某种特定规则将这个元素放置于适当的位置，关联式容器没有头尾
- 关联式容器的内部结构是一个平衡二叉树，平衡二叉树有AVL-tree, RB-tree,AA-tree



### 5.1 树的导览

- 几乎所有操作系统都将文件存放在树状结构里

- 二叉搜索树

  - 可提供对数时间的元素插入和访问
  - 任何节点的键值大于其左节点的键值，小于其右节点的键值

- 平衡二叉搜索树

  - AVL-tree, RB-tree, AA-tree均可实现平衡二叉树

- AVL Tree

  - 任何节点的左右子树高度相差最多1, 保证对数深度平衡状态
  - 插入新的节点后造成的不平衡状态有四种
    - 左左
    - 右右
    - 左右
    - 右左
  - 单旋转
    - 左左、右右
  - 双旋转
    - 左右、右左


### 5.2 RB-tree(红黑树)

- 一个被广泛运用的平衡二叉树
- 满足如下规则:
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-26 13-42-54.png)

- **根据规则4,新增节点必须为红，根据规则3,新增节点之父必须为黑**

- 插入节点

  - 破坏规则后必须旋转树形并改变节点颜色

  - 状况1:

    ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-26 13-51-58.png)

  - 状况2:

    ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-26 13-54-39.png)

    

  - 状况3:

    ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-26 13-57-41.png)

     

  - 状况4:

    ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-26 13-59-48.png)

    

    

- 一个由上而下的程序

- RB-tree的节点设计

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-26 18-47-48.png)

- RB-tree的迭代器

  - 双层节点结构和双层迭代器结构
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-26 18-51-03.png)

  - RB-tree迭代器属于双向迭代器，不具备随机定位能力

- RB-tree的数据结构

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-26 19-16-25.png)

- RB-tree的构造与内存管理

  - 以现有的RB-tree复制一个新的RB-tree
  - 产生一颗空空如也的树
  - 最需要的是边界情况的发生，SGI STL特别为根节点再设计一个父节点，名为header
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-26 19-22-45.png)

  - 每当插入新节点时，不但要依照RB-tree的规则来调整，并且维护header的正确性，使其父节点指向根节点，左子节点指向最小节点，右子节点指向最大节点

- RB-tree的元素操作

  - insert_equal()
  - insert_unique()
  - __reb_tree_rebalance()
  - 寻找RB树中是否有键值为k的节点

- 红黑树比AVL的优势所在

  - 红黑是用非严格的平衡来换取增删节点时候旋转次数的降低，任何不平衡都会在三次旋转之内解决，而AVL是严格平衡树，因此在增加或者删除节点的时候，根据不同情况，旋转的次数比红黑树要多
  - 如果插入一个node引起了树的不平衡，AVL和RB-Tree都是最多只需要2次旋转操作，即两者都是O(1)；但是在删除node引起树的不平衡时，最坏情况下，AVL需要维护从被删node到root这条路径上所有node的平衡性，因此需要旋转的量级O(logN)，而RB-Tree最多只需3次旋转，只需要O(1)的复杂度。
  - 其次，AVL的结构相较RB-Tree来说更为平衡，在插入和删除node更容易引起Tree的unbalance，因此在大量数据需要插入或者删除时，AVL需要rebalance的频率会更高。因此，RB-Tree在需要大量插入和删除node的场景下，效率更高。自然，由于AVL高度平衡，因此AVL的search效率更高。
  - map的实现只是折衷了两者在search、insert以及delete下的效率。总体来说，RB-tree的统计性能是高于AVL的。