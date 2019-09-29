



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



### 条款6 若不想使用编译器自动生成的函数，明确拒绝

- 不希望copy和copy assignment时，将成员函数声明为private且不实现它们　

- 为驳回编译器自动提供的机能，可将相应的成员函数声明为private且不予实现，或者继承一个Uncopyable 的base class ,可将链接期间的错误移到编译期

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-06 14-41-04.png)

  



### 条款7 为多态基类声明virtual 析构函数

- 当derived class对象经由一个base class指针被删除，而该base class 带着一个non-virtual析构函数，其结果未定义-实际执行的通常是对象的derived成分没被销毁，形参资源泄露问题
- 如果class 不含virtual 函数，通常表示它不意图被用作一个base class
- 每一个virtual函数的class都有一个相应的vtbl,当对象调用某一virtual函数，实际被调用的函数取决于该对象的vptr所指的vtbl
- 若class内含virtual函数，其对象的体积会增加，即多了一个vptr指针，32位机器中4个字节，64位机器中8个字节
- pure virtual 函数导致抽象classes,  为抽象基类定义pure virtual 析构函数
- 对于并非被设计用来经由base class接口处置derived class对象的，不需要virtual 析构函数
- 总结
  - 带多态性质的base classes应声明一个virtual 析构函数，如果class带有任何virtual函数，应拥有一个virtual析构函数
  - classes如果不是作为base classes使用，或不是为了具备多态性，就不应该声明virtual析构函数

### 条款8　别让异常逃离析构函数

- 析构函数吐出异常就是危险，总会带来过早结束程序、或发生不明确行为的风险
- 析构函数绝对不要吐出异常，如果一个析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下它们(不传播)或结束程序
- 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么class应该提供一个普通函数(而非在析构函数中)执行该操作

### 条款9 绝不在构造和析构过程中调用virtual函数

- 当pure virtual函数被调用，大多执行系统会终止程序(通常对结果发出一个信息)

- 在构造和析构期间不要调用virtual函数，因为这类调用从不下降至derived class

- derived class对象内的base class成分会在derived class自身成分被构造之前先构造妥当

- 正确使用方式如下

  ```c++
  class Transcation{
      public:
      explicit Transcation(const std::string& logInfo);
      void logTranscation(const std::string& logInfo) const;
  };
  Transcation::Transcation(const std::string& logInfo){
      logTranscation(logInfo);
  }
  class BuyTranscation: public Transcation{
      public:
      BuyTranscation(parameters):Transcation(createLogString(parameters))
      {}
      private:
      static std::string createLogString(parameters);
      //令此函数为static,则不可能意外指向初期未成熟的BuyTranscation对象内尚未初始化的成员变量
  };
  ```



### 条款10 令operator=返回一个reference to*this

- 赋值采用右结合律
  - x=y=z=15    x=(y=(z=15))
- 为了实现连锁赋值，赋值操作符必须返回一个reference指向操作符的左侧实参



### 条款11 在operator=中处理自我赋值

- 加上　if(this==&rhs) return *this    //具备自我赋值安全性，但可能不具备异常安全性

- 异常安全性

  ```c++
  Widget& Widget::operator=(const Widget& rhs){
      Bitmap* pOrig=pb;
      pb=new Bitmap(*rhs.pb);
      delete pOrig;
      return *this;
  }
  ```

  - copy and swap技术

### 条款12 复制对象时勿忘其每一个成分

- Copying函数应该确保复制"对象内的所有成员变量"及其所有base classs成分
- 不要尝试以某个copying函数实现另一个copying函数，应将共同机能放在第三个函数中，并由两个函数共同调用

## 第三章　资源管理

- 资源:内存、文件描述器、互斥锁、图形界面的字形和笔刷、数据库连接、网络sockets   不再使用它时，必须还给系统

### 条款13 以对象管理资源

