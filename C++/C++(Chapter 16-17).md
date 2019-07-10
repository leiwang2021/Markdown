# C++(Chapter 16-17)

## String类

- string实际上是模板具体化basic_string<char>的一个typedef

- 多个构造函数，重载了+=, =,<< ,[ ]

- ```C++
  template<class Iter>
  string(Iter begin, Iter end)
  //将string对象初始化为区间[begin, end)内的字符，begin和end可以是迭代器（广义化指针）
  ```

- string（string && str）类似于复制构造函数，但不保证将str视为const, 称为移动构造函数

- string(initializer_list<char> il) 使得能够将列表初始化用于string类

  ```C++
  string pinao_man={'L','i','s'};
  ```

- string输入

  - 对于C-风格字符串：

    ```C++
    char info[100];
    cin>>info;  //read a word
    cin.getline(info, 100);  // read a line,discard \n
    cin.get(info,100);       //read a line, leave \n in queue
    ```

  - 对于string对象, string的getline将自动调整对象的大小

    ```C++
    string stuff;
    cin>>stuff;
    getline(cin,stuff);  //read a line, discard \n
    ```

  - getline()有一个可选参数，指定使用哪个字符来确定输入的边界

    ```C++
    cin.getline(info,100,':');
    getline(stuff,':');  //read up to :, discard :  ，将:指定为分界字符后，换行符将
    //被视为常规字符
    ```

    

- string对象的最大允许长度，由string::npos指定

- 可以比较字符串，ASCII码，数字将小于大写字符，而大写字符将小于小写字符

- size()和length()成员函数都返回字符串中的字符数

- find()方法，在字符串中搜索给定的子字符串或字符

- capacity()返回当前分配给字符串的内存块大小，而reserve()方法能够请求内存块的最小长度

- C++实现分配一个比实际字符串大的内存块，为字符串提供了增大空间。如果字符串不断增大，超过了内存块的大小，程序将分配一个大小为原来两倍的新内存块

- open()方法要求使用一个C—风格字符串作为参数，c_str()方法返回一个指向C-风格字符串的指针

- string库实际上是基于一个模板类的

### 智能指针模板类

- 包含头文件memory

- 类似于指针的类对象

- 如果指针是对象，则可以在对象过期时，让它的析构函数删除指向的内存

- 三个智能指针模板, 位于名称空间std中

  可以将new获得的地址赋给这种对象，当智能指针过期时，其析构函数将使用delete来释放内存

  - auto_prt
  - unique_ptr
  - shared_ptr

- 所有智能指针都有一个explicit构造函数，该构造函数将指针作为参数

- 有关智能指针的注意事项：

  - 定义赋值运算符，使之执行深度复制
  - 建立所有权概念，对于特定的对象，只有一个智能指针可拥有它，让赋值操作转让所有权，这是auto_ptr,和unique_ptr的策略
  - 创建智能更高的指针，跟踪引用特定对象的智能指针数，引用计数。仅当最后一个指针过期时，才调用delete，这是shared_ptr的策略

- unique_ptr赋给另一个时，如果源unique_ptr是个临时右值，编译器允许这样做，如果源unique_ptr将存在一段时间，编译器将禁止这样做

- 使用new分配内存时，才能使用auto_ptr和shared_ptr，使用new[]分配内存时，不能使用它们

  unique_ptr都可以

- 如果程序要使用多个指向同一个对象的指针，应选择shared_ptr

### 标准模板库

- STL提供了一组表示容器、迭代器、函数对象和算法的模板，泛型编程

  - 容器与数组类似
  - 算法是完成特定任务的处方
  - 迭代器用来遍历容器的对象，是广义指针
  - 函数对象是类似于函数的对象，可以是类对象或函数指针

- 各种STL容器模板都接受一个可选的模板参数，该参数指定使用哪个分配器对象来管理内存

- vector模板使用动态内存分配

- 基本方法：

  - size()返回元素数目
  - swap交换两个容器的内容
  - begin 返回一个指向容器中第一个元素的迭代器
  - end 返回一个表示超过容器尾的迭代器

- 每个容器类都定义了一个合适的迭代器，该迭代器的类型是一个名为iterator的typedf,其作用域为整个类,类似与指针

  ```C++
  vector<double>::iterator pd;
  ```

- push_back将元素添加到矢量末尾

