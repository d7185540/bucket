#include "node.h"

node::node()
{
  for(int a=0;a<tasksize;a++)
  {
      for(int b=0;b<tasksize;b++)
      {
          son[a][b]=NULL;
      }
  }
}


void node::output()
{
    for(int a=0;a<tasksize;a++)
    {
        cout<<bucket[a]<<" ";
    }
    cout<<endl;
}


void node::caculate(int &a, int &b, int capacity[])
{
    if(bucket[a]>capacity[b]-bucket[b])
    {
        bucket[a]-=capacity[b]-bucket[b];
        bucket[b]=capacity[b];
    }
    else
    {
        bucket[b]+=bucket[a];
        bucket[a]=0;
    }
}

 bool node::isfinish(int item[])
{
    for(int a=0;a<tasksize;a++)
    {
        if(item[a]!=bucket[a])
            return false;
    }
    return true;
}


node::~node()
{
   if(parent!=NULL)
   this->parent->son[a][b]=NULL;
}