- 把资源放进对象内，便可依赖C++的析构函数自动调用机制确保资源被释放
- auto_ptr是类指针对象，即智能指针，其析构函数自动对其所指对象调用delete
- 注意别让多个auto_ptr同时指向同一对象，**若通过copy或copy assignment操作符复制它们，它们会变成null,而复制所得的指针将取得资源的唯一拥有权**
- 引用计数型智慧指针RCSP,行为类似垃圾回收，tr1::shared_ptr是一个RCSP
- auto_ptr和tr1::shared_ptr两者都在其析构函数内做delete而不是delete [] 操作

### 条款14 在资源管理类中小心copying行为

- 禁止复制，将copying操作声明为private
- 对底层资源祭出引用计数法
  - tr1::shared_ptr允许指定删除器(是一个函数或函数对象)，当引用次数为0时被调用
  - class析构函数会自动调用non-static成员变量的析构函数
- 复制底部资源
  - **进行的是深度拷贝，如字符串对象内含一个指针指向一块heap内存，当这样一个字符串对象被复制，不论其指针或其所指内存都会被制作出一个复件**
- 转移底部资源的拥有权
  - auto_ptr

### 条款15 在资源管理类中提供对原始资源的访问

- 将RAII class对象(如tr1::shared_ptr)转换为其内含之原始资源(如Inverstment* )
  - tr1::shared_ptr和auto_ptr都提供一个get成员函数，用来执行显示转换，返回智能指针内部的原始指针(的复件)
  - 隐式转换: 重载了指针取值和操作符
  - 提供隐式转换函数
- 每一个RAII class应该提供一个取得其所管理之资源的办法
- 对原始资源的访问可能经由显示转换或隐式转换，一般而言显示转换比较安全，但隐式转换对客户比较方便



### 条款16 成对使用new和delete时要采取相同形式

### 条款17 以独立语句将newed对象置入智能指针

- 在资源被创建(经由　new Widget)和资源被转换为资源管理对象两个时间点之间有可能发生异常干扰

- **以独立语句将newed对象存储于智能指针内，如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄露**

- ```c++
  std::tr1::shared_ptr<Widget> pw(new Widget);  //在单独语句内以智能指针存储newed所得对象
  processWidget(pw,priority())　//不会导致资源泄露
  ```


## 第四章　设计与声明

### 条款18 让接口容易被正确使用、不易被误用

- 任何接口如果要求客户必须记得做某些事情，就是有着不正确使用的倾向，教佳接口的设计原则是先发制人

- tr1::shared_ptr提供的某个构造函数接受两个实参:一个是被管理的指针，另一个是引用次数为０时被调用的删除器　　std::tr1::shared_ptr<Investment> Pinv(static_cast<Investment*> (0),getrifofInvertment);

- cross-DLL problem问题，发生在对象在动态链接库(DLL)中被new创建，却在另一个DLL内被delete销毁，tr1::shared_ptr没有这个问题，因为它会追踪记录引用次数为0时该调用的那个DLL's delete

- ```c++
  std::tr1::shared_ptr<Investment> createInvestment(){
      std::tr1::shared_ptr<Investment> retVal(static_cast<Investment*>(0),getridofInvestment);
      retVal=...;
      return retVal;
  }
  ```

### 条款19 设计class犹如设计type

### 条款20 宁以pass-by-reference-to-const替换pass-by-value

- 缺省情况下C++函数参数都是以实际实参的复件为初值，而调用端所获得的是函数返回值的一个副件，这个复件由对象的copy构造函数产出
- 以by reference 方式传递参数也可以避免slicing问题，当一个derived class 对象以by value 方式传递并被视为一个base class 对象，base class的copy构造函数会被调用
- 解决切割问题的办法：　以by reference-to-const的方式传递
- references往往以指针实现出来
- 内置类型pass by value效率更高些
- pass-by-value并不昂贵的唯一对象是内置类型和STL的迭代器和函数对象



### 条款21 必须返回对象时，别妄想返回其reference

