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

### 3.5 对象成员的效率

- 若关心程序效率，应该实际测试
- 间接性压抑了把所有运算都移往寄存器执行的优化能力



### 3.6 指向data members的指针

- 所有编译器不是把vptr放在对象的头就是放在对象的尾

- & Point3d::z 将得到z在class object中的偏移位置(offset)

- ```c++
  float Point3d::*p1=0;
  float Point3d::*p2=&Point3d::x;
  //为了区分p1和p2，每一个真正的member offset值都被加上１
  ```

- 取一个正在绑定于class object的data member的地址，将会得到该member在内存中的真正地址

- 虚拟继承带来的冲击：　每一层虚拟继承都导入了一个额外层次的间接性

## 第四章　Function语意学

- 三种类型的member funtions: static nonstatic   virtual

### 4.1 Member的各种调用方式

- 非静态成员函数

  - 编译器内部已将member函数实体转换为对等的nonmember函数实体,转化步骤
    - 改写函数原型，安插额外参数this
    - 将每一个对nonstatic data member的存取操作改为经由this指针来存取
    - 将成员函数重新写成一个外部函数
  - 名称的特殊处理
    - member的名称前面会被加上class名称，形成独一无二的命名
    - 两个实体如果拥有独一无二的name mangling, 那么任何不正确的调用操作在链接时期就因无法决议而失败
- 虚拟成员函数

  - vptr
- 静态成员函数
  - 由于static member funtion 没有this 指针，其地址的类似并不是一个指向class member funtion的指针，而是一个nonmember函数指针

### 4.2 虚拟成员函数

#### 单一继承

- 在C++中，多态表示以一个public base class的指针(或reference),寻址出一个derived class object的意思

- RTTI, 有了RTTI,就能在执行期查询一个多态的pointer或多态的reference了，欲鉴定出哪些classes展现出多态特性，需要额外的执行期信息，只要一个class含有virtual funtion,它就需要这份额外的执行信息

- vitual funtions 可以在编译期获知，地址是固定不变的，执行期不可能新增或替换

- 一个class只会有一个virtual table

  - 这一class所定义的函数实例
  - 继承自base class的函数实例
  - 一个pure_virtual_called()函数实例，可以当作执行期异常处理函数

- ```c++
  ptr->z();
  (*ptr->vptr[4])(ptr)  //经由ptr可以存取该对象的virtual table,每一个z()函数地址都被放在slot4中
  ```

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-17 15-02-51.png)

#### 多重继承下的virtual funtions

- 在多重继承之下，一个derived class内含n-1个额外的virtual table,针对每一个virtual table,Derived 对象中有对应的vptr
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-17 15-19-52.png)

  

#### 虚拟继承下的virtual funtions

- 不要在一个virtual base class中声明nonstatic data members
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-17 15-33-42.png)

### 4.3 函数的效能

- inline函数不只能够节省一般函数调用带来的额外负担，也提供了程序优化的额外机会



### 4.4 指向Member funtion的指针

- 对于一个nonstatic member function取其地址，将获得该函数在内存中的地址，对一个virtual funtion,其地址在编译时期是未知的，所能获得的是virtual table中的索引值
- 如何识别函数指针值是内存地址还是virtual table索引?
- 一个指向member function 的指针是一个结构，内含三个字段: index, faddr,delta



### 4.5 Inline functions

- 在inline扩展期间，每一个形式参数都会被对应的实际参数取代，面对会带来副作用的实际参数，通常需要引入临时性对象
- inline函数中的局部变量，再加上有副作用的参数，可能会导致大量临时性对象的产生
- 如果一个inline函数被调用太多次，会产生大量的扩展码，使程序大小暴涨
- 参数带有副作用，或是以一个单一表达式做多重调用，或是在inline函数中有多个局部变量，都会产生临时性对象

## 第五章　构造、析构、拷贝语意学

- 纯虚函数的存在

  - 抽象基类，不能被实例化

  - 定义和调用一个纯虚函数，只能静态地调用
  - 对于pure virtual destructor ,class设计者一定得定义它，由于每一个derived class destructor会被编译器加以扩张，以静态调用的方式调用其每一个virtual base class的destructor
  - 不要把virtual destructor声明为pure

- 虚拟规格的存在

- 虚拟规格中const的存在

