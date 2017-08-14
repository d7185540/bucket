#include "tree.h"

tree::tree(int a)
{
   this->num=a;
}

bool tree::isrepeat(node *p)
{
        node *q;
        q=p->parent;
        while(q!=NULL)
        {
            for(int a=0;a<tasksize;a++)
            {
                if(p->bucket[a]!=q->bucket[a])
                {
                    break;
                }
                if(a==tasksize-1)
                {
                    return true;
                }
            }
            q=q->parent;
        }
        return false;

}
void tree::output(node *p)
{
    if(p==head)
    {
       p->output();
    }
    else
    {
       output(p->parent);
       p->output();
    }

}
void tree::tree_start(node *p)
{
    if(p==NULL)
    {
//        node *i=new node();
//        p=head=i;
//        head->parent=NULL;
//        i->bucket[0]=21,i->bucket[1]=0,i->bucket[2]=0,i->bucket[3]=0;
//        i->len=1;
        cout<<"开始指针不能为NULL";
        exit(0);
    }
    for(int a=0;a<4;a++)
        for(int b=0;b<4;b++)
        {
            if(a!=b&&p->bucket[a]!=0&&p->bucket[b]!=rongliang[b])
            {
                node g=*p;
                node *q=&g;
                p->son[a][b]=q;
                p->son[a][b]->parent=p;
                p->son[a][b]->caculate(a,b,rongliang);


                p->son[a][b]->len++;


                p->son[a][b]->a=a;
                p->son[a][b]->b=b;
                if(p->son[a][b]->isfinish(item)==false)
                {

                    if(p->son[a][b]->len<=min_treelen)
                   {

                        if(isrepeat(p->son[a][b])==false)
                          tree_start(p->son[a][b]);
                   }

                }
                else
                {

                        if(min_treelen>p->son[a][b]->len)
                        {
                            min_treelen=p->son[a][b]->len;

                            //output(p->son[a][b]);
                            save_treepath(p->son[a][b]);
                          //  cout<<"目前最小次数为"<<min_treelen<<endl;
                            emit this->send_mintreelen(min_treelen,num);


                        }

                }
            }
        }
}


void tree::init(vector<vector<int> > data)
{
    if(data.size()>=0)
    {
    for(int a=0;a<data.size();a++)
    {
     if(a==0)
     {
         head=new node();
         startnode=head;
         for(int b=0;b<tasksize;b++)
             head->bucket[b]=data[a][b];
         head->len=a+1;
     }
     else
     {
         startnode->son[0][0]=new node();
         startnode->son[0][0]->parent=startnode;
         startnode->son[0][0]->len=a+1;
         for(int b=0;b<tasksize;b++)
             startnode->son[0][0]->bucket[b]=data[a][b];
         startnode=startnode->son[0][0];

     }
    }

   //  output(startnode);
    }
    else
    {
        startnode=head;
        head=NULL;
    }

}


void tree::clean_tree(node *p)
{

    if(p!=NULL)
    {

        for(int a=0;a<tasksize;a++)
        {
            for(int b=0;b<tasksize;b++)
            {
                if(a!=b)
                {
                if(p->son[a][b]!=NULL)
                {

                    clean_tree(p->son[a][b]);
                }
                }
            }
        }
        delete(p);
        if(p==head)
            head=NULL;

    }

}

void tree::receivetask(vector<vector<int> > data, int tree_minlen, int num)
{
    if(num==this->num)
    {
    tree_minlen=this->min_treelen;
    this->init(data);
    this->tree_start(this->startnode);
   // cout<<num<<"号线程执行完毕"<<endl;
    this->clean_tree(head);
    head=NULL;
    //cout<<num<<"号线程请求新任务"<<endl;
    //cout<<min_treelen<<"  "<<tree_pathdata.size()<<"   "<<endl;
    if(this->min_treelen<tree_pathdata.size())
    {
        tree_pathdata.clear();
        vector<vector<int> >(tree_pathdata).swap(tree_pathdata);
    }
    emit this->request_newtask(num,tree_pathdata);
    }
}

void tree::updata_mintreelen(int len)
{
    if(len<min_treelen)
    {
       // cout<<num<<"号线程更新最小值"<<len<<endl;
        min_treelen=len;
    }
}


void tree::save_treepath(node *p)
{
    this->tree_pathdata.clear();
    vector<vector<int> >(tree_pathdata).swap(tree_pathdata);
    while(p!=NULL)
    {
        vector<int> data1;
        for(int a=0;a<tasksize;a++)
        {
            data1.push_back(p->bucket[a]);

        }
        tree_pathdata.push_back(data1);
        p=p->parent;
    }
    reverse(tree_pathdata.begin(),tree_pathdata.end());

}
