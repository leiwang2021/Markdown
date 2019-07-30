#include<iostream>

using namespace std;

typedef int ElementType;

void Swap(ElementType *a,ElementType *b)
{
    ElementType t=*a;
    *a=*b;
    *b=t;
}

//简单选择排序

void SimpleSelectionSort(ElementType A[],int N)
{
    int i,j,min;
    for(i=0;i<N-1;i++)
    {
        min=i;
        for(j=i+1;j<N;j++)
        {
            if(A[j]<A[min])
                min=j;
        }
        Swap(&A[i],&A[min]);
    }
}


//堆排序
//堆的数据从第0个开始存放
void PercDown(ElementType A[],int p,int N)
{
    //将N个元素的数组以A[p]为根的子堆调整为最大堆
    int parent,child;
    ElementType X;
    X=A[p];
    for(parent=p;(parent*2+1)<N;parent=child)
    {
        child=parent*2+1;
        if((child!=N-1)&&(A[child]<A[child+1]))
            child++;
        if(X>A[child])
            break;
        else
            A[parent]=A[child];
    }
    A[parent]=X;
}

void HeapSort(ElementType A[],int N)
{
    int i;
    for(i=N/2-1;i>=0;i--)
        PercDown(A,i,N); //建立最大堆

    for(i=N-1;i>0;i--)
    {
        Swap(&A[0],&A[i]);
        PercDown(A,0,i);
    }
}

int main()
{
    int N;
    cout<<"请输入N:"<<endl;
    cin>>N;
    ElementType A[10]={0};
    cout<<"请输入数组的值: "<<endl;
    for(int i=0;i<N;i++)
    {
        cin>>A[i];
    }
    /*cout<<"简单选择排序结果: "<<endl;
    SimpleSelectionSort(A,N);
    for(int i=0;i<N;i++)
    {
        cout<<A[i]<<endl;
    }*/
    cout<<"堆排序结果: "<<endl;
    HeapSort(A,N);
    for(int i=0;i<N;i++)
    {
        cout<<A[i]<<endl;
    }
 
    return 0;

}
