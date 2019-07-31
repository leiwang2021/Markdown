//归并排序
#include<iostream>

using namespace std;
typedef int ElementType;

void Merge(ElementType A[],ElementType TmpA[],int L,int R,int RightEnd)
{
    //将两个有序的序列合并成一个有序序列
    int LeftEnd,NumElements,Tmp;
    int i;
    LeftEnd=R-1;
    Tmp=L;
    NumElements=RightEnd-L+1;

    while(L<=LeftEnd && R<=RightEnd)
    {
        if(A[L]<=A[R])
            TmpA[Tmp++]=A[L++];
        else
            TmpA[Tmp++]=A[R++];
    }
    while(L<=LeftEnd)
        TmpA[Tmp++]=A[L++];
    while(R<=RightEnd)
        TmpA[Tmp++]=A[R++];
    for(i=0;i<NumElements;i++,RightEnd--)
        A[RightEnd]=TmpA[RightEnd];
}


void Msort(ElementType A[], ElementType TmpA[], int L,int RightEnd)
{
    int Center;
    if(L<RightEnd)
    {
        Center=(L+RightEnd)/2;
        Msort(A,TmpA,L,Center);   //递归解决左边
        Msort(A,TmpA,Center+1,RightEnd);  //递归解决右边
        Merge(A,TmpA,L,Center+1,RightEnd); //合并两段有序序列
    }
}

void MergeSort(ElementType A[],int N)
{
    ElementType *TmpA;
    TmpA=(ElementType*)malloc(N*sizeof(ElementType));

    if(TmpA!=NULL)
    {
        Msort(A,TmpA,0,N-1);
        free(TmpA);
    }
    else
        cout<<"存储空间不足"<<endl;
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
    cout<<"归并排序法结果"<<endl;
    MergeSort(A,N);
    for(int i=0;i<N;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;
    return 0;
}




