#include<iostream>
#include<queue>

using namespace std;
const int queueSize=100;

struct ArcNode{
    int adjvex;
    ArcNode *Next;
};

struct VertexNode{
    int vertex;
    ArcNode *firstedge;
};

//基于邻接表结构的图的类实现
const int MaxSize=10;
int visited[MaxSize]={0};

template<class T>
class ALGraph
{
    public:
        ALGraph(T a[],int n,int e);
        ~ALGraph(){}
        void DFSTraverse(int v);
        void BFSTraverse(int v);
    private:
        VertexNode adjlist[MaxSize];  //存放顶点的数组
        int vertexNum,arcNum;
};

template<class T>
ALGraph<T>::ALGraph(T a[],int n,int e)
{
    vertexNum=n;
    arcNum=e;
    for(int i=0;i<vertexNum;i++)
    {
        adjlist[i].vertex=a[i];
        adjlist[i].firstedge=NULL;
    }
    for(int k=0;k<arcNum;k++)
    {
        int i,j;
        cout<<"请输入边的两个结点: "<<endl;
        cin>>i>>j;
        //无向图不仅要为<i,j>插入结点，还要为<j,i>插入结点
        ArcNode *s=new ArcNode;   //new的要在析构函数中释放结点
        s->adjvex=j;
        s->Next=adjlist[i].firstedge;
        adjlist[i].firstedge=s;
        ArcNode *t=new ArcNode;
        t->adjvex=i;
        t->Next=adjlist[j].firstedge;
        adjlist[j].firstedge=t;
    }
}

template<class T>
inline void ALGraph<T>::DFSTraverse(int v)
{
    cout<<adjlist[v].vertex;
    visited[v]=1;
    ArcNode *p=adjlist[v].firstedge;
    while(p!=NULL)
    {
        int j=p->adjvex;
        if(visited[j]==0)
            DFSTraverse(j);
        p=p->Next;
    }
}


template<class T>
inline void ALGraph<T>::BFSTraverse(int v)
{
    int visited[MaxSize]={0};
    queue<T> Q;
    cout<<adjlist[v].vertex;
    visited[v]=1;
    Q.push(v);
    while(!Q.empty())
    {
        v=Q.front();
        Q.pop();
        ArcNode *p=adjlist[v].firstedge;
        while(p!=NULL)
        {
            int j=p->adjvex;
            if(visited[j]==0)
            {
                cout<<adjlist[j].vertex;
                visited[j]=1;
                Q.push(j);
            }
            p=p->Next;
        }
    }
}

int main()
{
    int array[]={0,1,2,3,4,5};
    ALGraph<int> graph(array,6,9);
    cout<<"BFS: "<<endl;
    graph.BFSTraverse(3);
    cout<<endl;
    cout<<"DFS: "<<endl;
    graph.DFSTraverse(3);
    return 0;
}