- erase()方法删除矢量中给定区间的元素

- insert()方法，接受3个迭代器参数，第一个参数指定了新元素的插入位置，第二个和第三个迭代器参数定义了被插入区间

- for_each()函数可用于很多容器类，接受三个参数，前两个是定义容器中区间的迭代器，最后一个是指向函数的指针（函数对象），被指向的函数不能修改容器元素的值

  ```C++
  for_each(books.begin(),books.end(),ShowReview);
  ```

- Random_shuffle()函数接受两个指定区间的迭代器参数，并随机排列该区间中的元素,要求容器支持随机访问

  ```C++
  random_shuffle(books.begin(),books.end());
  ```

- sort()函数也要求容器支持随机访问，使用为存储在容器中的类型元素定义的<运算符

- 基于范围的for循环

  ```C++
  for_each(books.begin(),books.end(),ShowReview);
  for (auto x: books) ShowReview(x); //根据book的类型，编译器推断出x的类型，而循环依
  //次将books中的每个Review对象传递给ShowReview()
  //指定一个引用参数，基于范围的for循环可修改容器的内容
  ```

### 泛型编程

- 面向对象编程关注的是编程的数据方面，而泛型编程关注的是算法

- 模板使得算法独立于存储的数据类型，而迭代器使得算法独立于使用的容器类型

- 泛型编程使得函数不仅独立于容器中存储的数据类型，而且独立于容器本身的数据结构

- 每个容器类定义了相应的迭代器类型，每个容器类都有一个超尾标记，都有begin和end方法，都使用++操作

- STL定义了5种迭代器
  - 输入迭代器，可被程序用来读取容器中的信息，是单向的
  - 输出迭代器，将信息从程序传输给容器的迭代器
  - 正向迭代器，按相同的顺序遍历一系列值，可读可写
  - 双向迭代器
  - 随机访问迭代器

- 根据特定类型编写的算法可以使用该种迭代器，也可以使用具有所需功能的任何其他迭代器

- 容器种类：

  容器概念（容器、序列容器、关联容器）和容器类型

  - 容器概念指定了所有STL容器类都必须满足的一系列要求

  - 复杂度：编译时间、固定时间、线性时间

  - 复制操作保留源对象，而移动操作可修改源对象，还可能转让所有权，而不做任何复制

  - 七种序列容器类型：

    - vector:最简单的序列类型
    - deque表示双端序列
    - list表示双向链表
    - forward_list实现了单链表
    - queue是一个适配器类
    - priority_queue模板类是另一个适配器类
    - stack也是一个适配器类，它给底层类提供了典型的栈接口
    - array并非STL容器，但可将很多标准STL算法用于array对象

  - 关联容器：将键与值关联在一起，关联容器通常是使用某种树实现的

    - set:值类型与键相同，键是唯一的
    - multiset:类似与set,但可能有多个值的键相同
    - map:值与键的类型不同，键是唯一的，每个键只对应于一个值
    - multimap与map相似，只是一个键可以与多个值相关联

  - 无序关联容器

    也将值与键关联起来，并使用键来查找值，但底层的差别在于，关联容器是基于树结构的，而无序关联容器是基于数据结构哈希表的

    - unordered_set
    - unordered_multiset
    - unordered_map
    - unordered_multimap

### 函数对象

函数符，可以以函数方式与（）结合使用的任意对象，包括函数名，指向函数的指针，重载了（）运算符的类对象

- 生成器： 不用参数就可以调用的函数符

- 一元函数：用一个参数就可以调用的函数符

- 二元函数：用两个参数就可以调用的函数符

- 预定义的函数符

  STL定义了多个基本函数符，执行将两个值相加、比较两个值是否相等操作

- 头文件functional定义了多个模板类函数对象

- 对于所有内置的算术运算符、关系运算符和逻辑运算符，STL都提供了等价的函数符

- 自适应生成器、自适应一元函数、自适应二元函数、自适应谓词、自适应二元谓词

- 使函数符成为自适应的原因：它携带了标识参数类型和返回类型的typedef成员

- 函数自适应的意义在于：函数适配器对象可以使用函数对象，并认为存在这些typedef成员

- C++11提供了函数指针和函数符的替代品—lambda表达式

### 算法