- 任何函数如果返回一个reference指向某个local对象，或返回指针指向某个local对象，将一败涂地
- 绝不要返回pointer或reference指向一个local stack对象，或返回reference指向一个heap-based对象，或返回pointer或reference指向一个local static对象

### 条款22 将成员变量声明为private

- 一旦将一个成员变量声明为public或protected而客户开始使用它，就很难改变那个成员变量所涉及的一切，太多代码需要重写、重新测试、重新编写文档、重新编译等。。。
- 从封装的角度看，其实只有两种访问权限private(提供封装)和其他(不提供封装)
- protected并不比public更具封装性

### 条款23 宁以non-member、non-friend替换member函数(更大的封装性)

- 面向对象守则要求数据尽可能被封装：使我们能改变事物而只影响优先客户
- 越多函数可以访问它，数据的封装性就越低
- 能够访问private成员变量的函数只有class的member函数和friend函数
- namespace可跨越多个源码文件，classes不能
- 将所有便利函数放在多个头文件但属于同一个命名空间
- derived classes无法访问base class中private成员

### 条款24 若所有参数都需要类型转换，为此采用non-member函数

- 如果你需要为某个函数的所有参数(包括被this指针所指的那个隐喻参数)进行类型转换，那么这个函数必须是个non-member

### 条款25 考虑写出一个不抛出异常的swap函数

- std::swap的典型实现

- 我们不能改变std命名空间内的任何东西，但我们可以为标准template制造特化版本,但不能添加新的templates

- 所有STL容器也都提供public swap 成员函数，和std::swap特化版本(用以调用前者)

- 函数模板

  - 函数模板只能全特化，不能偏特化，如果要偏特化的话只能重载

  - ```c++
    template< >                                  // 全特化　注意语法
    double add(double a, double b)  { return a + b; }
    
    int main()
    {
        int x = 10, y = 20;
        double z = 1.1, w = 2.2;
        std::cout << add(x, y) << std::endl;   // 调用普通版本
        std::cout << add(z, w) << std::endl;   // 调用全特化版本
        return 0;
    }
    ```

  - 如果有与实参更加匹配的特例化版本，编译器将会选择特例化版本

  - 函数模板重载（不存在偏特化）,因为偏特化版本本质上仍然是模板，所以如果需要的话，可以重载一个函数模板

  - ```c++
    template<class T1>　　// 重载版本，接收参数为指针
    T1 add(T1* a, T1* b) { return *a + *b; }   
    int main()
    {
        int a = 10, b = 20;
        int *x = &a, *y = &b;
        add(a, b);    // 调用普通模板
        add(x, y);　  // 调用重载的模板
        return 0;
    }
    ```

- 类模板

  - 类模板全特化比较好理解，跟函数模板一样，全特化是一个实例，当编译器匹配时会优先匹配参数一致的实例

  - ```c++
    template< >     　　　// 注意语法
    class A<char*>       // 一个全特化的模板类A
    {                    // 当用char*类型来实例化类模板A时，将会优先调用这个全特化实例
    public:
        explicit A(char* val) : t(val) { }
        char* add(char* a, char* b) { return strcat(a, b); }
    private:
        char* t;
    };
    ```

  - 类模板偏特化本质上都是指定部分类型，让偏特化版本称为普通版本的子集，若实例化时参数类型为指定的类型，则优先调用特例化版本

    - ```c++
      template<class T1, class T2>      // 普通版本，有两个模板参数
      class B { ..... };
      
      template<class T2>　　　         // 偏特化版本，指定其中一个参数，即指定了部分类型
      class B<int , T2> { ..... };　　// 当实例化时的第一个参数为int 则会优先调用这个版本
      ```

    - ```c++
      template<class T>     // 普通版本
      class B { ..... };
      
      template<class T>　　　//这个偏特化版本只接收指针类型的模板实参 
      class B<T*> { ..... }; 
      
      template<class T>
      class B<T&> { ..... };     // 这个偏特化版本只接受引用类型的模板实参
      ```

    - ```c++
      template<class T>    //普通版本
      class B { ..... };
      
      template<class T>　　　// 这种只接受用T实例化的vector的模板实参．也是一种偏特化
      class B<vector<T>> { ......  };  
      ```

