#include<iostream>

using namespace std;

typedef int ElementType;

typedef struct AVLNode{
    ElementType data;
    struct AVLNode *lchild,*rchild;
    int height;
}AVLNode,*AVLTree;

//AVL树的插入和旋转
//
int Max(int a,int b)
{
    return a>b?a:b;

}

//求二叉树的高度算法
int GetHeight(AVLTree T)
{
    int HL, HR, MaxH;
    if(T)
    {
        HL=GetHeight(T->lchild);
        HR=GetHeight(T->rchild);
        MaxH=HL>HR?HL:HR;
        return (MaxH+1);
    }
    else return 0;
}

//左单旋
AVLTree SingleLeftRotation(AVLTree A)
{
    //顺时针旋转
    AVLTree B=A->lchild;
    A->lchild=B->rchild;
    B->rchild=A;
    A->height=Max(GetHeight(A->lchild),GetHeight(A->rchild))+1;
    B->height=Max(GetHeight(B->lchild),GetHeight(B->rchild))+1;
    return B;
}

//右单旋
AVLTree SingleRightRotation(AVLTree A)
{
    //逆时针旋转
    AVLTree B=A->rchild;
    A->rchild=B->lchild;
    B->lchild=A;
    A->height=Max(GetHeight(A->lchild),GetHeight(A->rchild))+1;
    B->height=Max(GetHeight(B->lchild),GetHeight(B->rchild))+1;
    return B;
}

//左右双旋
AVLTree DoubleLeftRightRotation(AVLTree A)
{
    //先右单旋，再左单旋
    A->lchild=SingleRightRotation(A->lchild);
    
    return SingleLeftRotation(A);

}

//右左双旋
AVLTree DoubleRightLeftRotation(AVLTree A)
{
    //先左单旋，再右单旋
    A->rchild=SingleLeftRotation(A->rchild);

    return SingleRightRotation(A);
}


//插入一个值
AVLTree Insert(AVLTree T,ElementType X)
{
    if(!T)
    {
        T=(AVLTree)malloc(sizeof(struct AVLNode));
        T->data=X;
        T->lchild=NULL;
        T->rchild=NULL;
        T->height=1;
    }
    else if(X<T->data)
        {
            T->lchild=Insert(T->lchild,X);
            if(GetHeight(T->lchild)-GetHeight(T->rchild)==2)
                if(X<T->lchild->data)
                    //左单旋
                    T=SingleLeftRotation(T);
                else
                    //左右双旋
                    T=DoubleLeftRightRotation(T);
            
        }
     else if(X>T->data)
     {
         T->rchild=Insert(T->rchild,X);
         if(GetHeight(T->rchild)-GetHeight(T->lchild)==2)
             if(X>T->rchild->data)
                 //右单旋
                 T=SingleRightRotation(T);
            else
                //右左双旋
               T=DoubleRightLeftRotation(T);
        
     }
     //等于时无需插入
     //更新树高

     T->height=Max(GetHeight(T->lchild),GetHeight(T->rchild))+1;
     return T;
    
}

void InorderTraverse(AVLTree T)
{
    if(!T)
        return;
    InorderTraverse(T->lchild);
    cout<<T->data<<' ';
    InorderTraverse(T->rchild);
}


int main()
{
    AVLTree T=NULL;
    ElementType X;
    cout<<"请输入数据建立二叉平衡树: "<<endl;
    while(cin>>X)     
        T=Insert(T,X);
    cout<<"中序遍历该树: "<<endl;
    InorderTraverse(T);
    return 0;
    
}



