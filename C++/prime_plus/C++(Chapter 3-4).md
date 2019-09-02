# C++(Chapter 3-4)

- 基本类型：整数和浮点数

- 复合类型：数组，字符串，指针，结构


##  整型：
char,short,int ,long, long long， 每种都有符号和无符号两种
short至少16位
int至少与short一样长
long至少32位
long long至少64位
8位： 0-256
16位：65536
- 字节
C++字节由至少能够容纳实现的基本字符集的相邻位组成
C++类型的宽度随实现而异，将C++从一种环境移到另一种环境时可能引发问题
**sizeof**运算符返回类型或变量的长度，单位为字节
对类型名使用sizeof时，应包括括号，变量时，括号可选
头文件climits中包含了关于整型限制的信息
-  初始化
```
int wrens(20)
int emus{7}
int rehes={12}
int rocs{}  //初始化为0
//C++可将大括号初始化器用于任何类型
```
如果不对函数内部定义的变量进行初始化，该变量的值将是不确定的，它是相应内存单元保存的值

- 无符号类型

  unsigned

  C++不保证符号整型超越限制（上溢和下溢）时不会出错

- char类型
专为存储字符而设计的，C++实现使用的是其主机系统的编码
字符用单引号，字符串用双引号
```
cout.put('!')    // 用于显示一个字符
```

- char16_t和char32_t类型

  前者是无符号的，16位。后者是无符号的，长32位

- bool类型
任何非零值都被转换为true，而零值被转换成false

## const限定符

```
const type name=value
```

## 浮点数

E表示法确保数字以浮点数格式存储，即使没有小数点

float, double, long double

有效位： float 通常32位，double 64位，long double 128位

- ostream方法setf()

  迫使输出使用定点表示法，参数ios_base:fixed和ios_base::floatfield是通过包含iostream来提供的常量

  ```
  cout.setf(ios_base::fixed, ios_base::floatfield)
  ```

- 以{}方式初始化时进行的转换（列表初始化）
  列表初始化不允许缩窄

- 传递参数时的类型转换通常由C++函数原型控制

- 强制类型转换
```
（typeName） value
typeName (value)
static_cast<typeName> (value)
```

- auto

  如果使用关键字auto,而不指定变量的类型，编译器将把变量的类型设置成与初始值相同

  ```
  std::vector<double> scores;
  std::vector<double>::iterator pv=scores.begin();
  //两种方式相同
  std::vector<double> scores;
  auto pv=scores.begin()
  ```

  
## 复合类型

### 数组

###### **声明数组**:  

```
typeName arrayName[arraySize];
```

编译器不会检查使用的下标是否有效

sizeof（数组名）得到的是整个数组中的字节数

###### 初始化：

`int cards[4]={1,2,3}`初始化时提供的值可以少于数组的元素数目，若只对一部分进行初始化，其他设为0

`short things[]={1,5,3,8}`

`double earnings[4] {1.2, 1.2, 1.3}`

### 字符串

存储在内存的连续字节中的一系列字符

###### C风格字符串

以空字符\0结尾

- 字符串常量：

  `char birds[11]="Mr.Cheeps";`

  用引号括起的字符串隐式地包括结尾的空字符

  ‘S'字符常量   "S"字符串常量表示两个字符组成的字符串，表示的是字符串所在的内存地址

###### cin使用空白（空格、制表符、换行符）来确定字符串的结束位置

- getline 和get()

  getline()读取一行输入，直到换行符，将丢弃换行符

  get()读取一行输入，将换行符保留在输入序列中

  `cin.getline(name,20)`将这一行读入到name数组中，最多读取19个，余下用来作为空字符

  `cin.get()`可读取下一个字符

  ```
  cin.get(name,Arsize);
  cin.get()   //处理换行的问题
  cin.get(dessert,Arsize);
  ```

  当cin读取后，可能将回车键生成的换行符留在了输入队列中，解决办法是加一个`cin.get()`