- 高效的swaps几乎总是基于对内置类型的操作(例如pimpl手法的底层指针)，而内置类型上的操作绝不会抛出异常

- 总结

  - 当std::swap 对你的类型效率不高时，提供一个swap成员函数，并确定这个函数不抛出异常
  - 如果提供一个member swap,也应该提供一个non-member　swap用来调用前者，对于classes(而非templates),请特化std::swap
  - 调用swap时应针对std::swap 使用using声明，然后调用swap且不带修饰
  - 为用户定义类型进行std templates全特化是好的，然不要在std内进行模板重载

### 条款27 尽量少做转型动作

- ```c++
  class Base{};
  class Derived: public Base {};
  Derived d;
  Base* pb=&d;  //隐喻地将Derived*指针转化为Base*
  //这种情况下会有个偏移量在运行期施加于Derived* 指针身上，用于取得正确的Base* 指针值
  //单一对象可能拥有一个以上的地址(以Base* 指针指向它和以Derived* 指向它时的地址)
  ```

### 条款28 避免返回handles指向对象内部成分

- 返回一个handle代表对象内部成分总是危险的，无论这个handle是个指针或迭代器或reference,也无论这个handle是否为const,也无论那个返回handle的成员函数是否为const
- oprator[]s是例外

### 条款29 为异常安全而努力是值得的

- 异常安全条件
  - 不泄露任何资源，可通过资源管理类解决
  - 不允许数据破坏

- 异常安全函数提供三个保证之一
  - 基本承诺
  - 强烈保证
  - 不抛掷保证：绝不抛出异常

- copy and swap:  一般化的设计策略实现强烈保证，为你打算修改的对象(原件)做出一份副本，然后在副本身上做一切必要改变，若有任何修改动作抛出异常，原对象保持未改变的状态，待所有改变都成功后，再将修改过的副本和原对象在一个不抛出异常的操作中置换(swap)

- pimpl idiom手法:  将所有属于对象的数据从原对象放进另一个对象内，然后赋予原对象一个指针，指向那个所谓的实现对象(即副本)

- 如果一个系统内有一个函数不具备异常安全性，整个系统就不具备异常安全性

### 条款30 透彻了解inlining的里里外外

- 编译器最优化机制通常被设计用来浓缩那些不含函数调用的代码

- inline造成的代码膨胀会导致额外的换页行为，降低指令高速缓存装置的击中率

- 隐喻提出(在class中)，以及明确提出

- Inline函数通常一定被置于头文件内，在大多数C++程序中是编译期行为

- template通常也被置于头文件内，在编译期完成具现化动作

- 所有virtual函数的调用都会使inlining落空

- ```c++
  inline void f() {}
  void (*pf) ()=f;
  f(); //这个调用将被inlined,因为它是一个正常调用
  pf();　//这个调用或许不被inlined,因为它通过函数指针达成
  ```

- Derived构造函数会陆续调用其成员变量和base class两者的构造函数，而那些调用(它们自身也有可能被inlined)会影响编译器是否对此空白函数inlining

- 如果f是程序库内的一个inlining 函数，客户将f函数本体编进程序中，一旦程序设计者决定改变f,所有用到f的客户端程序都必须重新编译

- 如果f是non-inline函数，一旦它有任何修改，客户端只需重新链接就好，比重新编译负担少

- 许多编译环境在调试程序时，禁止发生inlining

- 平均而言一个程序将80%的执行时间花费在20%的代码上面

- 将大多数inlining限制在小型，被频繁调用的函数身上，这可使日后的调试过程和二进制升级更容易

### 条款31 将文件间的编译依存关系降至最低

