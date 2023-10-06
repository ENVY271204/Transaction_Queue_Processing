#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
    public:
    unsigned int AccNo;
    int balance;
    Node* next;
    Node()
    {
        balance = 1000;
        next = nullptr;
    }
    Node(unsigned int Acc)
    {
        AccNo = Acc;
        balance = 1000;
        next = nullptr;
    }
    Node(unsigned int Acc, int bal)
    {
        AccNo = Acc;
        balance = bal;
        next = nullptr;
    }
};
class Dnode
{
    public:
    unsigned int AccNo;
    Dnode* prev;
    Dnode* next;
    int transaction; //Will always add to balance
    Dnode()
    {
        prev = nullptr;
        next = nullptr;
        transaction=0;
    }
    Dnode(int val)
    {
        prev = nullptr;
        next = nullptr;
        transaction=val;
    }
    Dnode(unsigned int Acc, int val)
    {
        prev = nullptr;
        next = nullptr;
        AccNo = Acc;
        transaction=val;
    }
};
class SLL
{
    Node* first;
    Node* last;
    int len;
    public:
    SLL()
    {
        first= nullptr;
        last = nullptr;
        len=0;
    }
    void insertEnd(unsigned int Acc)
    {
        Node* add = new Node(Acc);
        len++;
        if(first==nullptr)
        {
            first = add;
            last = add;
        }
        else if(first == last)
        {
            first->next = add;
            last = add;
        }
        else
        {
            last -> next =add;
            last =add;
        }
    }
    void updateBal(unsigned int acc, int trans)
    {
        Node* temp = first;
        for(int i=0;i<len;i++)
        {
            if(acc==temp->AccNo)
            {
                temp->balance = temp->balance + trans;
                break;
            }
            temp = temp->next;
        }
    }
    void printGX(int x)
    {
        if(len==0) return;
        Node* temp = first;
        int ct=0;
        for(int i=0;i<len;i++)
        {
            if(temp->balance>=x)
            {
                ct++;
            }
            temp= temp->next;
        }
        cout<<ct<<endl;
    }
    void highestBal()
    {
        if(len==0) return;
        Node* temp = first;
        int mx=-1000000000;
        for(int i=0;i<len;i++)
        {
            if(temp->balance>=mx)
            {
                mx = temp->balance;
            }
            temp= temp->next;
        }
        temp = first;
        vector<int> v;
        for(int i=0;i<len;i++)
        {
            if(temp->balance==mx)
            {
                v.push_back(temp->AccNo);
            }
            temp= temp->next;
        }
        sort(v.begin(),v.end());
        for(int i=0;i<v.size();i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }
    void printX(unsigned int x)
    {
        if(len==0) return;
        Node* temp = first;
        for(int i=0;i<len;i++)
        {
            if(temp->AccNo==x)
            {
                cout<<temp->balance<<endl;
                break;
            }
            temp= temp->next;
        }
    }
    friend class DLL;
};
class DLL
{
    Dnode* head;
    Dnode* tail;
    Dnode* curr;
    public:
    DLL()
    {
        head = new Dnode();
        tail = new Dnode();
        head->next =tail;
        tail->prev = head;
        curr = head;
    }
    void insertEnd(unsigned int Acc, char ch, int val)
    {
        Dnode* add;
        if(ch=='W') add = new Dnode(Acc,(-1*val));
        else add = new Dnode(Acc, val);
        if(head->next==tail)
        {
            head->next =add;
            add->prev =head;
            add->next = tail;
            tail->prev = add;
        }
        else
        {
            Dnode*temp = tail->prev;
            temp->next = add;
            add->prev = temp;
            add->next = tail;
            tail ->prev = add;
        }
    }
    void processNext(int X, SLL& list)
    {
        if(curr == tail)
                return;
        for(int i=0;i<X;i++)
        {
            curr = curr->next;
            if(curr == tail)
                break;
            list.updateBal(curr->AccNo, curr->transaction);
        }
    }
    void processPrev(int X,SLL& list)
    {
        if(curr==tail) curr= curr->prev;
        if(curr==head)
            return;
        for(int i=0;i<X;i++)
        {
            if(curr == head)
                break;
            list.updateBal(curr->AccNo, (-1*(curr->transaction)));
            curr = curr->prev;
        }
    }
    void insertTransK(int K,unsigned int Acc, char ch, int val, SLL& list)
    {
        Dnode* temp = head;
        int flag = 0;
        for(int i=0;i<K;i++)
        {
            if(temp == curr) flag=1;
            temp= temp->next;
            if(temp==tail)
            {
                return;
            }
        }
        if(temp == curr) flag=1;
        Dnode* add;
        if(ch=='W') add = new Dnode(Acc,(-1*val));
        if(ch=='D') add = new Dnode(Acc, val);
        Dnode* temp1 = temp->next;
        temp->next = add;
        add->prev = temp;
        add->next = temp1;
        temp1->prev = add;
        if(flag==0) list.updateBal(Acc,add->transaction);
    }
    void processAll(SLL& list)
    {
        if(curr==tail) return;
        curr = curr->next;
        while(curr!=tail)
        {
            list.updateBal(curr->AccNo, curr->transaction);
            curr=curr->next;
        }
    }
    void processUntil(unsigned int AccNo)
    {
        if(curr==head) return;
        Dnode* temp = head;
        temp = temp->next;
        while(temp!=curr)
        {
            if(temp->AccNo==AccNo)
            {
               if(temp->transaction>=0)
                {
                    cout<<AccNo<<" D "<<temp->transaction<<endl;
                }
                else
                {
                    cout<<AccNo<<" W "<<(-1*temp->transaction)<<endl;
                }
            }
            temp = temp->next;
        }
        if(temp!=tail)
        {
            if(temp->AccNo==AccNo)
            {
               if(temp->transaction>=0)
                {
                    cout<<AccNo<<" D "<<curr->transaction<<endl;
                }
                else
                {
                    cout<<AccNo<<" W "<<(-1*curr->transaction)<<endl;
                }    
            }
        }
    }
    void deleteDnode(Dnode* del)
    {
        Dnode* delprev = del->prev;
        Dnode* delnext = del->next;
        delprev->next = delnext;
        delnext->prev = delprev;
        delete del;
    }
    void deleteM(unsigned int A, int M, SLL& list)
    {
        Dnode* temp = curr;
        if(M>0)
        {
            if(temp==tail)
                return;
            while(M>0)
            {
                temp=temp->next;
                if(temp==tail) return;
                if(temp->AccNo==A)
                {
                    Dnode* prev = temp->prev;
                    deleteDnode(temp);
                    temp = prev;
                    M--;
                }
            }
        }
        else if(M<0)
        {
            if(temp==head)
                return;
            while(M<0)
            {
                temp=temp->prev;
                if(temp==head) return;
                if(temp->AccNo==A)
                {
                    Dnode* next = temp->next;
                    list.updateBal(A,(-1)* temp->transaction);
                    deleteDnode(temp);
                    temp = next;
                    M++;
                }
            }            
        }
    }
};
int main() {
    int n;
    cin>>n;
    SLL list;
    DLL dlist;
    for(int i=0;i<n;i++)
    {
        unsigned int acc;
        cin>>acc;
        list.insertEnd(acc);
    }
    int nt;
    cin>>nt;
    for(int i=0;i<nt;i++)
    {
        unsigned int acc;
        char ch;
        int trans;
        cin>>acc>>ch>>trans;
        dlist.insertEnd(acc,ch,trans);
    }
    while(1)
    {
        string s;
        cin>>s;
        if(s[0]=='E') break;
        if(s[0]=='F')
        {
            int x;
            cin>>x;
            dlist.processNext(x,list);
        }
        if(s[0]=='R')
        {
            int x;
            cin>>x;
            dlist.processPrev(x,list);
        }
        if(s[0]=='C')
        {
            dlist.processAll(list);
        }
        if(s[0]=='S')
        {
            unsigned int y;
            cin>>y;
            dlist.processUntil(y);
        }
        if(s[0]=='G')
        {
            int x;
            cin>>x;
            list.printGX(x);
        }
        if(s[0]=='M')
        {
            list.highestBal();
        }
        if(s[0]=='V')
        {
            int x;
            cin>>x;
            list.printX(x);
        }
        if(s[0]=='I')
        {
            unsigned int acc;
            char ch;
            int trans;
            cin>>acc>>ch>>trans;
            int k;
            cin>>k;
            dlist.insertTransK(k,acc,ch,trans,list);
        }
        if(s[0]=='D')
        {
            unsigned int acc;
            int M;
            cin>>acc>>M;
            dlist.deleteM(acc, M, list);
        }
    }
    return 0;
}

