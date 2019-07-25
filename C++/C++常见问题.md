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

   