- ＳＴＬ包含很多处理容器的非成员函数，它们大都使用迭代器来标识要处理的数据区间和结果的放置位置，有些函数还接受一个函数对象参数，并使用它来处理数据
- 对于算法函数设计，有两个主要的通用部分：它们都使用模板来提供泛型，它们都使用迭代器来提供访问容器中数据的通用表示
- ＳＴＬ将算法库分成４组：
  - 非修改式序列操作　:algorithm头文件中，对区间中的每个元素进行操作，不修改容器的内容
  - 修改式序列操作，　也对区间中的每个元素进行操作，可以修改容器的内容
  - 排序和相关操作，　包括多个排序函数和其他各种函数
  - 通用数字运算：　　包括将区间的内容积累，计算两个容器的内部乘积等，ｎｕmeric头文件中
- 有些算法就地完成工作（in-place algorithm），有的创建拷贝（copying algorithm），有些算法有这两个版本
- 对于复制算法，统一约定：返回一个迭代器，指向复制的最后一个值后面的一个位置
- string类不是STL的组成部分，但设计它时考虑到了ＳＴＬ，可以使用STL接口
- 函数和容器方法，通常方法是更好的选择

### 其他类

- vector  valarray  array
- 模板initializer_list





## 输入、输出和文件

### Ｃ++输入和输出概述

- C++把输入和输出看作字节流
- 缓冲区：用作中介的内存块，Ｃ++通常在用户按下回车键时刷新输入缓冲区，对于输出，通常在用户发送换行符时刷新输出缓冲区
- streambuf类为缓冲区提供了内存
- ios_base类表示流的一般特征
- ios类基于ios_base，包括了一个指向streambuf对象的指针成员
- ostream,istream提供了输出输入方法,从ios派生而来
- iostream类基于istream和ostream类
- 程序包含iostream文件将自动创建８个流对象：cin, cout, cerr, clog
- 当iostream文件为程序声明一个cout对象时，该对象将包含存储了与输出有关的信息的数据成员，如显示数据时使用的字段宽度、小数位数、显示整数时采用的计数方法以及描述用来处理输出流的缓冲区的streambuf对象的地址
- 标准输入和输出通常连接着键盘和屏幕，重定向使得能够改变标准输入和标准输出，对标准输出重定向并不会影响cerr和clog

### 使用cout进行输出

ostream类将数据内部表示（二进制模式）转换为由字符字节组成的输出流

- 重载的<<运算符
- ostream类的put()方法和write()方法，f分别用于显示字符和字符串
  - cout.put('W')  返回一个调用对象的引用
  - write()的第一个参数提供了要显示的字符串地址，第二个参数指出要显示多少个字符
- 控制符flush刷新缓冲区，endl刷新缓冲区，并插入一个换行符
- 用cout进行格式化
  - ios_base类存储了描述格式状态的信息，控制符实际上是函数，但可用如下的方式使用: cout<<hex; 与hex(cout)等价
  - 可用width成员函数将长度不同的数字放到宽度相同的字段中　　int width(int i), width方法值影响接下来的一个显示，之后恢复默认值
  - 默认情况下，cout用空格填充字段中未被使用的部分，可用用fill()成员函数来改变填充内容，新的填充字符将一直有效
  - C++的默认精度为６位，precision()成员函数使得能够选择其他值
  - ios_base类提供了一个setf()函数，能够控制多种格式化特性，cout.setf(ios_base::showpoint)使cout显示末尾小数点
  - setf的效果可用unsetf消除
  - 标准控制符
  - 头文件 iomanip

### 使用cin进行输入

cin对象将标准输入表示为字节流，根据接收值的变量的类型，使用其方法将字符序列转换为所需的类型

- cin>>hex  将整数输入解释为十六进制

- **cin跳过空白（空格、换行符、制表符**），直到遇到非空白字符。读取从非空白字符开始，到与目标类型不匹配的第一个字符之间的全部内容，其余的留在输入流中

- 输入与预期格式不匹配将导致cin>>input的结果为false

- cin和cout包含一个描述流状态的数据成员（从ios_base类那里继承），流状态由三个ios_base元素组成：　eofbit  badbit  failbit　都是１位

- 设置状态: clear()将调用默认参数０，将三个状态位清除，clear(efobit) 将efobit设置，其余清除，setstate(eofbit) 将只设置eofbit，不管其他的

- Ｉ/O和异常，　可以使用exceptions()方法来控制异常如何被处理，包含一个位字段，对于eofbit  badbit  failbit，　　ios_base::failure异常类

