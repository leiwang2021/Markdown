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

## 第二章　构造函数语意学

- conversion运算符的引入

### 2.1 Default Constructor 的构造操作

- 当编译器需要它的时候会合成出一个defailt constructor

- 带有Default Constructor 的Member class object

  - 当一个class没有任何constructor,但内含一个member object,而后者有default constructor，那么这个class的implicit default constructor 就是有用的

  - 编译器避免合成多个default constructor:把合成的构造器都以inline方式完成，一个inline有静态链接，不会被文件以外看到，若太复杂，则合成一个explictit non-inline static实例

    ```c++
    class FOO{
        public: 
        FOO();
        FOO(int);
        ..
    };
    class Bar{
        public:
        FOO foo;
        char* str;
    };
    
    Bar bar; //Bar::foo在此初始化
    //合成的默认构造器的函数如下:
    inline Bar::Bar(){
        foo.FOO::FOO()  //调用FOO的构造器
    }
    ```

    - 如果class A内含一个或以上的member class objects,那么class A的每一个构造器否必须调用member classes的默认构造器，编译器会扩张已存在的构造器，这些代码安排在explicit user code之前

- 带有Default Constructor的Base class

- 带有一个Virtual Funtion的Class

  - 合成出default constructor,为每一个class object的vptr设定初值，放置适当的virtual table地址
    - class声明(或继承)一个虚函数
    - class派生自一个继承串链，其中有一个或更多的virtual base classes
    - 对于virtual函数，具体调用哪个版本的函数取决于指针所指向对象类型。
    - 对于非virtual函数，具体调用哪个版本的函数取决于指针本身的类型，而和指针所指对象类型无关。
    - const 修饰的参数引用的对象，只能访问该对象的const函数，因为调用其他函数有可能会修改该对象的成员，编译器为了避免该类事情发生，会认为调用非const函数是错误的。

- 带有一个virtual base class的class

  - virtual base class的实现法在不同的编译器之间有极大的差异
  - cfront的做法是靠在derived class object的每一个virtual base classes中安插一个指针完成

- 总结

  - 4种情况下，编译器会为未声明constructor的classes合成一个default constructor
    - 调用member object
    - base class的默认构造器
    - 为每一个object初始化其virtual funtion机制
    - virtual base class 机制
  - 其他情况下不会合成出来，在合成的默认构造器中，只有base class subobjects和member class objects会被初始化，所有其他的nonstatic data member都不会被初始化

### 2.2 Copy Constructor的构造操作

- 三种情况下，会将一个object的内容作为另一个class object的初值

  - 显示地以一个object的内容作为另一个class object的内容
  - 隐式地初始化操作，作为函数的参数传递
  - 当函数传回一个class object时

- Bitwise Copy Semantics(位依次拷贝)

  - 当class object以相同class的另一个object为初值，内部是以default memberwise initialization手法完成的，即把每一个内建的或派生的data member的值，拷贝，不会拷贝member class object,以递归的方式施行memberwise initializaton

  - 展现出bitwise copy semanticas时，不会合成一个default copy constructor

    ```c++
    class Word{
        public:
        Word(const char*);
        ~Word(){delete [] str}
        private:
        	int cnt;
        	char* str;
    };
    //str会出问题，必须由设计者实现一个explicit copy constructor以改写default memberwise initialization
    ```

  - 编译器必须合成一个copy constructor.以便调用member class object的copy constructor

    ```c++
    class String{
        public:
        String(const char*);
        String(const String&);
        ~String();
    };
    class Word{
        public:
        Word(const String&);
        ~Word();
        private:
        int cnt;
        String str;
    };
    //String声明了一个explicit copy constructor,编译器必须合成一个copy constructor.以便调用member class object的copy constructor
    inline Word::Word(const Word& wd){
        str.String::String(wd.str);
        cnt=wd.cnt;
    }  //合成出来的
    ```

