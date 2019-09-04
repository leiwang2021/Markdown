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

