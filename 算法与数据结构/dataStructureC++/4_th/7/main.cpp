#include<iostream>
#include<string.h>

using namespace std;

//采用最小堆实现哈弗曼树
typedef struct HTNode{
    char ch;  //要编码的字符
    int weight;
    struct HTNode *lchild,*rchild;
}HTNode,*HuffmanTree;

const int MINDATA=-1;
typedef struct HNode{
    HuffmanTree *data;  //最小堆元素类型为HuffmanTree
    int Size;
    int Capacity;
}HNode,*Heap;

typedef Heap MinHeap;

HuffmanTree NewHuffmanNode()
{
    HuffmanTree BST=(HuffmanTree)malloc(sizeof(HTNode));
    BST->weight=0;
    BST->ch='0';
    BST->lchild=BST->rchild=NULL;
    return BST; 
}

//先序遍历
void PreOrderTraverse(HuffmanTree BST)
{
    if(BST)
    {
        cout<<BST->weight<<" ";
		if( (BST->lchild == NULL) && (BST->rchild == NULL)){
        cout<<BST->ch<<" ";}
        PreOrderTraverse(BST->lchild);
        PreOrderTraverse(BST->rchild);
    }
}


//创建空的堆
MinHeap CreateHeap(int MaxSize){
    MinHeap H=(MinHeap)malloc(sizeof(HNode));
    H->data=(HuffmanTree*)malloc((MaxSize+1)*sizeof(HuffmanTree));
    H->Size=0;
    H->Capacity=MaxSize;
    HuffmanTree T=NewHuffmanNode();
    T->weight=MINDATA;
    H->data[0]=T;  //将第0个元素设置为哨兵
    return H;
    }

//判断是否满
bool IsFull(MinHeap H)
{
    if(H->Size==H->Capacity)
        return true;
    else
        return false;
}


//最小堆的插入
bool Insert(MinHeap H,HuffmanTree X)
{
    if(IsFull(H))
    {
        
        cout<<"最大堆已满,不能插入元素"<<endl;
        return false;

    }
    else{
        int i=++H->Size;
        for(;H->data[i/2]->weight>X->weight;i=i/2)
            H->data[i]=H->data[i/2];  //上虑X
        H->data[i]=X;
        return true;
    }

}

bool IsEmpty(MinHeap H)
{
    return(H->Size==0);
}

HuffmanTree Delete(MinHeap H)
{
    if(IsEmpty(H))
    {
        cout<<"最小堆为空，返回NULL代表空"<<endl;
        return NULL;
    }
    else{
        HuffmanTree MinItem,X;
        MinItem=H->data[1];
        int Parent,Child;
        X=H->data[H->Size--];
        for(Parent=1;Parent*2<=H->Size;Parent=Child)
        {
            Child=Parent*2;
            if(Child!=H->Size && H->data[Child]->weight>H->data[Child+1]->weight)
                Child++;   //找出子节点中较小的一个
            if(X->weight<=H->data[Child]->weight){
                break;
            }
            else
                //下虑X
                H->data[Parent]=H->data[Child];
        }

        H->data[Parent]=X;
        
        return MinItem;
    }


}


//最堆的建立，线性时间复杂度
//每一步的过程与删除操作一样
void PercDown(MinHeap H, int i)
{
    int Parent,Child;
    HuffmanTree X=H->data[i];  //取出该子树根节点的值，向下过滤
    for(Parent=i;Parent*2<=H->Size;Parent=Child)
    {
        Child=Parent*2;
        if(Child!=H->Size && H->data[Child]->weight>H->data[Child+1]->weight)
            Child++;
        if(X->weight<=H->data[Child]->weight)
            break;
        else
            H->data[Parent]=H->data[Child];
    }
    H->data[Parent]=X;
}

//调整堆中的元素，使堆满足有序性
void BuildMinHeap(MinHeap H)
{
    int i;
    for(i=H->Size/2;i>=1;i--)
        //从最后一个结点的父节点开始，直到根节点1
        PercDown(H,i);
}