- 不展现出bitwise copy semantics的4种情况

  - 当class内含一个member object,而后者的class声明了一个copy constructor时(不论是被显示地声明，还是被编译器合成的)
  - 当class继承自一个base class，而后者存在一个copy constructor时(不论是被显示地声明还是被合成)
  - 当class声明了一个或多个virtual funtion时
  - 当class派生自一个继承串链，其中有一个或多个virtual base classes时

- 重新设定Virtual Table的指针

  - 当class有virtual函数时，编译器导入一个vptr到class之中时，该class就不再展现bitwise semantics了，编译器需要合成一个copy constructor以求将vptr适当地初始化
  - 当一个base class object以其derived class的object内容做初始化操作时，其vptr复制操作也必须保证安全
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-07 10-31-07.png)

   

- 处理virtual base class subobject

  - 一个virtual base class的存在会使bitwise copy semantics 无效

  - 编译器必须显示地将virtual base class pointer初始化

  - 在多重继承(multiple inheritance)中, 可能出现多个基类继承自同一个基类, 即"菱形继承", 会导致最顶层的基类, 被复制多次;

    可以采用虚继承(virtual inheritance)的方式, 使派生类(derived class)只保留最顶层基类的一个副本.

    virtual, 即需要vptr(virtual table pointer), 即虚表指针, 额外占用4个字节;




### 2.3 程序转化语意学

- 显示的初始化操作

  ```c++
  X x0;
  void foo(){
      X x1(x0);
      X x2=x0;
      X x3=X(x0);
  }
  //转化为以下形式，定义被重写，copy constrctuor调用操作被安插
  void foo(){
      //定义被重写，初始化操作被剥离
      X x1;
      X x2;
      X x3;
      
      x1.X::X(x0);
      x2.X::X(x0);
      x3.X::X(x0);
      
  }
  ```

- 参数的初始化

  ```c++
  void foo(X x0);
  X xx;
  foo(xx)  //会导入临时性object,并调用copy constructor将它初始化，并将临时性对象交给函数
  ```

- 返回值的初始化

  ```c++
  X bar(){
      X xx;
      return xx;
  }
  //返回值如何从局部对象xx中拷贝过来?
  //双阶段转化，如下:
  void bar(X& _result){
      X xx;
      xx.X::X();
      _result.X::X(xx);
      return;
  }
  ```

- 在使用者层面做优化

- 在编译器层面做优化

  - NRV优化

- Copy Constructor要还是不要

  - memcpy()和memset()只有在classes不含任何由编译器产生的内部members时才能有效运行

- copy constructor的应用，迫使编译器对程序代码做部分优化，尤其是当一个函数以值的方式传回一个class object，而该class有一个copy constructor时，这将导致程序的转化



### 2.4 成员们的初始化队伍

- member initialization list
  - list中的初始化顺序是由class中的members声明顺序决定的　
  - initialization list的项目被放在explicit user code之前
  - base class和virtual base class在member initialization list中的初始化程序
  - 编译器会对initialization list一一处理并可能重新排序，以反映出members的声明顺序，它会安插一些代码到constructor体内，并置于explicit user code之前



## 第三章　Data语意学

- class X{  };  sizeof X的结果为1,有一个隐藏的1字节大小，被编译器安插进去的一个char,使得这个class的两个object得以在内存中配置独一无二的大小

- ```c++
  class X{};       //1　　1
  class Y: public virtual X {};   //８  4 
  class Z: public virtual X {};   //８  4
  class A: public Y,public Z {};  //12  8
  ```

- Y和Z的大小受到三个因素的影响

  - virtual base class导致的某种形式的指针
  - empty class 导致的1bytes
  - Alignment的限制,　将数值调到某数的整数倍

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-10 14-01-51.png)  

- 另一种编译器的处理

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-10 14-05-10.png)  

  

- 一个virtual base class subobject只会在derived class中存在一份实例，不管它在class继承体系中出现了多少次
- static data members永远只存在一份实例，甚至该class没有任何object实例，其static data members也已存在，但是template class的static data members不同
- class object大小的原因
  - 由编译器自动加上的额外的data members,用以支持某些语言特性
  - 因为alignment(边界调整)的需要

