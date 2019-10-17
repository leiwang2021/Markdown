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

### 5.3 set

- set元素的键值(key)就是实值(value)，所有元素都会根据元素的键值自动被排序,set不允许两个元素有相同的键值
- set iterators是一种constant iterators, 迭代器在操作前和操作后都有效
- set以RB-tree为底层机制
- 面对关联式容器，应该使用其所提供的find函数来搜寻元素，会比使用STL算法find()更有效率，因为STL算法find()只是循序搜寻
- 企图通过迭代器来改变set元素，是不被允许的，因为任意改变set元素值，会严重破坏set组织

### 5.4 map

- 所有元素都会根据元素的键值(key)自动被排序，map的所有元素都是pair,同时拥有key和value,pair的第一元素被视为键值，第二元素被视为实值，map不允许两个元素有相同的键值
- map元素的键值关系到map元素的排列规则，任意改变map元素键值将会严重破坏map组织，如果想要修改元素的实值，是可以的。迭代器在操作前和操作后都有效
- map以RB-tree为底层机制
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-27 14-31-17.png)

-  map不允许相同键值存在，使用insert_equal



### 5.5 multiset

- 用法和set完全相同，唯一的差别是它允许键值重复，插入操作是insert_equal()

### 5.6 multimap

- 与map完全相同，唯一的差别在于它允许键值重复，插入操作是insert_equal()



### 5.7 hashtable

- 二叉搜索树具有对数平均时间的表现，构造在一个假设上: 输入数据具有足够的随机性
- hash table(散列表)　在插入、删除、搜寻等操作上也具有常数平均时间的表现，是以统计为基础的，不需要依赖随机性

- 概述
  - hash table可被视为一种字典结构，在于提供常数时间之基本操作
  - 散列函数
  - 解决碰撞的方法: 线性探测、二次探测、开链等
- 线性探测
  - 元素的删除，必须采用惰性删除，只标记删除记号
- 二次探测
- 开链
  - 在每一个表格元素中维护一个list,hash function 为我们分配某一个list, 然后我们在那个list身上执行元素的插入、搜寻、删除等操作。SGI STL的hash table便是采用这种做法

- hashtable 的桶子与节点

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 14-32-36.png)

- hashtable的迭代器

  - hashtable迭代器必须永远维系着与整个"buckets vector"的关系，并记录目前所指的节点
  - 迭代器是 forward迭代器

- hashtable的数据结构

  - vector\<node*,Alloc> buckets;

  - buckets以vector完成
  - bkt_num()调用hash function 

- hashtable的构造与内存管理

  - reserve是容器预留空间，但在空间内不真正创建元素对象，所以在没有添加新的对象之前，不能引用容器内的元素
  -  resize是改变容器的大小，且在创建对象，因此，调用这个函数之后，就可以引用容器内的对象了
  - 插入操作与表格重整(resize)
    - insert_unique()   如果发现与链表中的某键值相同，就不插入，立刻返回
    - 令新节点成为链表的第一个节点
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 15-17-33.png)

  - insert_equal()　　如果发现与链表中的某键值相同，就马上插入。然后返回
  - 判断元素的落脚处
    - bkt_num()函数
  - 复制和整体删除
    - 整个hash table由vector和linked-list组合而成
    - clear( )
    - copy_from()
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 15-34-33.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 15-35-17.png)

  - find  count函数　　输入参数为键值

- hash functions

  - 仿函数
  - 有些型别，未给它定义hash function,用户需要自己定义



### 5.8 hash_set

- hash_set操作行为，都只是转调用hashtable的操作行为而已
- RB-tree有自动排序功能，而hashtable没有
- set元素的实值就是键值
- 操作都使用insert_unique(),不允许键值重复
- C字符串的相等于否，必须一个字符一个字符地比较，不能直接以const char*做比较



### 5.9 hash_map

- hash_map的操作行为，都是转调用hashtable的操作行为而已

### 5.10 hash_multiset

### 5.11 hash_multimap



## 第六章　算法

### 6.1 算法概观

- 特殊的算法往往搭配特定的数据结构
- 算法分析与复杂度表示O( )
- STL算法总览
- 质变算法-会改变操作对象之值
  - 所有STL算法都作用在由迭代器所标志的区间上
  - 运算过程中会更改迭代器所指的元素内容
- 非质变算法- 不改变操作对象之值
- STL算法的一般形式
  - 每一个STL算法的声明，都表现出它所需要的最低程序的迭代器类型
  - replace()使用内建的equality操作符进行对比操作，replace_if()则以接收到的仿函数进行对比行为
  - 质变算法通常提供两个版本: 一个是in-place版，另一个是copy版，如replace()   replace_copy()
  - 所有数值算法，用户必须包含上层的<numeric>
  - 其他STL算法，必须包含上层的<algorithm>

