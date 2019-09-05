//二维数组中的查找
#include<iostream>
#include<vector>
using namespace std;

bool Find(int target,vector<vector<int>> array)
{
    //int m=array.size();  //行数
    //int n=array[0].size(); //列数
    int row=0;
    int column=array[0].size()-1;
    int temp=0;
    while(row<=array.size()-1 &&  column>=0)
    {
      temp=array[row][column];
      if(target>temp)
          row++;
      else if(target<temp)
          column--;
      else
          return true;

    }
    return false;
}

void test()
{
    vector<vector<int>> arrays={{1,2,3,4,5},{2,3,4,5,6},{3,4,5,6,7},{4,5,6,7,8}};
    int target=1;
    int result=-1;
    result=Find(target,arrays);
    cout<<"target: "<<target<<endl;
    cout<<"Find Result: "<<result<<endl;
    target=8;
    result=Find(target,arrays);
    cout<<"target: "<<target<<endl;
    cout<<"Find Result: "<<result<<endl;
    target=4;
    result=Find(target,arrays);
    cout<<"target: "<<target<<endl;
    cout<<"Find Result: "<<result<<endl;

}


void test1()
{
    vector<vector<int>> arrays={{1,2,3,4,5},{2,3,4,5,7},{3,4,5,7,8},{4,5,7,9,10}};
    int target=0;
    int result=-1;
    result=Find(target,arrays);
    cout<<"target: "<<target<<endl;
    cout<<"Find Result: "<<result<<endl;
    target=11;
    result=Find(target,arrays);
    cout<<"target: "<<target<<endl;
    cout<<"Find Result: "<<result<<endl;
    target=6;
    result=Find(target,arrays);
    cout<<"target: "<<target<<endl;
    cout<<"Find Result: "<<result<<endl;

}

int main()
{
    test();
    test1();
    return 0;
}
