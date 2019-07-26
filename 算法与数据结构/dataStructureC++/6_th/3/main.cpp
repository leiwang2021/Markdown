//图的存储结构实现
#include<iostream>
#include<queue>

using namespace std;

//边表顶点
struct ArcNode{
    int adjvex;
    ArcNode *Next;
};

//顶点表
template<class T>
struct VertexNode{
    T vertex;
    ArcNode *firstedge;
};

//邻接矩阵实现
//基于邻接矩阵存储结构的图的类的实现
const int MaxSize=10;
int visited[MaxSize]={0};  //顶点是否被访问的标记

template<class T>
class MGraph{
    public:
        MGraph(T a[],int n, int e);  //构造函数建立具有N个点e条边的图
        ~MGraph(){}
        void DFSTraverse(int v);   //深度　优先遍历
        void BFSTraverse(int v);   //广度优先遍历
    private:
        T vertex[MaxSize];  //存放顶点
        int arc[MaxSize][MaxSize];  //存放边
        int vertexNum,arcNum;  //顶点数和边数
};


template<class T>
inline MGraph<T>::MGraph(T a[],int n,int e)
{
    vertexNum=n;
    arcNum=e;
    for(int i=0;i<vertexNum;i++)
        vertex[i]=a[i];
    for(int i=0;i<vertexNum;i++)
        for(int j=0;j<vertexNum;j++)
            arc[i][j]=0;
    for(int k=0;k<arcNum;k++)
    {
        int i,j;
        cout<<"请输入边的两个顶点: "<<endl;
        cin>>i>>j;
        arc[i][j]=1;
        arc[j][i]=1;
    }
}

//DFS
template<class T>
inline void MGraph<T>::DFSTraverse(int v)
{
    cout<<vertex[v]<<" ";
    visited[v]=1;
    for(int j=0;j<vertexNum;j++)
    {
        if(arc[v][j] && visited[j]==0)
            //沿一个邻接点完全遍历后，再遍历第2、3...个邻接点
            DFSTraverse(j);
    }
}

//BFS
template<class T>
inline void MGraph<T>::BFSTraverse(int v)
{
    int visited[MaxSize]={0};
    queue<T> Q;
    cout<<vertex[v]<<" ";
    visited[v]=1;
    Q.push(v);    //被访问顶点入队
    while(!Q.empty())
    {
        v=Q.front();  //出队
        Q.pop();
        for(int j=0;j<vertexNum;j++)
        {
            //先遍历所有邻接点，再沿邻接点遍历第2圈的所有邻接点
            if(arc[v][j]==1 && visited[j]==0)
            {
                cout<<vertex[j]<<" ";
                visited[j]=1;
                Q.push(j);   //邻接点入队
            }
        }
    }
}


int main()
{
    int array[]={1,2,3,4,5,6};
    MGraph<int> graph(array,6,9);
    cout<<"BFS: "<<endl;
    graph.BFSTraverse(0);
    cout<<"DFS: "<<endl;
    graph.DFSTraverse(0);
    return 0;
}



