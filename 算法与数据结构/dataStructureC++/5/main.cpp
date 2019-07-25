#include<vector>
#include<typeinfo>
#include<math.h>
#include<string>
#include<fstream>
#include<iostream>


//文件的词频统计
using namespace std;

typedef string ElementType;
typedef struct LNode{
    ElementType data;
    int Count;
    struct LNode *Next;
}LNode,*List;

typedef struct TblNode{
    int TableSize;
    List Heads;
}TblNode,*HashTable;

const int MAXTABLESIZE=10000;

//得到素数
int NextPrime(int N)
{
    int i,p=(N%2)?N+2:N+1;

    while(p<MAXTABLESIZE)
    {
        for(i=(int)sqrt(p);i>2;i--)
        {
            if(!(p%i)) break;
        }
        if(i==2) break;
        else p+=2;
    }
    return p;
}

//建立散列表
//头结点是空的

HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;
    H=(HashTable)malloc(sizeof(TblNode));
    H->TableSize=NextPrime(TableSize);

    H->Heads=(List)malloc(H->TableSize*sizeof(LNode));
    for(i=0;i<H->TableSize;i++)
    {
        H->Heads[i].data=" ";
        H->Heads[i].Next=NULL;
        H->Heads[i].Count=0;
    }
    return H;

}

//散列函数:位移映射
int Hash(ElementType &Key,int TableSize)
{   
    unsigned int H=0;
    const char* key=Key.c_str();
    while(*key!='\0')
    {
        H=(H<<5)+*key++;
    }
    return H%TableSize;
}


//查找函数
List Find(HashTable H,ElementType Key)
{
    List P;
    int Pos;
    Pos=Hash(Key,H->TableSize);  //初始散列位置
    P=H->Heads[Pos].Next;   //从链表的第一个位置开始
    while(P&& P->data!=Key)
        P=P->Next;
    return P;   //此时P指向找到的结点，或者为空
}


//插入单词到哈希表中
void InsertAndCount(HashTable H, ElementType Key)
{
    List P, NewCell;
    int Pos;
    P=Find(H,Key);
    if(!P)   //未找到该单词
    {
        NewCell=(List)malloc(sizeof(LNode));
        NewCell->data=Key;
        //NewCell->data=string(Key.c_str())//出错　什么原因?  函数中创建的对象被析构的原因?
        NewCell->Count=1;
        Pos=Hash(Key,H->TableSize);
        NewCell->Next=H->Heads[Pos].Next;   //插入到头结点
        H->Heads[Pos].Next=NewCell;
        H->Heads[Pos].Count++;   //链表中增加了一个新单词
        cout<<"插入单词成功"<<endl;

    }
    else{
        P->Count++;
    }
}


//释放空间
void DestoryTable(HashTable H)
{
    int i;
    List P,Tmp;
    for(i=0;i<H->TableSize;i++)
    {
        P=H->Heads[i].Next;
        while(P)
        {
            Tmp=P->Next;
            free(Tmp);
            P=Tmp;
        }
    }
    free(H->Heads);
    free(H);
}

//显示所有单词及其词频
void Show(HashTable H)
{   
    List P;
    for(int i=0;i<H->TableSize;i++)
    {
        P=H->Heads[i].Next;
        while(P)
        {
            cout<<"单词: "<<P->data<<" ";
            cout<<"词频: "<<P->Count<<endl;
            P=P->Next;
        }
    }

}



int main()
{   
    HashTable H;
    string word;
    int TableSize=100;
    int length,wordcount=0;
    H=CreateTable(TableSize);
    cout<<"初始化表"<<endl;
    string filename="./test1.txt";
    fstream fin;
    fin.open(filename.c_str(),ios::in);
    fstream out;
    out.open("./test2.txt",ios::out);
    vector<string> v;
    //按每个单词读取文件，若按行，使用getline
    cout<<"开始读取单词"<<endl;
    if(!fin.is_open())
    {
        cout<<"第一个文件文件打开失败"<<endl;
    }
    if(!out.is_open())
    {
        cout<<"文件打开失败"<<endl;
    }
    while(fin>>word)
    {  //读取整个单词，以空格或换行符为分割
       length=word.size();
       cout<<word<<endl;
       out<<word.c_str()<<" ";  //以空格分割存储各个单词
       wordcount++;
       v.push_back(word);      //对数组v进行排序即可获得词频统计
       InsertAndCount(H,word);  //统计word出现次数
       

    }

    fin.close();
    out.close();
    cout<<"该文档中共出现"<<wordcount<<"个有效单词"<<endl;
    Show(H);  //显示所有单词
    DestoryTable(H);  //销毁

    List NewCell;
    NewCell=(List)malloc(sizeof(LNode));
    //NewCell->data=word;  //不会报错
    string temp;
    temp=string(word.c_str());
    NewCell->data=temp;       //这种方式不会出错，这种不是临时变量
    //NewCell->data=string(word.c_str());//出错　什么原因?  函数中创建的对象被析构的原因?
    //NewCell->data="sdfsfsd";   //不会报错
    //cout<<NewCell->data;
   // cout<<&(string(word.c_str()));  //临时变量，报错
     

    return 0;
}

















