#include<iostream>
using namespace std;
class A{
    public:
        virtual void test(){ cout<<"A"<<endl; }
};

class B:public A
{
    
    public:
    void test()
    {
        cout<<"B"<<endl;
    }
    virtual void test2()
    {}
};

int main()
{
    A a;
    B b;
    A* c=&b;
    A* d=&a;
    d->test();
    c->test();
    cout<<sizeof(a)<<endl;
    cout<<sizeof(b)<<endl;
    return 0;
}
