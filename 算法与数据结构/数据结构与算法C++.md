# 数据结构与算法(C++)

## 第一章　概论

### 1.1　引言

### 1.2 数据结构

- 抽象数据类型(ADT)

### 1.3 算法

- 算法复杂度
  - 空间复杂度　S(n)
  - 时间复杂度　T(n)
  - 两段算法串联在一起的复杂度，取决于比较慢的算法
  - 两段算法嵌套在一起的复杂度，为相乘的复杂度
  - 若是关于n的k阶多项式，复杂度为theta(n^k)
  - 一个for循环的复杂度等于循环次数乘以循环体代码的复杂度
  - if条件判断的复杂度等于判断复杂度和两个分支部分的复杂度的最大值

### １.4 最大子列和问题

- 分而治之（分治法）的基本思路是将原问题拆分成若干小型问题，分别解决后再将结果和而治之，用递归实现很方便
- 最大子列和的分治法：　O(NlogN)
- 在线处理：每输入一个数据就进行即时处理，得到结果是对于当前已经读入的所有数据都成立的解，即在任何一个地方终止输入，算法都能给出当前正确的解，复杂度只有O(N)  
- 关键是让计算机记住一些关键的中间结果，避免重复计算



## 第２章　数据结构实现基础

### 2.1

- 数据组织的基本存储方式主要是利用数组和链表方式来实现
- 数据结构的存储实现跟所需要的操作密切相关，没有最好的存储方式，只有最合适的存储方式
- **求集合中的第K大数问题**

### 2.2 　数据存储基础

- 数组

- 类型定义typedef

- 指针

  - 动态内存分配:   void * malloc (unsigned size)
  - 动态存储释放函数:   void free (void * ptr)

- 结构

- 共用体

- 链表

  - 每一个结点里保存着下一个结点的地址

  - 单向链表

    - 通常使用结构的嵌套来定义单向链表结点的数据类型，结构的递归定义

      ```C++
      typedef struct Node * PtrToNode;
      struct Node{
          ElementType Data;
          PtrToNode  Next;
      }
      ```

    - ```C++
      PtrToNode p=(PtrToNode) malloc (sizeof(struct Node));
      ```

    - 插入结点

      ```C++
      t->Next=p-Next;
      p->Next=t;
      ```

    - 删除结点

      ```C++
      t=p->Next;
      p->Next=t->Next;
      free(t)
      ```

    - 单向链表的遍历

    - 带头结点的单向链表

  - 双向链表

    - 多了前驱单元指针
    - 双向循环链表：

  - **单链表反转问题：**

### 2.3 流程控制基础

- 分支控制
- 循环控制
- **选择排序:** 从待排序列中找出值最大的元素，然后将该最大值元素与待排序列的第一个元素交换，一直重复该过程，直到待排序列只剩一个元素
- 函数与递归
  - 递归出口：即递归的结束条件
  - 递归子式：当前函数结果与准备调用的函数结果之间的关系
  - 汉诺塔问题
  - **第K大数**：递归方法求解
    - 选取s中的元素e将e分解为大于e的集合S1和小于e的集合S2,转换为在S1和S2中的查找问题。
    - 如何分解为两个集合：从左右两端扫描，直到中间相遇，时间复杂度为O(n)且不需要额外空间
    - 基于冒泡排序和简单选择排序，时间复杂度为o(n*k)
    - 基于最小堆，o(nlogk)
    - 基于快速排序，o(n)

## 第三章　线性结构

### 3.1

### 3.2 线性表的定义与实现

- 定义

  - 由同一类型的数据元素构成的有序序列的线性结构
  - 初始化
  - 查找
  - 插入
  - 删除

- 线性表的顺序存储实现(在内存中用地址连续的一块存储空间顺序存储各元素)

  ```C++
  typedef int Position;
  typedef struct LNode* PtrToLNode;
  struct LNode {
      ElementType Data[MAXSIZE];
      Position Last;
  };
  typedef PtrToLNode List;
  ```

- 初始化

  ```C++
  List MakeEmpty()
  {
      List L;
      L=(List)malloc(sizeof(struct LNode));
      L->Last=-1;
      return L
  }
  ```

- 查找,时间复杂度为O(n)

  ```C++
  #define ERROR -1
  Position Find(List L, ElemenType X)
  {
      Position i=0;
      while(i<=L->Last && L->Data[i]!=X)
      	i++;
      if(i>L->Last)
     		return ERROR;
     	else 
     		return i;
  }
  ```

- 插入,时间复杂度为O(n)

  ```C++
  bool Insert(List L, ElemenType X, int i)
  {
      Position j;
      if(L->Last==MAXSIZE-1)
      {	printf('满')
      	return false;
      }
       if(i<1 ||i>L->Last+2)
       {	printf('位序不合法');
      	return false;
       }
      for(j=L->Last;j>=i-1;j--)
      	L->Data[j+1]=L->Data[j];
      L->Data[i]=X;
      L->Last++;
      return true;
  }
  ```

