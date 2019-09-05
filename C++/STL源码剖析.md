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

  