- 重新考虑class的声明

  ```c++
  class Abstract_base{
      public:
      virtual ~Abstract_base();         //不再是pure virtual
      virtual void interface() =0;   //不再是const
      const char* mumble() const {return _mumble;}   //不再是virtual
      protected:
     　　Abstract_base(char *pc=0);        //constructor
     　　char* mumble;
  };
  ```

### 5.1 无继承情况下的对象构造

- ```c++
  typedef struct{
      float x,y,z;
  }Point;
  ```

- plain OI' Data声明形式，既没有被构造也没有被析构

- C++所有全局对象都被以初始化过的数据来对待

- 抽象数据类型

  ```c++
  class Point{
      public:
      Point(float x=0.0,float y=0.0,float z=0.0):_x(x),_y(y),_z(z){}
      private:
      float _x,_y,_z;
  };   //Point class有一个相关的default copy constructor, copy operator,destructor,然而它们都是trivial，编译器实际上根本没有产生它们
  ```

- 为继承做准备

  ```c++
  class Point{
      public：
      Point(float x=0.0,float y=0.0):_x(x),_y(y){}
      
      virtual float z();
      protected:
      float _x,_y;
  };
  ```

  - 所定义的constructor被附加一些代码，以便将vptr初始化
  - 合成一个copy constructor和一个copy assignment operator,其操作不是trival,但implicit destructor仍然是trival



### 5.2 继承体系下的对象构造

- 编译器会扩充constructor,如下的操作
  - member initialization list中的data members初始化会放在构造函数本体内
  - 未出现在member initialization list中的member如果有default 构造函数，会被调用
  - vptr会被设定
  - 所有上一层的base class constructors必须被调用
    - 若base class在member initialization list中，按指定参数设定
    - 若base class没有在......,则默认构造函数被调用
    - 若base class是多重继承下的第二或后继的base class,那么this指针必须有所调整
  - 所有virtual base class constructors必须被调用
- member class objects的destructor会被合成出来的析构器中调用，(以其构造的相反顺序)

#### 虚拟继承

- 在virtual base class情况下的constructor扩充内容，constructor的函数本体必须条件式地测试进来的参数，然后决定调用或不调用相关的virtual base class constructors

#### vptr初始化语意学

- 在一个class的constructor中，经由构造中的对象来调用一个virtual function, 其函数实例应该是在此class中有作用的那个
- vptr初始化操作应该在base class constructors调用操作之后，但是在程序员供应的代码或是member initialization list中所列的members初始化操作之前

### 5.3 对象复制语意学

- 拒绝把一个class object指定给另一个class object
  - 将copy assignment operator 声明为private
  - 不提供函数定义，则一旦某个member function或friend企图影响一份拷贝，程序在链接时就会失败
- 只有默认行为导致的语意不安全或不正确时，我们才需要设计一个copy assignment operator
- class有bitwise copy语意时，implicit copy assignment operator不会被合成出来，赋值操作由bitwise copy完成，并没有implicit copy assignment operator被调用
- 不会表现出bitwise copy语意的四种情况
  - base class有一个copy assignment operator
  - member object有一个copy assignment operator
  - virtual function
  - 继承自一个virtual base class
- copy assignment operator在虚拟继承情况下行为不佳，需要小心地设计和说明
  - 尽可能不要允许一个virtual base class的拷贝操作
  - 不要在任何virtual base class中声明数据

### 5.3 对象的效能

- bitwise copy语意
  - struct
  - class
  - 单一继承的class
  - 多重继承的class
- 单层虚拟继承
  - 不再有bitwise copy语意
  - 合成型的inline copy constructor和copy assignment operator被产生出来，导致效率成本上的增加
- 有着封装味道并有virtual function的class
  - 合成型的inline copy constructor和copy assignment operator被产生出来，导致效率成本上的增加



### 5.5 析构语意学

- 如果class没有定义destructor,那么只有在class内含的member object(或base class)有destructor的情况下，编译器才会自动合成一个，否则不会合成，甚至它拥有一个虚函数，即使虚拟继承
- 没有任何理由说在delete一个对象之前先得将其内容清除干净，也不需要归还任何资源，因此，也不一定需要一个destructor
- 一个由程序员定义的destructor被扩展的方式类似constructors被扩展的方式，但顺序相反
  - destructor的函数本体首先被执行
  - member class objects如果有destructors,以声明顺序的相反顺序调用
  - vptr被重新设定，指向base class的virtual table
  - 上层的nonvirtual base class如果有destructor,被调用
  - 如果有virtual base class拥有destructor,目前的是最尾端的class,会以其原来的构造顺序的相反顺序被调用