- 删除，时间复杂度为O(n)

  ```C++
  bool delete (List L, int i)
  {
      Position j;
      if(i<1 || i>L->Last+1)
      {	printf('位序不存在元素');
      	return false;
      }
      for(j=i;j<=L->Last;j++){
          L->Data[j-1]=L->Data[j];
      }
      L->Last--;
      return true;
  }
  ```

- 线性表的链式存储实现(不需要地址连续的存储单元，不要求逻辑上相邻的两个元素物理上也相邻)

  ```c++
  typedef struct LNode* PtrToLNode;
  struct LNode {
      ElementType Data;
     	PtrToLNode Next;
  };
  typedef PtrToLNode List;
  typedef PtrToLNode Position;
  ```

- 求表长,时间复杂度为O(n)

  ```
  int Length(List L){
      Position p;
      int cnt=0;
      p=L;
      while(p){
          p=p->Next;
          cnt++;
      }
      return cnt
  }
  ```

- 查找，时间复杂度为O(n)

  - 按序号查找
  - 按值查找

- 插入,时间复杂度为O(n)

  ```C++
  bool Insert(List L,ElemenType X, int i){
      //默认有头节点
      Position tmp,pre;
      int cnt=0;
      pre=L;
      while(pre && cnt<i-1){
          pre=pre->Next;
          cnt++;
      }
      if(pre==NULL || cnt!=i-1)
      	return false;
      else{
          tmp=(Position)malloc(sizeof(struct LNode));
          tmp->Data=X;
          tmp->Next=pre->Next;
          pre->Next=tmp;
          return true;
      }
      
  }
  ```

- 删除，时间复杂度为O(n)

  ```C++
  bool Delete(List L,int i){
      Position tmp,pre;
      int cnt=0;
      
      pre=L;
      while(pre && cnt<i-1){
          pre=pre->Next;
          cnt++;
      }
      if(pre==NULL || cnt!=i-1 || pre->Next=NULL){
          return false;
      }
      else{
          tmp=pre->Next;
          pre-Next=tmp->Next;
          free(tmp);
          return true
      }
  }
  ```

- 广义表与多重链表

  - 广义表中，元素不仅可以是单元素也可以是另一个广义表

  - 采用共用体实现两个域的复用

    ```c++
    typedef struct GNode* PtrToGNode;
    typedef PtrToGNode GList;
    struct GNode{
        int Tag;
        union{
            ElementType Data;
            GList Sublist;
        }URegion;
        PtrToGNode Next;
    };
    ```

  - 双向链表不是多重链表

  - 树、图可以用多重链表实现

### 3.3 堆栈

- 具有一定约束的线性表，插入和删除都作用在栈顶的端点位置

- LIFO表，压入栈:Push   弹出栈:Pop

- 堆栈的实现(C++中有STL实现):

  - 可采用顺序和链式两种形式

  - 栈的顺序存储实现：

    ```c++
    typedef int Position;
    typedef struct SNode* PtrToSNode;
    struct SNode {
        ElementType * Data;
        Position Top;  //栈顶指针
        int MaxSize;
    }
    typedef PtrToSNode Stack
    ```

    ```C++
    //创建一个空的堆栈
    Stack CreateStack(int MaxSize){
        Stack S=(Stack)malloc(sizeof(struct SNode));
        S->Data=(ElemenType*)malloc(MaxSize*sizeof(ElemenType));
        S->Top=-1;
        S->MaxSize=MaxSize;
        return S
    }
    ```

  - 入栈操作

    ```c++
    bool IsFull(Stack S){
        return(S->Top==S->MaxSize-1);
    }
    bool Push(Stack S, ElementType X){
        if(IsFull(S)){
            printf('堆栈满');
            return false
        }
        else{
            S->Data[++(S->Top)]=X;
            return true;
        }
    }
    ```

  - 出栈操作

    ```C++
    bool IsEmpty(Stack S){
    	return (S->Top==-1);
    }
    ElementType Pop(Stack S){
        if(IsEmoty(S)){
            printf('空');
            return ERRROR;
        }
        else{
            return (S->Data[(S->Top)--]);
        }
    }
    ```

  - 用一个数组实现两个堆栈

    ```C++
    typedef int Position;
    typedef struct SNode* PtrToSNode;
    struct SNode{
        ElemenType* Data;
        Position Top1;
        Position Top2;
        int MaxSize;
    }
    typedef PtrToSNode Stack;
    
    bool push(Stack S,ElementType X, int Tag){
        if(S->Top1-S->Top2==1){
            return false;
        }
        else{
            if(Tag==1)
                S->Data[++(S->Top1)]=X;
            else
                S->Data[--(S->Top2)]=X;
        return True;
        }
        
    }
    
    bool Pop(Stack S,int Tag){
        if(Tag==1){
            if(S->Top1==-1)
                return false;
            else
                return S->Data[(S->Top1)--];
        }
        else{
            if(S->Top2==MaxSize)
                return false;
            else
                return S->Data[(S->Top2)++];
        }
    }
    ```