- 编译器必须在编译期间知道对象的大小，询问class定义式
- pimpl idiom   实现接口与实现分离
- 如果使用object references或pointers可以完成任务，就不要使用objects.   可以只靠一个类型声明式就定义出指向该类型的reference和pointers,但如果定义某类型的objects,就需要用到该类型的定义式
- 尽量以class声明式替换class定义式
- 为声明式和定义式提供不同的头文件
- Handle classes
- 抽象基类（作为接口class），通常不带成员变量，只有一个虚析构函数一组pure virtual 函数
- Handle classes和Interface classes解除了接口和实现之间的耦合关系，从而降低文件间的编译依存性
  - Handle classes身上，成员函数必须通过implementation pointer取得对象数据，implementation pointer必须被初始化
  - 至于Interface classes,由于每个函数都是virtual,必须付出额外的代价



## 第六章　继承与面向对象设计

### 条款32 确定你的public 继承塑模出is-a关系

- 公开继承意味着  is-a 的关系
- 适用于base classes身上的每一件事情一定也适用于derived classes身上，因为每一个derived class对象也都是一个base class对象

### 条款33 避免遮掩继承而来的名称

- derived class作用域被嵌套在base class作用域内
- ![](/home/leiwang/Markdown/C++/picture/Screenshot%20from%202019-09-23%2017-10-33.png)
- ![](/home/leiwang/Markdown/C++/picture/Screenshot%20from%202019-09-23%2017-16-09.png)
- derived classes内的名称会遮掩base classes内的名称
- 为了让被遮掩的名称再见天日，可使用using 声明式或转交函数



### 条款34 区分接口继承和实现继承

- 声明一个pure virtual 函数的目的是为了让derived classes只继承函数接口
- 声明impure virtual函数的目的是为了让derived classes继承该函数的接口和缺省实现
- pure virtual函数必须在derived classes中重新声明，但它们也可以拥有自己的实现
- 声明non-virtual函数的目的是为了令derived calsses继承函数的接口及一份强制性实现
- 总结
  - **pure virtual函数只具体指定接口继承**
  - **impure virtual函数具体指定接口继承及缺省实现继承**
  - **non-virtual函数具体指定接口继承以及强制性实现继承**

### 条款35  考虑virtual函数以外的选择

#### 借由non-virtual interface手法实现Template Method模式

- 通过public non-virtual成员函数间接调用private virtual函数

#### 借由Function Pointers实现Strategy模式

#### 借由tr1::function 完成Strategy模式

- std::tr1::function<int (const GameCharacter &)>  指向函数的泛化指针

#### 古典的Strategy模式

- virtual函数的替代方案包括NVI手法及Strategy设计模式的多种形式
- tr1::function对象的行为就像一般函数指针



### 条款36 绝不重新定义继承而来的non-virtual函数

- 静态绑定
  - 由于PB被声明为一个pointer-to-B,通过PB调用的non-virtual函数永远是B定义的版本，即使PB指向一个类型为B派生之class的对象
- 动态绑定
  - 虚函数是动态绑定的

### 条款37 绝不重新定义继承而来的缺省参数值

- 缺省参数值是静态绑定

- 对象的所谓静态类型，就是它在程序中被声明时所采用的类型

  ```c++
  Shape* ps;   
  Shape* pc=new Circle;
  Shape* pr=new Rectangle;
  //ps和pc和pr的静态类型都是Shape*
  ```

- 对象所谓的动态类型，就是目前所指对象的类型

  - pc的动态类型是Circle*   pr的动态类型是Rectangle*,ps没有动态类型
  - **Virtual函数系动态绑定而来，调用一个virtual函数时，取决于发出调用的那个对象的动态类型**

- virtual函数是动态绑定的，而缺省参数值是静态绑定的，可能会在调用一个定义于derived class内的virtual函数的同时，却使用base class为它指定的缺省参数值

### 条款38 通过复合塑模出has-a或根据某物实现出

- set的实现往往招致每个元素耗用三个指针的额外开销，因为sets通常以平衡二叉树实现而成
- 实现sets的方法太多了，其中一种便是在底层采用linked lists
- Set对象可根据一个list对象实现出来，是has-a的关系