### 6.2 算法的泛化过程

- 只要把操作对象的型别加以抽象化、把操作对象的标示法和区间目标的移动行为抽象化，整个算法也就在一个抽象层面上工作了，称为算法的泛型化
- 当指针指向array尾端以外的位置时，它只能用来与其他array指针相比较，不能提领其值



### 6.3 数值算法

- 运用实例

  - ostream_iterator

- accumulate

  ```c++
  T accumulate(InputIterator first, InputIterator last, T init);
  T accumulate(InputIterator first, InputIterator last, T init, BinaryOpration binary_op);
  ```

- adjacent_difference  

  - 与partial_sum互为逆运算

- inner_product

  - 能够计算[first1, last1)和[first2, first2+(last1-first1))的一般内积

- partial_sum

- power

  ```c++
  template<class T, class Integer, class MonoidOperation>
  T power(T x, Integer n, MonoidOperation op) 
  {
  	if (0 == n)
  		return x;
  	else {
  		while (0 == (n & 1)) {
  			n >>= 1;
  			x = op(x, x);
  		}
  		T result = x;
  		n >>= 1;
  		while (n != 0) {
  			x = op(x, x);
  			if (0 != (n & 1)) 
  				result = op(result, x);
  			n >>= 1;
  		}
  		return result;
  	}
  }
  ```

  - x^n = x^(2^i0 + 2^i1 + ... + 2^ik)
  - 步骤一：先找到N的二进制表示里面最低2的次幂的地方k1
  - 步骤二：找到了第一个2^k之后，后续的X ^ ( 2^(k+1) )就等于( X ^ (2^k) ) ^2
  - 步骤三：然后依次循环，来计算N的二进制表示里，每一位的情况。根据N的每一位情况，来计算X的幂次方

- iota



### 6.4 基本算法<stl_algobase.h>

- 运用实例

- equal

  - 第一版本缺省采用equality
  - 第二版本允许指定仿函数

- fill

  - 将所有元素改填新值

- fill_n

  - 将[first, last)内的前n个元素改填新值
  - inserter()可产生一个用来修饰迭代器的配接器

- iter_swap

  - iterator_traits的运用

- lexicographical_compare

  - 以字典排列方式对两个序列进行比较
  - memcmp()是C标准函数，正是以unsigned char的方式来比较两序列中一一对应的每一个bytes

- max

- min

- mismatch

  - 用来平行比较两个序列，指出两者之间的第一个不匹配点，返回一对迭代器

- swap

- copy

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-09 15-54-35.png)

  - 如果输出区间的尾端与输入区间重叠，可以使用copy
  - 如果输出区间的起头与输入区间重叠，可以使用copy_backward
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-09 16-37-22.png)
  - memove()会先将整个输入区间的内容复制下来，没有被覆盖的危险，copy算法根据其所接收的迭代器特性决定是否调用memove()
  - copy更改的是迭代器所指对象，而非更改迭代器本身
  - 如果指针所指对象拥有non-tirval assignment operator,复制操作就一定要通过它来进行，如果指针所指对象拥有的是trival assignment operator,复制操作可以不通过它，直接以最快速的内存拷贝方式完成(memove())
  - 程序中所有用户自定义型别，都被编译器视为拥有non-trival ctor/dtor/operator=  ,如果我们确知某个class具备的是trival ctor/dtor/operator=,我们就得自己动手为它做特性设定，可借用<type_traits.h>中的__type_traits<T> 

- copy_backward

  - 与copy类似
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-09 16-36-57.png)
  - 迭代器必须是BidirectionalIterators



### 6.5 set相关算法

- 并集(union)  交集(intersection)  差集(difference)   对称差集(symmetric difference)
- 本节的四个算法所接受的set, 必须是有序区间，元素可以重复出现
- 第一版本，第二版本允许用户指定a<b的意义
- 当集合允许重复元素的存在时，并集，交集，差集，对称差集的定义都与直观定义有些微的不同

- set_union

  - s1 s2及其并集都是以排序区间表示，返回值为一个迭代器，指向输出区间的尾端

  - max(m,n)  重复的元素
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-10 15-49-03.png)

  - set_intersection
    - min(m,n)重复的元素，并且全部来自s1
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-10 15-52-34.png)

  - set_difference
    - 能构造出集合s1-s2,出现s1但不出现于s2的每一个元素
    - s1出现n次，s2出现m次，出现max(n-m,0)次
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-10 15-59-28.png)

  - set_symmetric_difference
    - 它能构造集合(s1-s2)U(s2-s1)
    - |n-m| 
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-10 16-04-10.png)

### 6.6 heap算法

### 6.7 其他算法

- 单纯的数据处理

- adjacent_find

  - 找出第一组满足条件的相邻元素

