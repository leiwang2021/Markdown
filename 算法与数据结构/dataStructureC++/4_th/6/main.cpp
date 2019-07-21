#include<iostream>

using namespace std;

typedef int ElementType;
const ElementType MAXDATA=10000;
typedef struct HNode{
    ElementType *data;
    int Size;
    int Capacity;
}HNode,*Heap;

typedef Heap MaxHeap;

//创建空的堆
MaxHeap CreateHeap(int MaxSize){
    MaxHeap H=(MaxHeap)malloc(sizeof(HNode));
    H->data=(ElementType*)malloc((MaxSize+1)*sizeof(ElementType));
    H->Size=0;
    H->Capacity=MaxSize;
    H->data[0]=MAXDATA;  //将第0个元素设置为哨兵
    return H;
    }

//判断是否满
bool IsFull(MaxHeap H)
{
    if(H->Size==H->Capacity)
        return true;
    else
        return false;
}


//最大堆的插入
bool Insert(MaxHeap H,ElementType X)
{
    if(IsFull(H))
    {
        
        cout<<"最大堆已满,不能插入元素"<<endl;
        return false;

    }
    else{
        int i=++H->Size;
        for(;H->data[i/2]<X;i=i/2)
            H->data[i]=H->data[i/2];  //上虑X
        H->data[i]=X;
        return true;
    }

}

bool IsEmpty(MaxHeap H)
{
    return(H->Size==0);
}

ElementType Delete(MaxHeap H)
{
    if(IsEmpty(H))
    {
        cout<<"最大堆为空，返回-1代表空"<<endl;
        return -1;
    }
    else{
        ElementType MaxItem,X;
        MaxItem=H->data[1];
        int Parent,Child;
        X=H->data[H->Size--];
        for(Parent=1;Parent*2<=H->Size;Parent=Child)
        {
            Child=Parent*2;
            if(Child!=H->Size && H->data[Child]<H->data[Child+1])
                Child++;   //找出子节点中较大的一个
            if(X>=H->data[Child]){
                break;
            }
            else
                //下虑X
                H->data[Parent]=H->data[Child];
        }

        H->data[Parent]=X;
        
        return MaxItem;
    }


}


//最大堆的建立，线性时间复杂度
//每一步的过程与删除操作一样
void PercDown(MaxHeap H, int i)
{
    int Parent,Child;
    ElementType X=H->data[i];  //取出该子树根节点的值，向下过滤
    for(Parent=i;Parent*2<=H->Size;Parent=Child)
    {
        Child=Parent*2;
        if(Child!=H->Size && H->data[Child]<H->data[Child+1])
            Child++;
        if(X>=H->data[Child])
            break;
        else
            H->data[Parent]=H->data[Child];
    }
    H->data[Parent]=X;
}

//调整堆中的元素，使堆满足有序性
void BuildMaxHeap(MaxHeap H)
{
    int i;
    for(i=H->Size/2;i>=1;i--)
        //从最后一个结点的父节点开始，直到根节点1
        PercDown(H,i);
}

int main()
{
    cout<<"建立最大堆: "<<endl;
    cout<<"输入最大堆的大小: ";
    int Size;
    cin>>Size;
    cout<<"建立一个空的最大堆"<<endl;
    MaxHeap H=CreateHeap(Size);
    cout<<"给堆中输入元素: "<<endl;
    for(int i=1;i<=Size;i++)
    {
        cin>>H->data[i];
        H->Size++;
    }
    cout<<"建立最大堆，调整有序性: "<<endl;
    BuildMaxHeap(H);
    cout<<"取走最大堆的元素: ";
    for(int i=1;i<=Size;i++)
    {
        cout<<Delete(H)<<" ";
    }
    cout<<"输入插入一个元素: "<<endl;
    ElementType X;
    cin>>X;
    cout<<Insert(H,X)<<endl;
    cout<<"再插入一个元素: "<<endl;
    cin>>X;
    cout<<Insert(H,X)<<endl;
    cout<<"取走最大堆的元素: ";
    cout<<"第1: "<<Delete(H)<<endl;
    cout<<"第2: "<<Delete(H)<<endl;
    //此处for循环不能写为H->Size
    /*for(int i=1;i<=H->Size;i++)
    {
        cout<<Delete(H)<<" ";
    }*/
    
    
    return 0;


}
