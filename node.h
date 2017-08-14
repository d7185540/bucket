#ifndef NODE_H
#define NODE_H
#include<iostream>
using namespace std;
class node
{
public:
     node();
    ~node();
    int bucket[4]={0,0,0,0};
    node *son[4][4];
    node *parent=NULL;
    int a=0,b=0;
    int tasksize=4;
    void output();
    void caculate(int &a,int &b,int capacity[]);
    bool isfinish(int item[]);
    int len=0;
    int min_treelen=1000;
};

#endif // NODE_H