- count

  - 返回与value相等的元素个数

- count_if

  - 将一个仿函数施行于区间内，返回true的所有元素个数

- find

- find_if

  - 找到第一个令仿函数运算结果为true者，没有则返回last

- find_end
  - 在序列1所覆盖的区间内，查找序列2的最后一次出现点，没有则返回last1
  - 正向迭代器和负向迭代器

- find_first_of

  - 以[first2,last2)区间内的某些元素为查找目标，寻找它们在[first1,last1)区间内的第一次出现点

- for_each

  - 将仿函数f施行于区间内的每一个元素身上，不可以改变元素内容，若要修改，应该使用transform()

- generate

  - 将仿函数的运算结果填写在区间内的所有元素身上

- generate_n

  - 填写在n个元素身上

- includes(应用于有序区间)

  - 判断s2是否涵盖于s1,都必须是有序集合
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-12 15-57-40.png)

  - 版本一
  - 版本二　　comp的型别是Compare

- max_element

  - 返回一个迭代器，指向序列之中数值最大的元素

- merge(应用于有序区间)

  - 将两个经过排序的集合s1和s2，合并起来置于另一段空间，所得结果是一个有序序列。返回一个迭代器
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-12 16-09-57.png)

- min_element

  - 返回一个迭代器，指向序列之中数值最小的元素

- partition 
  - 所有被一元操作符判定为true的元素都会被放在区间的前段，被判定为false的元素，都会被放在区间的后段
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-12 16-21-01.png)

- remove 移除(但不删除)

  - 移除所有与value相等的元素，并不真正从容器中删除那些元素,容器大小未改变

- remove_copy
  - 将结果复制到一个以result标示起始位置的容器身上，新容器和原容器可以重叠
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-12 16-30-41.png)

- remove_if
  - 移除所有被仿函数核定为treu的元素，容器大小未改变
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-12 16-32-28.png)

- remove_copy_if

- replace

  - 将所有旧值都以新值替代

- replace_copy

  - 新序列会被复制到result所指的容器中

- replace_if

  - 被pred评估为true的元素都以新值取而代之

- replace_copy_if

- reverse
  - 将序列的元素在原容器中颠倒重排
  - 设计为双层结构

- reverse_copy

- rotate
  - 将[first,middle)内的元素和[middle,last)内的元素互换
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-12 16-46-09.png)

- 迭代器的移动能力，影响了这个算法的效率，所以设计为双层结构
  - forward iterator版
  - bidirectional iterator版
  - random access iterator版

- rotate_copy

- search

  - 序列1内是否存在与序列2完全匹配的子序列

- search_n
  - 查找连续count个符合条件之元素所形成的子序列
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-12 17-30-36.png)

- swap_ranges

  - 将[first1,last1)区间内的元素与从first2开始，个数相同的元素互相交换，这两个序列可位于同一容器中，也可位于不同的容器中

- transform
  - 两个版本
  - 第一版本以仿函数作用于[first, last)中的每一个元素身上，并将结果放进迭代器result所标示的容器中
  - 第二版本以仿函数作用于一双元素身上，结果放在result中

- unique

  - 只移除相邻的重复元素

- unique_copy

- lower_bound(应用于有序区间)

  - 二分查找
  - 在不破坏排序状态的原则下，可插入value的第一个位置

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-14 16-46-13.png)

- upper_bound

  - 在不破坏顺序的情况下，可插入value的最后一个合适位置

- binary_search(应用于有序区间)

  - 二分查找法
  - 在已排序的[first,last)中查找元素value
  - 利用lower_bound函数

- next_permutation
  - 如a b c的排列组合:   abc  acb  bac  bca  cab  cba
  - next_permutation会获得[first,last)所标示之序列的下一个排列组合

- prev_permutation

- random_shuffle
  - 将[first,last)的元素次序随机重排
  - 产生一个均匀分布，任何一个排列被选中的几率为1/N!
  - 版本一使用内部随机数产生器
  - 版本二使用一个会产生随机随机数的仿函数，该仿函数的传递方式是by_reference

- partial_sort/ partial_sort_copy
  - 接受一个middle迭代器，使序列中的middle-first个最小元素以递增顺序排序
  - 算法内部使用heap sort来完成任务
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-14 17-25-25.png)