### 3.1 Data Member的绑定

- **extern**可以置于变量或者函数前，以标示变量或者函数的定义在别的文件中，提示编译器遇到此变量和函数时在其他模块中寻找其定义。此外extern也可用来进行**链接指定**。

- 在一个inline　member funtion内的一个data member绑定操作，会在整个class声明完成之后才发生，但是对于member funtion的argument list不为真，argument list中的名称还是会在它们第一次遭遇时被适当地决议

- **把nested type声明放在class的起始处，如果把nested typedef定义于在class中被参考之前，就可以确保非直觉绑定的正确性**

  ```c++
   //错误的方式
   typedef int length;
   
   class Point3d{
       public:
           void mumble(length val){_val=val;}　　　//length被决议为global
           length mumble(){return _val;}
       private:
           typedef float length; //这样的声明将使之前的参考操作不合法
           length _val;
   };
   //正确的方式
    typedef int length;
   
   class Point3d{
       public:
           typedef float length;
           void mumble(length val){_val=val;}
           length mumble(){return _val;}
       private:
           length _val;
   };
  ```

  - 一个inline函数实体，在整个class声明未被完全看见之前，是不会被评估求值的，一个inline memberfuntion 内的一个data member 绑定操作，会在整个class声明完成之后发生



### 3.2 Data Member的布局

- members的排列只需要符合较晚出现的members在class object中有较高的地址这一条件即可，members的边界调整可能需要一些bytes
- 任何中间介入的static data member都不会被放进对象布局之中
- 目前各家编译器都是把一个以上的access section连锁在一起，依照声明的顺序，成为一个连续区块

### 3.3 Data  Member的存取

- static Data members只有一个实例，存放在程序的data segment之中，其实不在class object之中，因此存取static members并不需要通过class object

- 对于复杂继承关系而来的static member,还是只有一个实例，其存取路径仍然直接

- 若取一个static data member的地址，会得到一个指向其数据类型的指针，而不是一个指向其class member的指针

- 如果两个classes,每一个都声明了一个static member freeList,它们放在程序的data segment时，会导致名称冲突，编译器的解决方法是暗中对每一个static data member编码

- Nonstatic Data Members

  - 在一个member function中直接处理一个nonstatic data member,所谓的implicit class object对象就会发生，即this->x  

  - 对一个nonstatic data member进行存取操作，编译器需要把class object的起始地址加上data member的偏移位置

  - 每一个nonstatic data member的偏移位置在编译时期就可获得，即使member属于base class subobject也一样，存取效率相同

  - ```c++
    Point3d origin;
    origin.x=0;
    Point3d *pt=&origin;
    pt->x=0;
    ```

  - 从origin存取和从pt存取的差异?  当Point3d是一个derived class,而其继承体系结构中有一个virtual base class,并且被存取的member是一个从该virtual base class继承而来的member时，不知道pt指向哪一种class type,也就不知道编译时期这个member真正的偏移位置，所以这个存取操作必须延迟到执行期，但如果使用origin,类型确定，members的偏移位置在编译时期就固定了


### 3.4 继承与Data Member

- 在大部分编译器上头，base class members总是先出现，但属于virtual base class的除外

- 单一继承不含虚函数、单一继承含虚函数、多重继承、虚拟继承

- 只要继承不要多态(单一继承且没有虚函数)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 19-12-49.png)

  - 出现在derived class中的base class subobject有其完整原样性

    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 19-18-24.png)

    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 19-18-58.png)

    - 现在Concrete3的object大小是16bytes,　Concrete2的大小是12bytes
    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 19-20-41.png)

    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 19-26-46.png)

