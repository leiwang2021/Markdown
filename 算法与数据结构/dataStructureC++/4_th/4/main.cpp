#include<iostream>

using namespace std;

//实现二叉搜索树

typedef int ElementType;
typedef struct Node{
    ElementType data;
    struct Node *lchild,*rchild;
}Node,*BiTree;


//插入操作，也可以作为创建

BiTree Insert(BiTree T, ElementType X)
{
    if(!T)
    {
        T=(BiTree)malloc(sizeof(Node));
        T->data=X;
        T->lchild=NULL;
        T->rchild=NULL;
    }
    else{
        if(X>T->data)
        {
            T->rchild=Insert(T->rchild,X);
        }
        else if(X<T->data)
        {
            T->lchild=Insert(T->lchild,X);
        }
    }
    return T;
}

//查找元素，递归实现
BiTree Find(BiTree T, ElementType X)
{
    if(!T)
        return NULL;
    if(X<T->data)
    {
        return Find(T->lchild,X);
    }
    else if(X>T->data)
    {
        return Find(T->rchild,X);
    }
    else
        return T;

}

//查找元素，非递归实现

BiTree Find2(BiTree T,ElementType X)
{
    while(T)
    {
        if(X<T->data)
            T=T->lchild;
        else if(X>T->data)
            T=T->rchild;
        else
            return T;
    }
    return T;
}

//查找最小元素，递归实现
ElementType FindMin(BiTree T)
{
    if(!T)
        return false;
    else{
        if(!T->lchild)
            return T->data;
        else {
            return FindMin(T->lchild);
        }
    }
}
//查找最小元素，非递归实现
ElementType FindMin2(BiTree T)
{
    if(!T)
        return false;
    while(T->lchild)
        T=T->lchild;
    return T->data;
}
//查找最大元素，递归实现
ElementType FindMax(BiTree T)
{
    if(!T)
        return false;
    else{
        if(!T->rchild)
            return T->data;
        else{
            return FindMax(T->rchild);
        }
    }
}
//查找最大元素，非递归实现
ElementType FindMax2(BiTree T)
{
    if(!T)
        return false;
    while(T->rchild)
        T=T->rchild;
    return T->data;
}

//删除操作的实现
//删除叶结点，删除只有一个孩子结点，删除有两个孩子结点

BiTree Delete(BiTree T, ElementType X) 
{
    BiTree tmp;
    if(!T)
        cout<<"未找到要删除的元素"<<endl;
    else{
        if(X<T->data)
        {
            T->lchild=Delete(T->lchild,X);
        }
        else if(X>T->data)
        {
            T->rchild=Delete(T->rchild,X);
        }
        else{
            if(T->lchild && T->rchild)
            {
                T->data=FindMin(T->rchild);            //找到右子树的最小元素填充
                T->rchild=Delete(T->rchild,T->data);   //从右子树中删除该元素
            }
            else{
                tmp=T;
                if(!T->lchild)
                    T=T->rchild;
                else
                    T=T->lchild;
                free(T);
            }
        }
    }
    return T;
}


int main()
{
    cout<<"请输入各个元素构成二叉搜索树:"<<endl;
    ElementType X;
    BiTree T=NULL;
    while(cin>>X)
      T=Insert(T,X);
    //while循环输入有Bug，有待改进
    cout<<"输入要查找的元素: ";
    cin>>X;
    cout<<"递归实现"<<endl;
    cout<<"这个元素在位置: "<<Find(T,X)<<endl;
    cout<<"非递归实现"<<endl;
    cout<<"这个元素在位置: "<<Find2(T,X)<<endl;
    cout<<"输出最小的元素"<<endl;
    cout<<"递归实现: "<<FindMin(T)<<endl;
    cout<<"非递归实现: "<<FindMin2(T)<<endl;
    cout<<"输出最大的元素"<<endl;
    cout<<"递归实现: "<<FindMax(T)<<endl;
    cout<<"非递归实现:"<<FindMax2(T)<<endl;
    cout<<"输入要删除的元素: ";
    cin>>X;
    cout<<"删除元素"<<X<<Delete(T,X);

    return 0;

}