- sort

  - 接受两个随机存取迭代器，将区间内的所有元素以递增方式由小到大排列

  - 所有关系型容器都拥有自动排序功能，不需要用到sort算法

  - sort算法适合于vector  deque

  - 数据量大时采用Quick sort,分段递归排序，数据量小于某个门槛后，改用Insertion Sort

  - Insertion Sort
    - 复杂度为O(N^2), 数据量小时有不错的效果
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-14 19-29-24.png)

  - Quick sort
    - 平均复杂度为O(NlogN)
    - IntroSort最坏情况为O(NlogN)
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-14 19-32-31.png)

    - Quick Sort采行分段排序，分段的原则通常采用median-of-three(首、尾、中英的中间值)

    - Partitioning(分割)

      ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-14 19-49-17.png)

    - threshold阈值

      - Quick Sort会为了极小的子序列而产生许多的函数递归调用
      - 适当评估序列的大小，决定采用Quick Sort还是Insertion Sort

    - final insertion sort

    - introsort

      - 当分割行为有恶化为二次行为的倾向时，能够自我监测，转而改用Heap Sort,但比一开始使用Heap Sort效果好

  - SGI STL sort

    - RW版本用的是纯粹是Quick Sort,而不是IntroSort

- equal_range(应用于有序区间)

  - 二分查找的一个版本
  - 返回一对迭代器[i,j)区间内的每个元素都等同于value
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-14 20-18-56.png)

     

- inplace_merge(应用于有序区间)

  - 如果两个连接在一起的序列[first,middle)和[middle,last)都已排序，那么inplace_merge可将它们结合成单一一个序列，并保持有序性
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-14 20-32-43.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-14 20-33-15.png)

- nth_element

  - 只接受RandomAccessIterator
- merge_sort

  - 将区间对半分割，左右两段各自排序，再利用inplace_merge重新组合为一个完整的有序序列，对半分割的操作可以递归进行，直到每一小段的长度为0或1



## 第七章　仿函数(函数对象)

### 7.1 仿函数概观

- 一种具有函数特质的对象

- ```c++
  #include<functional>
  greater<int> ig;
  ig(4,6);
  greater<int>()(4,6)  //先产生临时对象，再调用
  ```



### 7.2 可配接的关键

- STL仿函数应该有能力被函数配接器修饰，每一个仿函数必须定义自己的相应型别
- unary_function 用来呈现一元函数的参数型别和回返值型别
- binary_function 用来呈现二元函数



### 7.3 算术类仿函数

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-15 21-01-05.png)

- 证同元素(identity element)

### 7.4 关系运算类仿函数

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-15 21-05-13.png)

### 7.5 逻辑运算类仿函数

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-15 21-07-03.png)

### 7.6 证同、选择、投射

- identity
- select1st 接受一个pair,传回其第一元素
- select2nd 接受一个pair,传回其第二元素
- project1st  传回第一参数
- project2st　　传回第二参数



## 第八章　配接器

- adapter事实上是一种设计模式

### 8.1 配接器之概观与分类

- 应用于容器container adapters
  - queue 
  - stack
- 应用于迭代器　iterator adapters
  - insert iterators
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-17 16-09-51.png)
  - reverse iterators
  - iostream iterators
    - 可将迭代器绑定到某个iostrem上
  - 由<iterato>获得
- 应用于仿函数 function adapters
  - <functional>
  - 任何期望获得配接能力的组件，本身必须是可配接的
  - 以经过修饰的一般函数搭配STL算法
  - 以修饰过的成员函数搭配STL算法
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-17 16-25-21.png)



### 8.2 container adapters

- stack
- queue

### 8.3 iterator adapters

- insert iterators

  - operator=操作符调用底层容器的push_front()或push_back()或insert()

- reverse iterators

  - rbegin()
  - rend()
  - 双向序列容器且需要提供begin()和end()
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-17 16-51-27.png)

  - 对逆向迭代器取值，就是将对应之正向迭代器后退一格而后取值

- stream iterators

  - istream_iterator
    - 其实是在istream iterator内部维护一个istream member
    - 只要客户端定义一个istream iterator并绑定到某个istream object,程序便立刻停在istream_iterator<T>::read()函数，等待输入，因此在必要的时候才定义istream_iterator
    - 客户端对于这个迭代器所做的operator++ 操作，会被导引调用迭代器内部所含的istream_iterator的输入操作
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-17 19-04-10.png)
  - ostream_iterator
    - 在其内部维护一个ostream member,客户端对于这个迭代器所做的operator=操作，会被导引调用对应的ostream member的输出操作

### 8.3 function adapters

- 每一个function adapters也内藏了一个member object,其型别等同于它所要配接的对象
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-17 19-47-26.png)

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-17 19-49-58.png)

- 对返回值进行逻辑否定: not1  not2
- 对参数进行绑定，bind1st  bind2nd
- 用于函数合成: compose1  compose2
- 用于函数指针: ptr_fun
  - 能将一般函数当做仿函数使用
  - 用一个仿函数将一元函数指针包起来
- 用于成员函数指针: mem_fun  mem_fun_ref
  - 将成员函数当作仿函数使用
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-10-17 20-02-33.png)

- mem_fun1  mem_fun1_ref