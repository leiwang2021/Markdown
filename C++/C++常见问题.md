# C++常见问题

- istream类没有处理string对象的类方法

  读取一行时，应使用getline(cin, string)

  但可以使用cin>>string  (友元函数的作用)

- cin忽略输入流中的空白符（回车符、空格符、制表符），回车符仍保留在输入流中
   cin.get();  //     提取先前留在输入流中的回车符，否则下 getline()不会等待输入，而直接读取输入流中已有的回车符

- cin>>ch 将跳过空格、换行符和制表符，cin.get(ch)  和cin.get()将读取这些字符

- 如何使 while（getline(cin, str)）或者 while(cin >> str)正常跳出循环继续剩余程序的执行,UNIX/Linux下：UNIX/Linux模拟流/文件结束标志为CRTL+D

- Segmentation fault (core dumped), 可能是数组越界的问题

- gdb的调试

- swap(S[left],S[right]);　　　swap函数可用于交换两个vector位置的元素

- Segmentation fault (core dumped),访问一些空的，可能会出现该问题

- 当有多个cin输入时，注意要不要加上cin.get()去掉缓冲区中的换行符

- cin.getline()用于读取字符串时，输入时中间不能有空格

- 将一个string(key.c_str())直接赋值给一个string报错，什么原因????     

   ```
       string data;
        string data2="sdfsdf";
        data=string(data2.c_str());
        cout<<data;
   //这种方式不出错
   ```

   ```
        List NewCell;
        NewCell=(List)malloc(sizeof(LNode));
        //NewCell->data=word;  //不会报错
        string temp;
        temp=string(word.c_str());
        NewCell->data=temp;       //这种方式不会出错，这种不是临时变量
        //NewCell->data=string(word.c_str());//出错　什么原因?  函数中创建的对象被析构的原因?
        //NewCell->data="sdfsfsd";   //不会报错
        //cout<<NewCell->data;
       // cout<<&(string(word.c_str()));  //临时变量，报错
   
   
   //会报Segmentation fault (core dumped),错误
   //临时变量的问题????????????
   ```

- 将常量字符串赋给char* 在C++11中不允许，应该赋给char const *

- ```c++
  int *p1 = new int[10]; 
  int *p2 = new int[10]();
  //对于内置类型而言，new仅仅是分配内存，除非后面显示加(),相当于调用它的构造函数，对于自定义类型而言，只要一调用new，那么编译器不仅仅给它分配内存，还调用它的默认构造函数初始化，即使后面没有加()
  ```

- **全局变量时初始化为0，局部变量时初始化为随机值。**

- p1指向字符型，一次移动一个字符型，1个字节；p1+5后移5个字节，16进制表示为5；

-  p2指向长整型，一次移动一个长整型，4个字节，p2+5后移20字节，16进制表示为14。

- 数组作为函数的参数是会退化为函数指针的

- 全局变量，静态局部变量，局部变量空间的堆分配和栈分配

  - 全局变量和静态局部变量时从 静态存储区中划分的空间，全局变量作用域大于静态局部变量

  - ```c++
    C c;
    void main()
    {
        A*pa=new A();
        B b;
        static D d;
        delete pa;
    }
    //对于类A,  是建立在堆上的对象指针pa, 手动释放.对于类B, 是建立在栈上的对象b,main函数结束就释放
    //对类C ,在静态存储区创建了一个对象c ,程序结束时候释放.对类D,也是在静态存储区建立对象d,但是局部变量,程序结束时候释放.
    ```

  - 当类中出现static成员变量的时候，static成员变量是存储在静态区当中的，它是一个共享的量，因此，在为这个类创建一个实例对象的时候，是无需再为static成员变量分配空间的，所以，这个类的实例对象所需要分配的空间是要排除static成员变量的，于是，当sizeof计算类的大小的时候会忽略static成员变量的大小