# C++ (Chapter 5-6)

## 循环和关系表达式

### for循环

- cout.setf(ios: boolalpha)函数调用设置了一个标记，命令cout显示true和false

- 在for-init-statement中声明变量，这种变量只存在于for语句中
- a++使用a的当前值计算表达式，然后将a的值加1
- 复合语句：如果在语句块中定义一个新的变量，则仅当程序执行该语句块中时，变量才存在
- 逗号运算符：先计算第一个表达式，然后计算第二个表达式，逗号表达式的值是第二部分的值
- C-风格字符串的比较：strcmp()  如果两个字符串相同，该函数将返回零
- string类重载了运算符，可以直接使用比较运算符
### while循环

- 头文件ctime

  符号常量CLOCKS_PER_SEC，每秒钟包含的系统时间单位数

  clock_t 为clock()返回类型的别名

- 类型别名
    使用预处理器  #define BYTE char
    使用关键字typedef char byte, typedef char*  byte_pointer 将byte_pointer声明为char指针

- do  while 循环

- 基于范围的for循环
```
double prices[5]={5.2,32.2,231.3,32.2,23};
for (double &x:prices)
    x=x*0.8;
```

- 头文件iostream将cin.get(ch)的参数声明为引用类型，因此该函数可以修改其参数的值

- 函数重载允许创建多个同名函数，条件是它们的参数列表不同

- EOF结束输入，cin.clear()方法可清除EOF标记，使输入继续进行，EOF不表示输入中的字符，而是指出没有字符

## 分支语句和逻辑运算符

### if语句

- 错误防范 if(3==myNumber)   
### 逻辑表达式
|| &&  !

- 字符函数库cctype

  isalpha(ch)  是否为字母

  ispunct(ch) 是否为标点符号
- ？：运算符
- switch语句
程序跳到switch中特定代码行后，将依次执行之后的所有语句，除非有明确指示，程序不会在执行到下一个case处自动停止
switch语句中的每一个case标签都必须是一个单独的值，这个值必须是整数，case标签值必须是常量
- 在for循环中，continue语句将使程序跳到更新表达式处，对于while语句，将跳到测试表达式处
- goto语句，跳到标签的位置
### 读取数字的循环
- 输入错误和EOF都将导致cin返回false
### 简单文件输入和输出
- 必须包含头文件，头文件fstream定义了一个用于输出的ofstream类
- open（）方法接受一个C—风格字符串作为参数
- 包含头文件，创建一个ofstream对象，将该对象和一个文件关联起来，像使用cout一样使用它
- 打开已有的文件，以接受输入时，默认将其长度截断为0
- 声明一个ifstream对象，像cin一样使用它
- 函数exit()终止程序

  