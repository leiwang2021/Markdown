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



  

  

  