## 第六章　执行期语意学

- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-25 13-42-58.png)





### 6.1 对象的构造和析构

- 如果一个区段或函数有一个以上的离开点，destructor必须被放在每一个离开点
- 一般而言应把object尽可能放置在使用它的那个程序区段附近，这样可以节省非必要的对象产生操作和摧毁操作

#### 全局对象

- **C++程序所有的global objects都被放置在程序的data segment中，如果显式指定给它一个值，此objects将以该值为初值，否则object所配置到的内存内容为0**,**它需要静态的初始化操作和内存释放操作**
- class obejct在编译时期可以被放置于data segment中并且内容为0,但constructor一直要到程序启动时才会实施
- ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-25 13-55-15.png)





#### 局部静态对象

- constructor，destructor必须只能施行一次，即使函数被调用多次

#### 对象数组

- vec_new()　　把默认构造器施行于class objects所组成的数组的每一个元素身上
- vec_vnew()
- vec_delete()
- vec_vdelete()

#### Default constructors和数组

### 6.2 new和delete运算符

- new运算符的两个步骤
  - 通过适当的_new运算符函数实例，配置所需的内存
  - 将配置得来的对象设立初值
- delete类似，如果指针是0,C++要求delete运算符不要有操作
- new运算符实际上总是以标准的C malloc()完成的
- delete运算符也是以标准的C free()完成的

#### 争对数组的new语意

- ```c++
  int* p_array=new int[5];  //没有构造器，只是单纯地获得内存
  //vec_new()不会被调用，new运算符会被调用
  int* p_array=(int*)_new(5*sizeof(int));
  ```

- ```c++
  Point3d* p_array=new Point3d[10];  //有默认构造器时，会被编译为下面的形式
  Point3d* p_array;
  p_array=vec_new(0,sizeof(Point3d),10,&Point3d::Point3d,&Point3d::~Point3d);
  ```

- delete []  p_array   只有在中括号出现时，编译器才寻找数组的维度

- **施行于数组上的destructor,是根据交给vec_delete()函数的被删除之指针类型的destructor, 最好避免以一个base class指针指向一个derived class objects所组成的数组**



#### placement operator new的语意

- Point2w* ptw=new(arena) Point2w;   //其中arena指向内存中的一个区块，它只要将arena所指的地址传回即可

- Placement new operator所扩充的另一半是将Point2w constructor自动施行于arena所指的地址上

- ```c++
  Point2w* ptw=(Point2w*) arena;
  if(ptw!=0)
  {
      ptw->Point2w::Point2w();
  }
  ```

- ```c++
  Point2w* p2w=new(arena) Point2w;
  p2w->~Point2w;   //显式地调用destructor并保存存储空间以便再使用
  p2w=new(arena)Point2w;
  ```

- 一般而言，placement new operator并不支持多态，被交给new的指针，应适当地指向一块预先配置好的内存，如果derived class比其base class，可能会导致严重的破坏



### 6.3 临时性对象

- ```c++
  T operator+(const T&, const T&);
  T a,b;
  T c=a+b;
  //1. 编译器产生一个临时性对象，放置a+b结果，再调用T的copy constructor，把该临时性对象当作c的初始值
  //2. 直接以拷贝构造的方式，将a+b的值放在c中
  //3. NRV优化可能实施，直接导致在上述c对象中求表达式的结果
  ```

- ```c++
  T c=a+b;  //总是比下面的操作更有效率地编译器转换
  c=a+b;
  ```

- 临时对象被摧毁，应该是对完整表达式求值过程中的最后一个步骤。即任何一个子表达式所产生的任何一个临时对象，都应该在完整表达式被求值完成后，才可以毁去　

- 凡持有表达式执行结果的临时性对象，应该留存到object的初始化操作完成为止

- ```c++
  const char* programversion=program+version;
  //这个初始化操作保证失败，programversion指向未定义的heap内存
  String temp;
  operator+(temp,program,version);
  programversion=temp.String::operator char*();
  temp.String::~String;
  ```

