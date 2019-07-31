//插入排序
//简单插入排序
#include<iostream>
using namespace std;
typedef int ElementType;


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

//希尔排序，每次交换相隔一定距离的元素
void ShellSort(ElementType A[],int N)
{
    //用Sedgewick增量序列,最后一个增量序列排序即为简单插入排序
    int Si,D,P,i;
    ElementType Tmp;
    int Sedgewick[]={929,505,209,109,41,19,5,1,0};
    for(Si=0;Sedgewick[Si]>=N;Si++)
        ; //增量序列的长度不能大于待排序的长度
    for(D=Sedgewick[Si];D>0;D=Sedgewick[++Si])
    {
        for(P=D;P<N;P++)
        {
            //插入排序
            Tmp=A[P];
            for(i=P;i>=D && A[i-D]>Tmp;i-=D)
            {
                A[i]=A[i-D];
            }
            A[i]=Tmp;
        }
    }
}


int main()
{
    cout<<"请输入数组的个数N: "<<endl;
    int N;
    cin>>N;
    ElementType A[100];
    cout<<"请输入数组的元素: "<<endl;
    for(int i=0;i<N;i++)
    {
        cin>>A[i];
    }
    cout<<"简单插入排序: "<<endl;
    //InsertionSort(A,N);
    for(int i=0;i<N;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;
    cout<<"希尔排序: "<<endl;
    ShellSort(A,N);
    for(int i=0;i<N;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;
   
    return 0;
}