//哈夫曼树构造算法
HuffmanTree Huffman(MinHeap H)
{
    int i,N;
    HuffmanTree T;
    BuildMinHeap(H);
    N=H->Size;
    for(i=1;i<N;i++)   //N-1次合并
    {
        T=NewHuffmanNode();
        T->lchild=Delete(H);   //注意此处从最小堆中删除元素的过程，顺序不一样，构建的哈夫曼树的形状也不一样
        T->rchild=Delete(H);
        T->weight=T->lchild->weight+T->rchild->weight;
        Insert(H,T);
    }
    T=Delete(H);
    return T;  //最小堆中最后一个元素即是指向哈夫曼树根节点的指针
}




/************递归进行哈夫曼编码*************/
void HuffmanCode(HuffmanTree BST,int depth)  //depth为目前编码到哈夫曼树的深度（层次） 
{
	static int code[10];  //编码空间,静态存储，在整个程序执行期间都存在 
	
	if( BST ){
		if( (BST->lchild == NULL) && (BST->rchild == NULL)){  //找到了叶结点
            cout<<BST->ch<<" "<<BST->weight<<" ";
			for(int i=0; i<depth; i++){
                cout<<code[i]<<" ";
			}
            cout<<endl;
		}else{
			code[depth] = 0;  //往左子树方向编码为0 
			HuffmanCode(BST->lchild,depth+1);
			code[depth] = 1;  //往右子树方向编码为1 
			HuffmanCode(BST->rchild,depth+1);
		}
	} 
}
  
/*******************哈夫曼解码*********************/
void HuffmanDecode(char ch[],HuffmanTree BST)  //ch[] 要解码的序列
{
	int cnt;
	int num[100];
	HuffmanTree temp;
	
	for(int i=0; i<strlen(ch); i++){
		if(ch[i] == '0'){
			num[i] = 0;
		}else{
			num[i] = 1;
		}
	}
	if( BST ){
		cnt = 0;  //计数已经解码0101串的长度 
		while(cnt < strlen(ch)){
			temp = BST;
			while((temp->lchild != NULL ) && (temp->rchild != NULL)){
				if(num[cnt] == 0){
					temp = temp->lchild;
				}else{
					temp = temp->rchild;
				}
				cnt++;
			}
			cout<<temp->ch;  //输出解码后对应结点的字符 
		}
	}
 } 




int main()
{
	int i,N;
	MinHeap h;
	HuffmanTree T,BT = NULL;
	
    cout<<"请输入叶子结点的个数: ";
    cin>>N;
	h = CreateHeap(2*N);  //创建最小堆   //N个叶子节点最终形成的哈夫曼树最多有2N-1个树结点 
    cout<<"请输入叶子结点对应的权值: "<<endl;
	for(i=1; i<=N; i++){/*最小堆元素赋值*/ 
		T = NewHuffmanNode();
        cin>>T->weight;
		h->data[++(h->Size)] = T;
	}
	char string[100]; 
    cout<<"请输入叶子结点代表的字符"<<endl;
    cin.get();   //需加上cin.get(),去除缓冲区中的换行符
    cin.getline(string,N+1);   //cin.getline()可丢弃换行符，但此输入中间不能有空格
	for(i=1; i<=h->Size; i++){/*最小堆元素赋值*/ 
		h->data[i]->ch= string[i-1];
	}
	BT = Huffman(h);  //构造哈夫曼树 
	printf("先序遍历此哈夫曼树的权值:\n"); 
	PreOrderTraverse(BT);  //先序遍历此哈夫曼树 
    cout<<"遍历完毕"<<endl;
    //debug以下部分
	HuffmanCode(BT,0);
    cout<<"请输入需要解码的二进制编码序列: "<<endl;
	char ch[100];
    cin.getline(ch,100);//getline
    cout<<"解码结果为: "<<endl;
	HuffmanDecode(ch,BT); 
    cout<<endl;
	
	return 0;
 } 
