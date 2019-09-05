//仿函数
#include<iostream>
using namespace std;

template<class T>
struct plus1{
    T operator()(const T & x, const T & y) const {
        return x+y;
    }

};
template<class T>
struct minus1{
    T operator()(const T& x, const T&y) const{
        return x-y;
    }
};

int main()
{   //产生仿函数对象
    plus1<int> plusobj;  
    minus1<int> minusobj;

    //使用仿函数
    cout<<plusobj(3,5)<<endl;
    cout<<minusobj(3,5)<<endl;

    //以下直接产生仿函数的临时对象，并调用之
    cout<<plus1<int>()(43,50)<<endl;
    cout<<minus1<int>()(43,50)<<endl;
    return 0;
}