### 条款39 明智而审慎地使用private继承

- private继承
  - 如果classes之间的继承关系是private,编译器不会自动将一个derived class对象转换为一个base class对象
  - 由private base class继承而来的所有成员，在derived class中都会变成private属性
  - **private继承意味着根据某物实现出**
- 尽可能使用复合，必要时才使用private继承，主要是当protected成员或virtual函数牵扯进来时，当一个意欲成为derived class者想访问一个意欲成为base class的protected成分，或为了重新定义一或多个virtual函数，但这时候两个classes之间的概念关系是根据某物实现
- public继承加复合　　　private继承
- C++裁定凡是独立(非附属)对象都必须有非零大小，这个约束不适用于derived class对象内的base class成分
- 空白基类最优化，只在单一继承下才可行，private继承可以造成empty base 最优化



### 条款40 明智而审慎地使用多重继承

- virtual base class
  - 非必要不要使用virtual bases
  - 如果必须使用，尽可能避免在其中放置数据，就不需要担心这些classes身上的初始化和赋值带来的诡异事情
- 多重继承比单一继承复杂，它可能导致新的歧义性，以及对virtual继承的需要
- virtual继承会增加大小、速度、初始化(及赋值)复杂度等等成本，如果virtual base classes不带任何数据，将是最具实用价值的情况
- 多重继承的确有正当用途，其中一个情节涉及 public继承某个Interface class和private继承某个协助实现的class的两相组合



## 第七章　模板与泛型编程

### 条款41 了解隐式接口和编译期多态

- 面向对象总是以显式接口和运行期多态解决问题
- 隐式接口和编译期多态在Templates及泛型编程的世界更常见
  - 由template中的T决定支持哪一种接口
  - 以不同的template参数具现化function templates会导致调用不同的函数，这就是编译期多态
- classes和templates都支持接口和多态
- 对classes而言接口是显式的，以函数签名为中心，多态则是通过virtual函数发生于运行期
- 对templates参数而言，接口是隐式的，基于有效表达式。多态则是通过template具现化和函数重载解析符发生于编译期

### 条款42 了解typename的双重含义

- 当我们声明template类型参数，class和typename的意义完全相同
- template内出现的名称如果相依与某个template参数，称之为从属名称，如果从属名称在class内呈嵌套状，称为**嵌套从属名称**
- 非从属名称
- 如果解析器在template中遭遇一个嵌套从属名称，它便假设这名称不是个类型，除非你告诉它是，所以缺省情况下嵌套从属名称不是类型
- typename C::const_iterator  iter(container.begin())
- typedef typename std::iterator_traits\<IterT>::value_type  value_type;
- 请使用关键字typename 标识嵌套从属类型名称，但不得在base class lists或member initialization list内以它作为base class修饰符



### 条款43 学习处理模板化基类内的名称

- C++往往拒绝在templatized base class(模板化基类)内寻找继承而来的名称
  - 解决办法1  在base class函数调用动作之前加上this->
  - 使用using 声明式
  - 明确指出被调用的函数处于base class内
- 模板化基类内的函数名称会被derived classes遮盖

### 条款44 将与参数无关的代码抽离templates

- 必须训练自己去感受当template被具现化多次时可能发生的重复
- 由非类型模板参数可能带来代码膨胀，类型参数也可能带来膨胀
- 总结
  - Templates生成多个classes和多个函数，所有任何template代码都不应该与某个造成代码膨胀的template参数产生相依关系
  - 因非类型模板参数而造成的代码膨胀，往往可以消除，做法是以函数参数或class成员变量替换template参数
  - 因类型参数而造成的代码膨胀，往往可降低，做法是让带有完全相同二进制表述的具现类型共享实现代码



### 条款45 运用成员函数模板接受所有兼容类型

- 智能指针: 行为像指针的对象
- 真实指针支持:
  - derived class指针可以隐式转换为base class指针
  - 指向non-const对象的指针可以转换为指向const对象