- 如果一个临时性对象被绑定于一个reference,对象将残留，直到被初始化之reference的生命结束，或直到临时对象的生命范畴结束

## 第七章　站在对象模型的尖端

### 7.1 template

- 使用实例化表示进程将真正的类型和表达式绑定到template相关形式参数上头

#### template的实例化行为

- ```c++
  Point<float>* ptr=0;  //一个指向class object的指针，本身并不是一个class object,不会被实例化
  const Point<float> &ref=0;
  //内部扩展
  Point<float> temporary(float(0));
  const Point<float> &ref=temporary;  //会实例化
  
  ```

- member function只有被使用的时候，C++　standard才要求它们被实例化

#### template 的错误报告

- 所有与类型有关的检验，如果牵扯到template参数，都必须延迟到真正的实例化操作发生，才的为之

#### template中的名称决议

- template之中，对于一个nonumber name决议结果，是根据这个name的使用是否与用以实例化该template的参数类型有关而决定的。如果互不相关，就以 scope of the template declaration来决定name. 如果其使用互有关联，就以scope of the template instantiation来决定name

#### member function的实例化行为



### 7.2 异常处理

- 执行期类型识别　RTTI

#### exception handling 快速检阅

- throw
- catch
- try
- 当一个exception被抛出时，堆栈中的每一个函数调用被推离，在每一个函数被推离堆栈之前，函数的local class objects的destructor会被调用
- 如果new运算符抛出一个exception,那么就不需要配置heap中的内存，constructor也不需要被调用，也不用调用delete. 如果在constructor中发生exception, 此时内存配置已经完成，那么对象将被自动析构掉，heap内存也会被释放掉，不需要调用delete



#### 对于exception handing的支持

![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-28 10-27-21.png)

- 决定throw 是否发生在一个try区段中
- 将exception的类型和每一个catch子句的类型作比较
  - 对于每一个被抛出来的exception,编译器必须产生一个类型描述器
- 当一个实际对象在程序执行时被抛出，会发生什么事?
  - 当一个exception被抛出时，exception object会被产出来并被放置在相同形式的exception数据堆栈中，从throw端传给catch子句的，是exception object的地址、类型描述符

### 7.3 执行期类型识别(RTTI)

- downcast(向下转换)
- 保证安全的向下转换操作
  - 欲支持type-safe downcast,在object空间和执行时间上都需要一些额外负担
    - 需要额外的空间以存储类型信息，通常是一个指针，指向某个类型信息结点
    - 需要额外的时间以决定执行期的类型
  - C++的RTTI机制提供了一个安全的downcast设备，但只对那些展现多态(使用继承和动态绑定)的类型有效
  - 所有多态classes的objects都维护了一个vptr,只要把与该类相关的RTTI　object地址放进virtual table中，这一指针只需被设定一次，它是被编译器静态设定的
- 保证安全的动态转换
  - dynamic_cast运算符可以在执行期决定真正的类型，类型描述器必须在执行期通过vptr取得
  - dynamic\<pfct>(pt) 比static cast昂贵，但安全

- references并不是Pointers

  ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-28 10-54-32.png)

  - 当dynamic_cast运算符施行于一个reference时，不能提供对等于指针情况下的那一组true/false
  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-28 10-56-41.png)

- Typeid运算符

  - typeid运算符返回一个const reference,类型为type_info,   ==是一个被重载的函数

  - ```c++
    typeid(rt)==typeid(fct);
    bool type_info::operator==(const type_info &) const;
    ```

  - ![](/home/leiwang/Markdown/C++/picture/Screenshot from 2019-09-28 10-59-53.png)

- RTTI提供的type_info对于exception handing的支持是必要的，但再加上一些type_info derived classes，就可以在exception发生时提供关于指针、函数、类等更详细的信息

- 事实上type_info objects也适用于内建类型，以及非多态的使用者自定类型

  - ```c++
    int ex_errno;
    throw ex_errno;
    //int 也有它自己的type_info object
    int *ptr;
    if(typeid(ptr)==typeid(int*))
    ```

  - typeid(double)这样的会传回一个const type_info&,这时的type_info object是静态取得的，而非执行期取得

### 7.4 效率有了，弹性呢?

- 动态共享函数库
- 共享内存