# 深度探索C++对象模型

- 对象模型是深层结构的知识，关系到"与语言无关，与平台无关，跨网络可执行"软件组件的基础原理。了解C++对象模型，是学习软件三大规格(COM, CORBA, SOM)的技术基础。

## 第一章　关于对象

## 1.1 C++对象模式

- data: static和nonstatic     functions: static nonstatic  virtual
- 被const修饰的函数是不能改变对象状态的（即成员变量）
- 静态成员变量 -静态成员变量属于整个类所有
      -静态成员变量的生命期不依赖于任何对象，为程序的生命周期
      -可以通过类名直接访问公有静态成员变量
      -所有对象共享类的静态成员变量
      -可以通过对象名访问公有静态成员变量
      -静态成员变量需要在类外单独分配空间
      -静态成员变量在程序内部位于全局数据区 (Type className::VarName = value)
- 静态成员函数
      -静态成员函数是类的一个特殊的成员函数
      -静态成员函数属于整个类所有，没有this指针
      -静态成员函数只能直接访问静态成员变量和静态成员函数
      -可以通过类名直接访问类的公有静态成员函数
      -可以通过对象名访问类的公有静态成员函数
      -定义静态成员函数，直接使用static关键字修饰即可

#### 简单对象模型

- 一个object是一系列的slots,每一个slot指向一个members, members按其声明顺序，各被指向一个slot. 每一个data member 或function member都有自己的一个slot
- 只有指向member的指针才放在object内

#### 表格驱动对象模型

- 一个data member table 和一个member function table

#### C++对象模型

- virtual table (vtbl)
- vptr:  class对象的指针，指向相关的vtbl
- 虚拟继承
- base class table的应用
- virtual base class的原始模型是在class object中为每一个有关联的virtual base class 加上一个指针。其他演化出来的模型则要不是导入一个virtual base class table,就是扩展已存在的virtual table,以维护每一个virtual base class的位置.

#### 对象模型如何影响程序

- 代码会根据对象模型在内部有不同的转化结果

### 1.2 关键词带来的差异

#### 关键词的困扰

- class与struct

#### 策略性正确的struct

- 把单一元素的数组放在一个struct的尾端，每个struct objects可以拥有可变大小的数组，class不一定能行

- C++中处于同一个access section,必须保证以其声明顺序出现在内存布局中，然而被放置在多个access section中的各笔数据，排列顺序就不一定了

  ```c++
   struct mumble{
       char pc[1];
   };
   
   int main()
   {
       char const* string="Heelo";
       struct mumble* pmumb1=(struct mumble*)malloc(sizeof(struct mumble)+strlen(string)+1);
       strcpy(pmumb1->pc,string);
       cout<<pmumb1->pc<<endl;
       return 0;
   }
  ```

- 同理，base class 和derived classes的data members的布局也未有谁先谁后的强制规定，不能保证前面的struct技巧有效

- 组合，而非继承，才是把C和C++结合在一起的唯一可行方法(即struct和class)

- C struct 在C++的一个合理用途:当你要传递一个复杂的class object的全部或部分到某个C函数中去时，struct可以将数据封装起来，并保证与C兼容的空间布局

### 1.3 对象的差异

- C++程序设计模型直接支持三种programming paradigms

- procedural model:  同C一样

- abstract data type model,ADT, 处理的是一个拥有固定而单一类型的实例，在编译时期就完全定义好了

- object-oriented model ，处理一个未知实例，它的类型随便有所界定，却有无限可能

  ```c++
  //不确定类型
  Librar_materials *px=retrieve();
  Librar_materials &rx=*px;  //px或rx要么是Librar_materials类型，或其子类型
  
  //确定类型
  Librar_materials dx= *px;　//dx只能是Librar_materials类型
  ```

- 多态只存在于一个个的public class体系中

- C++以下方法支持多态

  - 经由一组隐式的转化操作，例如把一个derived class 指针转化为一个指向其public base type的指针

    ```c++
    shape *ps=new circle();
    ```

  - 经由virtual funtion机制

    ```c++
    ps->rotate()
    ```

  - 经由dynamic_cast和typeid运算符

    ```c++
    if(circle *pc=dynamic_cast<circle*>(ps))
    ```

  - 多态的主要功能是经由一个共同的接口来影响类型的封装，这个接口通常被定义在一个抽象的base class中，共享接口是以virtual funtion 机制引发的

- 一个class object的内存大小

  - 其nonstatic data members的总和大小
  - 加上由于alignment的需要而填补上去的空间
  - 为了支持virtual而由内部产生的任何额外负担，一个指针，不管指向哪一种数据类型，指针本身所需内存大小是固定的

- 指针的类型

  - 指向不同类型的各指针，是在其所寻址出来的object类型不同
  - 一个指向地址1000的整数指针，在32位机器上，将涵盖地址空间1000-1003(整数是4 bytes)
  - 一个类型为void* 的指针只能持有一个地址，不能通过它操作所指之object的缘故
  - 转换(cast)其实是一种编译器指令，大部分情况下它不改变一个指针所含的真正地址，**它只影响"被指出之内存的大小和其内容"的解释方式**

- 加上多态后

  - 一个pointer或一个reference之所以支持多态，是因为它们并不引发内存中的任何与类型有关的内存委托操作，会受到改变的，只有它们所指向的内存的“大小和内容解释方式”而已

  - 当一个base class object被直接初始化为一个derived class object时，derived object会被切割塞入较小的base type 内存中
  - ADT程序风格，称为OB, 所有函数调用操作都在编译时期解析完成，对象构建起来不需要设置virtual 机制

  

  

  

  

  

  



