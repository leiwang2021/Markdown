#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

//采用分而治之法计算最大子列和
int maxSum1(vector<int> & se, int left,int right)
{
    //递归停止条件
    if(left==right)
    {
        if(se[left]<0)
            return 0;
        else
            return se[left];
    }

    int maxLeftsum,maxRightsum;
    int center=(left+right)/2;
    //首先计算左子列和右子列的最大和
    maxLeftsum=maxSum1(se,left,center);
    maxRightsum=maxSum1(se,center+1,right);

    //计算横跨左子列和右子列的最大和
    int maxLeftBordersum=0,maxRightBordersum=0;
    int Thissum=0;

    for(int i=center;i>=left;i--)
    {
        Thissum+=se[i];
        if(Thissum>maxLeftBordersum)
            maxLeftBordersum=Thissum;
        
    }
    Thissum=0;
    for(int i=center+1;i<=right;i++)
    {
        Thissum+=se[i];
        if(Thissum>maxRightBordersum)
            maxRightBordersum=Thissum;

    }
    int maxBorder=maxLeftBordersum+maxRightBordersum;
    if(maxLeftsum>maxRightsum)
    {
        if(maxLeftsum>maxBorder)
            return maxLeftsum;
        else 
            return maxBorder;
    }
    else
    {
        if(maxRightsum>maxBorder)
            return maxRightsum;
        else
            return maxBorder;
    }

}

//在线计算最大子列和
int maxSum2(vector<int> se,int left,int right) 
{
    //在线计算方法，若有子列和小于０，则丢弃
    int Thissum=0,maxSum=0;
    for(int i=left;i<=right;i++)
    {
        Thissum+=se[i];
        if(Thissum>maxSum)
            maxSum=Thissum;
        if(Thissum<0)
            Thissum=0;
    }
    return maxSum;
}



int main()
{
    int n;
    vector<int> sequence;
    cout<<"请输入各个元素,以ctrl+D结束"<<endl;
    while(cin>>n)
    {
        sequence.push_back(n);
    }
    int max_sum1,max_sum2;
    clock_t start,end;
    int N=sequence.size();
    start=clock();
    max_sum1=maxSum1(sequence,0,N);
    end=clock();
    cout<<"The max_sum1 is: "<<max_sum1<<endl;
    cout<<"Run time is:"<<double(end-start)/CLOCKS_PER_SEC<<" s"<<endl;

    start=clock();
    max_sum2=maxSum2(sequence,0,N);
    end=clock();
    cout<<"The max_sum2 is: "<<max_sum2<<endl;
    cout<<"Run time is:"<<double(end-start)/CLOCKS_PER_SEC<<" s"<<endl;

    return 0;
    
        
   
}
