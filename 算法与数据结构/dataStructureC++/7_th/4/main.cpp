//交换排序
#include<iostream>
using namespace std;

typedef int ElementType;

void Swap(ElementType *a,ElementType *b)
{
    ElementType t;
    t=*a;
    *a=*b;
    *b=t;
}

//冒泡排序
void BubbleSort(ElementType A[],int N)
{
    int P,i;
    bool flag;
    for(P=N-1;P>=0;P--)
    {
        flag=false;
        for(i=0;i<P;i++)  //一趟冒泡
        {
            //每次循环找出最大元素，被交换到最右端 
            if(A[i]>A[i+1])
            {
                Swap(&A[i],&A[i+1]);
                flag=true;
            }
        }
        if(flag==false)
            break;       //若全程无交换，则有序，跳出
    }
}


//快速排序,使用分治法
void InsertionSort(ElementType A[],int N)
{
    //简单插入排序
    int P,i;
    ElementType Tmp;
    for(P=1;P<N;P++)
    {
        Tmp=A[P];   //取出未排序序列的第一个元素
        for(i=P;i>0 && A[i-1]>Tmp;i--)
        {
            A[i]=A[i-1];
        }
        A[i]=Tmp;

    }
}


//选取基准
ElementType Median3(ElementType A[],int left,int right)
{
    int center=(left+right)/2;
    if(A[left]>A[center])
        Swap(&A[left],&A[center]);
    if(A[left]>A[right])
        Swap(&A[left],&A[right]);
    if(A[center]>A[right])
        Swap(&A[center],&A[right]);
    Swap(&A[center],&A[right-1]);  //将基准藏到最右边

    return A[right-1];

}

void Qsort(ElementType A[],int left,int right)
{
    int Pivot,cutoff=2,low,high;
    if(cutoff<=right-left)  //如果序列元素足够多，进入快排
    {
        Pivot=Median3(A,left,right);
        low=left;
        high=right-1;
        while(1) //将序列中比基准大的移到右边，比基准小的移到左边
        {
            while(A[++low]<Pivot);
            while(A[--high]>Pivot);
            if(low<high)
                Swap(&A[low],&A[high]);
            else
                break;  //一趟结束
        }
        Swap(&A[low],&A[right-1]);   //将基准交换到正确的位置
        cout<<"采用快速排序"<<endl;
        Qsort(A,left,low-1);  //递归解决左边
        Qsort(A,low+1,right); //递归解决右边
    }
    else
    {
      
        InsertionSort(A+left,right-left+1);  //元素太少，用简单排序
        cout<<"采用简单排序"<<endl;
    }
}

void QuickSort(ElementType A[],int N)
{
    Qsort(A,0,N-1);  //统一接口
}


int main()
{
    cout<<"请输入元素个数N:"<<endl;
    int N;
    cin>>N;
    ElementType A[100];
    cout<<"请输入数组的元素:"<<endl;
    for(int i=0;i<N;i++)
    {
        cin>>A[i];
    }
    cout<<"冒泡排序法结果"<<endl;
    //BubbleSort(A,N);
    for(int i=0;i<N;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;
    cout<<"快速排序结果: "<<endl;
    QuickSort(A,N);
    for(int i=0;i<N;i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}




