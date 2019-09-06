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


