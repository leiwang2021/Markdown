#include<iostream>
using namespace std;


int countRange(const int* numbers,int length,int start, int end)
{
    int count=0;
    for(int i=0;i<length;i++)
    {
        if(numbers[i]>=start && numbers[i]<=end)
            count++;
}
return count;
}


int GetDuplicate(const int* numbers,int length)
{
    if(numbers==nullptr || length<0)
        return -1;
    int start=1;
    int end=length-1;
    int middle=0;
    while(end>=start)
    {
        middle=(end-start)/2+start;
        int Count=countRange(numbers,length,start,middle);
        if(end==start)
        {
            if(Count>1)
                return start;
            else
                return -1;
        }
        if(Count>(middle-start+1))
        {
            end=middle;
        }
        else{
            start=middle+1;
        }

    }
}

void test1()
{
    cout<<"test1"<<endl;
    int len=10;
    int Num[]={1,9,2,9,2,4,3,8,7,4};
    int d=-1;
    d=GetDuplicate(Num,len);
    cout<<"d: "<<d<<endl;
}

void test2()
{
    cout<<"test2"<<endl;
    int len=10;
    int Num[]={1,2,3,4,5,6,7,8,9,10};
    int d=-1;
    d=GetDuplicate(Num,len);
    cout<<"d: "<<d<<endl;
}

void test3()
{
    cout<<"test3"<<endl;
    int len=10;
    int* Num=nullptr;
    int d=-1;
    d=GetDuplicate(Num,len);
    cout<<"d: "<<d<<endl;
}
int  main()
{
    test1();
    test2();
    test3();
    return 0;
}
