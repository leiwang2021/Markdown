#include<iostream>
#include<iterator>
#include<algorithm>
#include<deque>
using namespace std;
int main()
{

    int ia[]={0,1,2,3,4,5};
    deque<int> id(ia,ia+2);
    istream_iterator<int> inite(cin),eos;
    copy(inite,eos,inserter(id,id.begin()));
    ostream_iterator<int> out_iter(cout, " ");
    copy(id.begin(),id.end(),out_iter);
    
    return 0;
}
