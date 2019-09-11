#include<iostream>

using namespace std;

class Test{
    public:
        virtual int test(int m){return m;}
    private:
        int a;
       char b;
        char* c;
};

struct p1{
    int i;
    char* j;
    char m;
};

int main()
{
    Test A;
    cout<<sizeof(A)<<endl;  //填充后为24字节,按偏移量计算填充
    p1 p;
    cout<<sizeof(p)<<endl;  //填充后为24字节，按偏移量计算填充
}
