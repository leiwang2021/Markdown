#include<iostream>
using namespace std;

bool duplicate(int numbers[],int length,int* duplication)
{
    if(numbers==nullptr || length<=0)
        return false;
    for(int i=0;i<length;i++)
    {
        if(numbers[i]<0 || numbers[i]>length-1)
            return false;
    }
    
    for(int i=0;i<length;i++)
    {
        while(numbers[i]!=i)
        {
            if(numbers[numbers[i]]==numbers[i])
            {
                *duplication=numbers[i];
                return true;
            }
            else
            {
                int temp=numbers[i];
                numbers[i]=numbers[temp];
                numbers[temp]=temp;
            }
        }
    }
    return false;

}

void test()
{
    int len=10;
    int Num[]={0,9,1,1,2,4,5,3,6,2};
    int* d=new int;
    bool reuslt=duplicate(Num,len,d);
    cout<<*d<<endl;
    delete d;

}

void test2()
{
    int len=5;
    int Num[]={0,1,2,3,4};
    int* d=new int;
    bool result=duplicate(Num,len,d);
    cout<<*d<<endl;
    delete d;
    cout<<"result:"<<result<<endl;

}

int main()
{
    test();
    cout<<"---------------"<<endl;
    test2();
}
