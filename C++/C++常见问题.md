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

-  swap(S[left],S[right]);　　　swap函数可用于交换两个vector位置的元素
