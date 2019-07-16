//单链表反转的问题
#include<iostream>
using namespace std;

typedef struct ListNode
{
    ListNode* next;
    int val;
    ListNode():val(0),next(NULL){}
}* LinkList;


LinkList CreateLinkList(int cnt)
{
    LinkList head=(LinkList)(malloc(sizeof(ListNode)));
    head->next=NULL;
    head->val=-1;
    LinkList q,p;
    q=head;
    while(cnt)
    {
        p=new ListNode;
        p->val=cnt;
        q->next=p;
        q=p;
        cnt--;
    }
    return head;
}


LinkList ReverseLinkList(LinkList L)
{
    LinkList Old_head,New_head,tmp;
    Old_head=L;
    New_head=NULL;
    while(Old_head!=NULL)
    {
        tmp=Old_head->next;
        Old_head->next=New_head;
        New_head=Old_head;
        Old_head=tmp;

    }
    L=New_head;
    return L;
}



int main()
{
    int K;
    cout<<"请输入链表的长度: ";
    cin>>K;
    LinkList lk;
    lk=CreateLinkList(K);
    LinkList p=lk;
    while(p!=NULL)
    {
        cout<<p->val<<endl;
        p=p->next;
    }

    cout<<"反转链表------------"<<endl;
    lk=ReverseLinkList(lk);
    p=lk;
    while(p!=NULL)
    {
        cout<<p->val<<endl;
        p=p->next;
    }
    return 0;
}