- 堆栈的链式存储实现

  - 与单链表类似，但插入和删除只能在链栈的栈顶进行，栈顶指针就是链表的头指针

    ```C++
    typedef struct SNode* PtrToSNode;
    struct SNode{
        ElementType Data;
        PtrToSNode Next;
    };
    typedef PtrToSNode Stack;
    
    Stack CreateStack(){
        Stack S;
        S=malloc(sizeof(struct SNode))
        S->Next=Null;
        return S;
    }
    
    bool IsEmpty(Stack S){
        return(S->Next==NULL);
    }
    
    bool push(Stack S, ElementType X){
        PtrToSNode TnpCell;
        
        TmpCell=(PtrToSNode)malloc(sizeof(struct SNode));
        TmpCell->Data=X;
        TmpCell->Next=S->Next;
        S->Next=TmpCell;
        return true;
    }
    
    ElemenType Pop(Stack S){
        if(IsEmpty(S)){
            return false;
        }
        esle{
            PtrToSNode FirstCell;
            ElementType TopElem;
            FirstCell=S->Next;
            TopElem=FirstCell->Data;
            S->Next=FirstCell->Next;
            free(FirstCell);
            return TopElem;
        }
    }
    ```

  - 利用堆栈实现后缀表达式

### 3.4 队列

- 队列也是一个有序线性表，但队列的插入和删除操作是在线性表的两个不同端点进行的

- FIFO

- 队列的顺序存储实现

  - Rear(或front)%数组长度　取余运算就可以实现折返到起始单元
  - 实际使用队满的条件是(Rear+1)%数组长度==Front

  ```C++
  typedef int Position;
  typedef struct QNode* PtrToQNode;
  struct QNode{
      ElemenType* Data;
      Position Front,Rear;
      int MaxSize;
  };
  typedef PtrToQNode Queue;
  //循环队列的创建插入和删除
  Queue CreateQueue(int MaxSize){
      Queue Q=(Queue)malloc(sizeof(struct QNode));
      Q->Data=(ElementType*)malloc(MaxSize*sizeof(ElementType));
      Q->front=Q->Rear=0;
      Q->MaxSize=MaxSize;
  	return Q
  }
  ```

- 队列的链式存储实现

  - 队列的头指向链表的头节点，队列的尾指向链表的尾结点

- 总结

  堆栈的应用：表达式求值，函数调用、递归实现、深度优先搜索

  队列的应用：广度优先搜索、操作系统中竞争性资源的管理、服务资源的获得

## 第四章 树

### 4.1 

- 静态查找、动态查找

- 静态查找

  - 集合中的记录是固定的，不涉及对记录的插入和删除操作，而仅仅是按关键字查找记录

  - 顺序查找：从线性表的一端开始，向另一端逐个取出数据元素的关键字，并与要找的关键字K比较，以判断是否存在要找的数据元素。时间复杂度为O(n)

  - 二分查找：数据是有序存放的，折半查找，二分查找具有对数时间复杂度O(logn)

  - ```C++
    int binarysearch(int a[], int n, int K){
        //数组从小大排列
        int left=0,right=n;
        int mid;
        while(left<=right){
            mid=(left+right)/2;
            if(K>a[mid])
            	left=mid+1;
            elif(K<a[mid]){
                right=mid-1;
            }
            else
            	return mid;
        }
        return -1
    }
    ```

### 4.2 树的定义、表示和术语

- 树是一种非线性数据结构
- 结点的层次：规定根结点在第一层
- 结点的度：子树的个数

### 4.3 二叉树

- 定义：左子树和右子树也为二叉树

- 性质

  - 斜二叉树：已退化为线性表
  - 完美二叉树（满二叉树）
  - 完全二叉树：已有的结点与完美二叉树的编号相同，叶结点只能存在于最下层和次下层，深度为O(logN)
  - 一个二叉树第i层的最大结点树为$2^{i-1}$
  - 深度为k的二叉树有最大结点数$2^{k}-1$
  - $n_0=n_2+1$ 度为0的个数以及度为2的个数

- 二叉树的存储结构

  - 顺序存储结构：通常用于完全二叉树，先编号后存储 i/2向下取整为父节点  2i为左孩子， 2i+1为右孩子。数组下标起始单元为1

  - 二叉树的链表存储 ，每个结点由数据和左右指针三个数据成员组成

    ```C++
    tyoedef struct TNode* Position;
    typedef Position BinTree;
    struct TNode{
        ElementType Data;
        BinTree left;
        BinTree right;
    };
    ```

    






​                                                                                               