###  String类

  str的声明创建一个长度为0的string对象，但程序将输入读取到str中时，将自动调整str的长度

```
string thidrs {"Hank's Fine Eats};
```

**不能将一个数组赋给另一个数组，但可将一个string对象赋给另一个string对象**

```
string str1;
string str2="panther";
str=str2;
string str3;
str3=str1+str2;
strcpy(charr1,charr2); //可将charr2复制到charr1中
strcat(charr1,charr2); //将charr2的附加到charr1末尾
```

```
int len1=str1.size();
int len2=strlen(charr1);
```

###### char16_t, char32_t, 原始字符串

```
L"Chief"
u"Felonia"
U"Humber"
R"(sfdklsdjgl""fsdf\nsfes)"
```

### 结构

结构是用户定义的类型，定义结构描述，按描述创建结构变量

外部变量由所有函数共享，不提倡使用外部变量，提倡使用外部结构声明

支持列表初始化，支持赋值操作

```
struct inflatable
{
    char name[20];
    float volume;
    double price;
};
inflatable guest{
    "dasda",
    1.2,
    1.2
};
```

### 共用体

能够存储不同的数据类型，但只能同时存储一种类型

```
union one4all
{
    int int_val;
    long long_val;
    double double_val;
};
```

共用体每次只能存储一个值，长度为最大成员的长度

```
struct widget
{
    char brand[20];
    int type;
    union
    {
        long id_num;
        char id_char[20];
    };
};
widget prize;
if(prize.type==1)
	cin>>prize.id_num;
else
	cin>>prize.id_char;
//共用体常用于节省内存
```

### 枚举

`enum spectrum {red, orange, green}`将red, orange,green作为符号常量，对应于整数值0-2

枚举量是整型，可被提升为int类型

`enum bits{one=1, two=2, eight=8}`

`enum big{first, second=100, third}` first为0，third为101

### 指针和自由存储空间

OOP强调的是在运行阶段（而不是编译阶段）进行决策

指针声明时必须指定指针指向的数据类型

```
int* p1,p2  //创建一个指针p1和一个int型变量，对于每个指针变量名，都需要使用一个*
```

一定要在应用*之前，将指针初始化为一个确定的、适当的地址

##### new

`int* pn=new int;`

**一般变量的值都存储在栈（stack)的内存区域中，而new从堆（heap)或自由存储区的内存区域分配内存**

```
int* ps=new int;
...
delete ps;  //释放ps指向的内存，但不会删除指针ps本身
```

**一定要配对地使用new和delete，否则将发生内存泄露**

#### 静态联编和动态联编

```
int* psome=new int [10];  //new运算符返回第一个元素的地址
...
psome[1]  //可使用数组表示法来访问元素
delete [] psome;
```

#### 指针、数组和指针算术

C++将数组名解释为数组第一个元素的地址

在cout和多数C++表达式中，char数组名、char指针、用引号括起来的字符串常量都被解释为字符串第一个字符的地址

给cout提供一个指针，它将打印地址，但如果指针的类型为char*，cout将显示指向的字符串

使用new创建动态结构

#### 自动存储、静态存储和动态存储

##### 自动存储

自动变量是一个局部变量，其作用域为包含它的代码块，通常存储在栈中，后进先出（LIFO）

##### 静态存储

static，在整个程序执行期间都存在

##### 动态存储

在堆或自由存储空间中，  new和delete，数据的生命周期不完全受程序或函数的生存时间控制

#### 模板类vector和array

##### vector

vector类使用new和delete来管理内存

```
#incluede<vector>
using namespace std;
vector<int> vi;
int n;
cin>>n;
vector<double> vd(n);
```

##### array

array对象的长度是固定的，使用栈（静态内存分配），但可以将一个array对象赋给另一个array对象

```
#include<array>
using namespace std;
array<int,5> ai;
array<double,4> as={1.2,1.2,12.2,2.3};
```

如果ar是数组名，则表达式ar[i]被解释为*(ar+i)



