//利用快排的思想解决第K大数问题
#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

int FindK(vector<int> & S, int left, int right, int K)
{
    //先将其分为两边
    int e=S[left];
    int L=left, R=right;
    while(1)
    {
        while((left<=right)&&(e<=S[left]))
            left++;
        while((left<right)&&(e>S[right]))
            right--;
        if(left<right)
            swap(S[left],S[right]);
        else
            break;

    }
    swap(S[left-1],S[L]); //e在left-1的位置，其左边为S1,右边为S2
    if(left-1-L>=K)
        return FindK(S,L,left-2,K);
    else if(left-1-L<K-1)
        return FindK(S,left,R,K-(left-1-L)-1);
    else 
        return e;


}


int main()
{
    vector<int> S;
    int n;
    int K;
    cout<<"请输入K值: ";
    cin>>K;
    cout<<"请输入一个数组:"<<endl;
    while(cin>>n)
    {
        S.push_back(n);
    }
    cout<<K<<endl;
    int N=S.size();
    clock_t start,end;
    start=clock();
    int Max=FindK(S,0,N-1,K);
    cout<<"第K大数为"<<Max<<endl;
    end=clock();
    cout<<"Run time is: "<<double(end-start)/CLOCKS_PER_SEC<<" s"<<endl; 
    return 0;
    
}