- 导致输入循环终止的不匹配输入仍然留在输入队列中，程序必须跳过它，一种方法是一直读取字符，直到到达空白，isspace()在空白字符时返回Ｔrue,或丢弃行中剩余部分

- get(char &) 提供不跳过空白的单字符输入功能，只要存在有效输入，cin.get(ch)的返回值都是cin,此时的判定结果为True，循环将继续，到达文件尾时，返回值为false

- get(void)提供不跳过空白的单字符输入功能，但使用返回值来将输入传递给程序，返回类型为int,到达文件尾时，cin.get(void) 将返回ＥＯＦ

- 字符串输入：getline()  get()  ignore()

  　get将换行符留在输入流中，getline()将丢弃换行符。遇到分界符后，输入将停止。

  - istream & get(char*, int, char)  第三个参数指定用作分界符的字符，只有两个参数的版本将换行符用作分界符
  - istream & get(char*, int)
  - istream & getline(char*, int, char)
  - istream & getline(char*, int)
  - cin.ignore(255,'\n') 读取并丢弃接下来的２５５个字符或直到到达第一个换行符
  - get和getline在不能抽取字符时，将把空值字符放置到输入字符串中，并使用setstate()设置failbit

- 其他istream方法：

  - read()读取指定数目的字节，并存储到指定的位置　cin.read(gross,144),不会在输入后加上空值字符，不能将输入转换为字符串，read()常与ostream write()使用，完成文件输入输出
  - peek()返回输入中的下一个字符，但不会抽取输入流中的字符



### 文件输入和输出

- 简单的文件IO:
  - 写入文件：创建ofstream对象，将该对象与文件关联起来（可以使用open方法），以cout方式使用该对象，有缓冲区
  - 读取文件：创建ifstream对象，将该对象与文件关联起来，以使用cin的方式使用该对象，有缓冲区
  - 使用close()关闭到文件的连接，只是断开流到文件的连接，并不会删除流，对象与缓冲区仍然存在，可将流重新连接到一个文件

- 流状态检查和is_open()
  - C++文件流类从ios_base类继承了一个流状态成员　　　fin.fail()
  - ifstream对象被放在需要bool类型的地方时，将被转换为bool值
  - 方法is_open()能够检测到以不合适的文件模式打开文件时失败和good()能检查到的错误

- 打开多个文件：可以打开一个流，将它依次关联到各个文件

- 命令行处理技术：让在命令行中运行的程序能够访问命令行参数的机制
  - int main(int argc, char *argv[])
  - 可使用cerr<<"wrong "表示错误的信息

- 文件模式

  读、写、追加等

  ```C++
  ofstream fout("bagels", ios_base::out | ios_base::app);
  //|运算符合并模式，ios_base::out | ios_base::app意味着启用模式out和app
  ```

  - C++模式和C模式

  - 追加文件:  ios_base::app

  - 文本格式和二进制格式

    使用二进制文件模式时，程序将数据从内存传输给文件，将不会发生任何隐藏的转换，而默认的文本模式并非如此

    - 文本格式：存储的是字符格式，可使用编辑器读取和处理文本文件

      ```C++
      ofstream fout("planets.dat", ios_base::out |ios_base::app);
      fout<<pl.name<<" "<<pl.population<<" "<<pl.g<<"\n";
      ```

    - 二进制格式:存储的是计算机内部表示，保存速度更快

      ```C++
      ofstream fout("planets.dat", ios_base::out |ios_base::app | ios_base::binary);
      fout.write((char*) &pl, sizeof pl);　　//使用read来恢复
      ```

- 随机存取：直接移动到文件的任何位置，常用于数据库文件

  - seekg():将输入指针移动到指定的文件位置
  - seekp():将输出指针移动到指定的文件位置　指针指向的是缓冲区中的位置，而不是实际的文件
  - tellg()和tellp()返回一个表示当前位置的streampos值

- 使用临时文件

  tmpnam()函数创建一个临时文件名，常量L_tmpnam和TMP_MAX(定义在cstdio中)限制了文件名包含的字符数以及tmpnam()可被调用的次数

### 内核格式化

读取string对象中的格式化信息或将格式化信息写入string对象

istringstream和ostringstream类使得能够使用istream和ostream类的方法来管理存储在字符串中的字符数据