- 加上多态(单一继承并含有虚函数的情况)
  - 有的编译器把vptr放在class object的尾端，可以保留base class C struct的对象布局，某些编译器把vptr放在class object的前端，有一些好处，代价是丧失了C语言从一个C　struct派生出一个具有多态性质的class的语言兼容性
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 19-42-57.png)

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 19-43-21.png)

  -  父类对象和子类对象分别有vptr指针，指向虚函数表，表中存储函数入口地址

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 20-18-48.png)

  - 1.普通继承+父类无virtual函数 

     若子类没有新定义virtual函数 此时子类的布局是 :

    ​                         由低地址->高地址 为父类的元素(没有vptr),子类的元素(没有vptr).

       若子类有新定义virtual函数 此时子类的布局是 :

    ​                         由低地址->高地址 为父类的元素(没有vptr),子类的元素(包含vptr,指向vtable.)

    2. 普通继承+父类有virtual函数
             不管子类没有新定义virtual函数 此时子类的布局是 : 由低地址->高地址 为父类的元素(包含vptr), 子类的元素.
             如果子类有新定义的virtual函数,那么**在父类的vptr**(也就是第一个vptr)对应的vtable中**添加**一个函数指针.
    3. virtual继承
          若子类没有新定义virtual函数 此时子类的布局是 :

    ​         由低地址->高地址 子类的元素(有vptr),虚基类的元素.为什么这里会出现vptr,因为虚基类派生出来的类中,虚类的对象不在固定位置(猜测应该是在内存的尾部),需要一个中介才能访问虚类的对象.所以虽然没有virtual函数,子类也需要有一个vptr,对应的vtable中需要有一项指向虚基类.
    ​         若子类有新定义virtual函数 此时子类的布局是与没有定义新virtual函数内存布局一致.但是在vtable中会多出新增的虚函数的指针.

    　4.多重继承
        此时子类的布局是 :

    ​                  由低地址->高地址 为父类p1的元素(p1按照实际情况确定元素中是否包含vptr), 父类p2的元素(p2按照实际情况确定元素中是否包含vptr),子类的元素.
       如果所有父类都没有vptr,那么如果子类定义了新的virtual function,那么子类的元素中会有vptr,对应的vtable会有相应的函数指针.
      如果有的父类存在vptr.如果子类定义了新的virtual function,会生成一个子类的vtable，这个子类的vtable是，在它的父类的vtable中后添加这个新的虚函数指针生成的.因为子类分配的空间显示并没有新增加一个4字节的指针空间，其实不管子类增加了多少新的虚函数，其空间大小不变，因为其和虚函数相关的分配的空间就是一个vptr，是一个指针，也就是4字节，不变，要变是变在vtable.

  - struct和class的区别

    - ![](/home/leiwang/Markdown/C++/picture/20181122191431245.png)

    - 在C++中引入struct是为了保持对C程序的兼容，在引入之后C++对其进行了扩充，现在struct可以拥有静态成员、成员数据可进行初始化、拥有函数、也可以继承、甚至多态也支持。从表面看起来两者之间像是没有区别，有时你把程序中的所有class改为struct，程序也照常运行。之所以说是看起来呢，两者之间肯定还是有差别
    - struct默认防控属性是public的，而class默认的防控属性是private的
    - 在继承关系，struct默认是public的，而class是private
    - **默认的防控属性取决于子类而不是基类**

- 多重继承

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 20-34-16.png)

- 虚拟继承

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 20-39-47.png)

  - Class如果内含一个或多个virtual base class subobjects,将被切割为两部分：一个不变区域和一个共享区域，不变区域中的数据总拥有固定的offset,可变直接存取，共享区域，表现出来的是virtual base class subobjects，位置因每次派生操作而变化。只能被间接存取

  - 多种布局，如下

    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 20-55-35.png)

    - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-12 20-56-13.png)

  - 经由一个非多态的class object来存取一个继承而来的virtual base class的member,可以被优化为一个直接存取操作，就好像一个经由对象调用的virtual funtion调用操作，可以在编译时期被决议完成一样。一般而言，virtual base class最有效的一种运用形式就是:一个抽象的virtual base class,没有任何data member。