- 如果以带有base-derived 关系的B,D类型分别具现化某个template, 产生出来的两个具现体并不带有base-derived关系
- member function template
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-27 10-51-29.png)

- 有了一个泛化构造函数，这个构造函数只在其所获得的实参适当兼容类型时才通过编译
- 总结
  - 请使用member function templates生成可接受所有兼容类型的函数
  - 如果你声明member templates用于泛化copy构造或泛化assignment操作，还是需要声明正常的copy构造函数和copy assignment操作符

### 条款46 需要类型转换时请为模板定义非成员函数

- 必须先为相关的function template推导出参数类型，然后才可将适当的函数具现化出来
- 在template实参推导过程中从不将隐式类型转换函数纳入考虑
- class template并不依赖于template实参推导
- 当我们编写一个class template,而它所提供之与此template相关的函数支持所有参数之隐式类型转换时，请将那些函数定义为class template内部的friend函数



### 条款47 请使用traits classes表现类型信息

- traits 允许在编译期间取得某些类型信息
- traits必须能够施行于内置类型，因此类型的traits信息必须位于类型自身之外，标准技术是放在一个template或其特化版本中
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-27 11-29-59.png)

- 编译期核定比运行期核定更好
- 重载可以实现编译期核定
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-27 11-34-24.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-27 13-12-39.png)

- 如何使用traits class
  - 建立一组重载函数(劳工)或函数模板，彼此间的差异只在于各自的traits参数。令每个函数实现码与其接受之traits信息相应和
  - 建立一个控制函数(工头)或函数模板，它调用上述那些劳工函数，并传递traits class所提供的信息
- TR1一共为标准C++添加了50个以上的traits classes
- traits class使得类型相关信息在编译期可用，它们以templatesh和templates 特化完成实现
- 整合重载技术后，traits class有可能在编译期对类型执行if...else测试

### 条款48 认识template元编程

- template metaprogramming(TMP,模板元编程)是编写template-based C++程序并执行于编译期的过程
- 让事情更容易
- 将工作从运行期转移到编译期
- 编译时间变长了
- 编译器必须确保所有源码都有效，纵使是不会执行起来的代码
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-27 13-30-47.png)
- TMP可将工作由运行期移往编译期，因而得以实现早期错误侦测和更高的执行效率
- TMP可被用来生成基于政策选择组合的客户定制代码，也可用来避免生成对某些特殊类型并不适合的代码



## 第八章　定制new和delete

### 条款49 了解new-handler的行为

- 当operator new抛出异常以反映一个未获得满足的内存需求之前，它会调用new-handler,使用set_new_handler

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-28 11-20-42.png)

- 末端的throw()是异常明细，表明该函数不抛出任何异常

- set_new_handler的参数指向operator new无法分配足够内存时该被调用的函数，返回指向set_new_handler被调用前正在执行的那个new_handler函数

- 当operator new 无法满足内存申请时，它会不断调用new-handler函数，直到找到足够内存

- 一个new-hadler函数必须做以下事情

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-28 11-22-38.png)

- 实现class专属之new-handlers

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 10-27-30.png)

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 10-27-55.png)

- 将global new-handler视为资源，并运用资源管理对象
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 10-35-57.png)

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-28 11-31-17.png)

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 10-38-26.png)

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 10-39-25.png)

- 继承自NewhandlerSupport的每一个class,拥有实体互异的NewHandlerSupport复件(更准确的说是其static 成员变量currentHadnler),Template机制会为每一个T生成一个currentHandler
- Notrhrow new是一个颇为局限的工具，因为它只适用于内存分配，后继的构造函数调用还是可能抛出异常



### 条款50 了解new和delete的合理替换时机

