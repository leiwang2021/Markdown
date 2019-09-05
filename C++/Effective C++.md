# Effective C++

- C++的四种编程范型：　procedural-based   object-based    object-oriented    generics

- 声明告诉编译器某个东西的名称和类型，定义提供编译器一些声明所遗漏的细节

- explicit禁止隐式类型转换，允许显示类型转换，遵循此策略

- copy构造函数，copy assignment操作符

  ```c++
  Widget w1;   //调用默认构造函数
  Widgt  w2(w1);　//调用copy构造函数
  W1=w2;　　　　　　//调用copy赋值构造函数
  Widgt w3=w2;    //调用copy构造函数　　　      
  ```

  如果一个新对象被定义，一定有个构造函数被调用，不可能调用赋值操作，如果没有新对象被定义，就不会有构造函数被调用，当然是赋值操作被调用.

- TR1

- Boost

## 第一章　让自己习惯C++

### 条款1 视C++为一个语言联邦

- C++是多重范型编程语言：过程形式、面向对象形式、函数形式、泛型形式、元编程形式
- C++的次语言:
  - C
  - Object-Oriented C++
  - Template C++　　　　　　　　　
  - STL,  迭代器和函数对象都是在C指针上塑造出来的
- C++是从四个次语言组成的联邦政府，每个次语言带有自己的规约
- C++高效编程守则视状况而变化，取决于使用C++的哪一部分

### 条款2 尽量以const enum inline 替换#define

- 宁可以编译器替换预处理器

- ＃define ASPECT_PATIO 1.653   记号名称ASPECT_PATIO可能没有进入记号表

- const double AspectRation=1.653;   会进入记号表，使用常量可能比使用#define导致较小量的码

- 由于常量定义式通常放在头文件内，有必要将指针声明为const

  ```c++
  const char* const authorName= "Scott Meyers";
  const std::string authorName("Scott Meyers");
  ```

- class的专属常量，应让它成为一个static成员

  ```c++
  class GamePlayers{
      private:
      static const int NumTurns=5;
      int scores[NumTurns]
  }
  //声明式，class的专属常量为static且为整数类型，只要不取它们的地址，就可以声明并使用它们而不必提供定义式，取地址时，提供定义式:   const int GamePlayers::NumTurns  放在实现文件中
  
  class CostEstimate{
      private:
      static const double FudgeFactor;
  };　　//常量声明，位于头文件
  const double CotsEstimate::FudgeFactor=1.35;  //static class 常量定义
  ```

- #define不能够用来定义class专属常量，不能封装

- 或者使用枚举类型代替

  ```c++
  class GamePlayer{
      private:
      enum {NumTurns=5};    //取一个enum的地址不合法
      int scores[NumTurns];
  }
  ```

- 优秀的编译器不会为整数型const对象设定另外的存储空间(除非创建pointer，reference), 不够优先的编译器可能会，enums和#define不会导致非必要的内存分配

- template inline 函数可以获得宏带来的效率以及一般函数的所有可预料行为和类型安全性

  ```c++
  template<typename T>
  inline void callWithMax(const T& a,const T& b)
  {
      f(a>b?a:b);
  }
  ```

- 有了consts enums 和inlines，预处理器的需要降低了，但#include仍然是必须的，#ifdef #ifndef也是必须的

- 对于单纯常量，最好以const对象或enums替换#defines

- 对于形似函数的宏,最好改用inline 函数替换#defines

## 条款3 尽可能使用const

- const

  ```c++
  char greeting []="Hello";
  char* p=greeting;    //non-const pointer, non-const data
  const char* p=gerrting; //non-const pointer, const data
  char* const p=greeting; //const pointer,non-const data
  const char* const p=greeting //const pointer,const data
  ```

- 如果const出现在*左边，表示被指物是常量，如果出现在星号右边，表示指针是常量

  ```c++
  void f1(const Widget* pw);
  void f2(Widget const * pw);  //两种形式相同
  ```

- STL迭代器的作用就像T*指针

  ```c++
  std::vector<int> vec;
  const std::vector<int>::iterator iter=vec.begin();   //想T* const
  *iter=10;
  std::vector<int>::const_iterator cIter=vec.begin();  //像const T*
  ++cIter;
  ```

- 函数的返回值设为const, 可避免(a*b)=c 这种赋值错误

- const成员函数，确认该成员函数可作用于const对象

  - 两个成员函数如果只是常量性不同，可以被重载

  - ```c++
    class TextBlock{
        public:
        const char& oprator[] (std::size_t position) const {  //用于const 对象
            return text[position];
        } 
        char& oprator[](std::size_t position){  //用于non-const对象
            return text[position];
        }
        private:
        	std::string text;
    }
    TextBlock tb("Hello");
    std::cout<<tb[0];   //调用non-const
    const TextBloc ctb("World");
    std::cout<<ctb[0];  //调用const
    ```

  - 如果函数的返回类型是个内置类型，那么改动函数返回值就不合法

  - bitwise constness和logical constness

    - mutable可解决，mutable释放掉non-static成员变量的bitwise constness约束
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-04 15-15-46.png)

- 在const和non-const成员函数中避免重复

  - 为了避免代码重复，即运用const operator[]  实现non-const版本，可使用casting

- 将某些东西声明为const可帮助编译器侦探出错误用法，对象、函数参数、函数返回类型、成员函数本体

- 编译器强制实施bitwise constness,但编写程序应使用概念上的常量性

- 当const和non-const成员函数有实质等价的实现时，令non-const版本调用const版本可避免代码重复

### 条款4　确定对象被使用前已先被初始化

- 对于无成员的内置类型，手动初始化

- 对于自定义类型，构造函数初始化

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-05 14-09-28.png)

- 上述非内置成员的初始化发生于这些成员的default构造函数被调用之时，比进入ABEntry构造函数本体的时间更早，内置类型不一定

- 构造函数的一个教佳写法是member initialization list替换赋值动作,效率更高

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-05 14-14-32.png)

  

- 总是在初值列中列出所有成员变量
- 对于有多个构造函数的，内置类型的成员变量最好改用赋值操作，并移往某个函数，供所有构造函数调用
- C++的成员初始化次序: base classes更早被初始化，class的成员变量以其声明次序被初始化

- 不同编译单元内定义之non-local static对象的初始化次序

  - 编译单元指产出单一目标文件的那些源码，即单一源码文件加上所含头文件

  - 函数内的static对象为local static对象，其他static对象为non-local static 对象，static对象在main()结束时自动销毁

  - 将每个non-local static对象搬到自己的专属函数内，对象被声明为static,函数返回一个reference指向它所含的对象，用户调用函数，而不直接用对象，即non-local static对象被local static对象代替了

    ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-05 14-41-04.png)

  - 任何一种non-const static对象无论在local或non-local，在多线程环境下等待某事发生都会有麻烦，解决办法是在程序的单线程启动阶段手工调用所有reference-returning函数

- 为内置型对象进行手工初始化

- 构造函数最好使用成员列表初始化，排序次序与声明次序应相同

- 为避免跨编译单元初始化次序问题，以local static对象替换non-loca static对象

## 第二章　构造/析构/赋值运算

### 条款5 了解C++默默编写并调用哪些函数

- 空类在编译器处理之后会自动生成构造函数,copy构造函数,析构函数,copy assignment操作符

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-05 14-51-36.png)

- 它们都是public且inline的，这些函数被调用才会被编译器创建出来
- 声明了构造函数后，编译器不再为它创建默认构造函数
- 对于内含reference成员的class，必须自己定义copy assignment操作符
- 对于内含const成员的classer,也必须自己定义，编译器将拒绝编译