- 用来检测运用上的错误
- 为了强化效能，编译器自带的operator news 和delete比较中庸
- 为了收集使用上的统计数据
- 为了增加分配和归还的速度
- 为了降低缺省内存管理器带来的空间额外开销
- 为了弥补缺省分配器中的非最佳对齐
- 为了将相关对象成簇集中
- 为了获得非传统的行为
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 10-52-45.png)
- C++要求所有operator news返回的指针都有适当的对齐
- 有许多的理由要写自定的new和delete,包括改善性能，对heap运用错误进行调试、收集heap使用信息



### 条款51 编写new和delete时需要固守常规

- 只有当指向new-handling函数的指针是null, operator new才会抛出异常
- C++规定，即使客户要求0 Bytes,operator new也得返回一个合法指针
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 11-03-53.png)

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 11-04-13.png)
- 有可能base class的operator new被调用用以分配derived class对象，这时令标准的operator new 处理
- C++保证删除null指针永远安全
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 11-11-34.png)
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-28 11-40-02.png)

### 条款52 写了placement new也要写palcement delete

- Widget* pw=new Widget      new函数被调用，默认构造函数也被调用

- 如果operator new接受的参数除了一定会有的那个size_t之外还有其他，这便是个所谓的placement new

- void* operator new(std::size_t ,void* pMemory) throw();          placement new

- placement delete 只有在伴随placement new调用而触发的构造函数出现异常时才会被调用

- 在有palcement new时，也必须提供一个正常版的operator delete(用于构造期间无任何异常被抛出)

- 小心避免让class专属的news掩盖客户期望的其他news

- 缺省情况下，C++在global作用域提供以下形式的operator new:

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 11-25-16.png)

- 当你写一个placement operator new，请确定也写出对应的placement operator delete,如果不这么做，可能会发生内存泄露
- 当你声明palcement new和placement delete,请确定不要无意识地遮盖了它们的正常版本



## 第九章　杂项讨论

### 条款53 不要轻忽编译器的警告

- 严肃对待编译器发出的警告信息，努力在你的编译器的最高警告级别下争取无任何警告
- 不同的编译器发出的警告信息可能不同



### 条款54 让自己熟悉包括TR1在内的标准程序库

- TR1代表　Techinical Report 1
- C++98列入的C++标准程序库
  - STL(标准模板库)
  - Iostreams
  - 国际化支持
  - 数值处理，包括复数模板和纯数值数组
  - 异常阶层体系
  - C89标准程序库
- TR1详细叙述了14个新组件，通通放在std命令空间内
  - 指针指针　tr1::shared_ptr  和tr1::weak_ptr, tr1::shared_ptr会记录有多少个tr1::shared_ptr共同指向同一对象
  - tr1::function ` void registerCallback(std::tr1::function<std::string (int)> func);`
  - tr1::bind    能够做绑定器
  - Hash tables   tr1::unordered_set  tr1::unordered_multiset  tr1::unordered_map,  tr1::unordered_multimap
  - 正则表达式
  - Tuples(变量组)　　pair只能持有两个对象，tr1::tuple可持有任意个数的对象
  - tr1::array       大小固定，并不使用动态内存
  - tr1::mem_fn这是个语句构造上与成员函数指针一致的东西
  - tr1::reference_wrapper 一个让reference的行为更像对象的设施
  - 随机数工具
  - 数学特殊函数
  - C99兼容扩充
  - Type traits,一组traits class,用以提供类型的编译期信息
  - tr1::result_of,这是个模板，用来推导函数调用的返回类型
- TR1的14个组件中的10个奠基于免费的Boost程序库
- 所有Boost组件都位于命令空间boost内,TR1组件都位于std::tr1
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 13-32-19.png)

### 条例55 让自己熟悉Boost

- Boost是一个C++开发者集结的社群，也是一个可自由下载的C++程序库群，网址是http://boost.org

- Boost程序库的主题:

  - 字符串和文本处理

  - 容器

  - 函数对象和高级编程，如lambda

    ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-29 13-41-04.png)

  - 泛型编程，覆盖一大组traits class
  - 模板元编程TMP
  - 数学和数值
  - 正确性与测试
  - 数据结构
  - 语言间的支持性
  - 内存
  - 杂项

