#include "bucket_manage.h"

bucket_manage::bucket_manage()
{
  qRegisterMetaType<vector<vector<int>> >("vector<vector<int>>");
}

void bucket_manage::create(node *p, int nodesize)
{
  //  cout<<"add  "<<p->bucket[0]<<" "<<p->bucket[1]<<" "<<p->bucket[2]<<" "<<p->bucket[3]<<" "<<"!"<<endl;
    if(p!=NULL)
    {
        for(int a=0;a<tasksize;a++)
        {
            for(int b=0;b<tasksize;b++)
            {
                if(a!=b&&p->bucket[a]!=0&&p->bucket[b]!=rongliang[b])
                {
                    node *d=new node();
                    d->a=a;
                    d->b=b;
                    p->son[a][b]=d;
                    d->parent=p;
                    for(int c=0;c<tasksize;c++)
                        d->bucket[c]=p->bucket[c];
                    d->caculate(a,b,rongliang);
                    if(isrepeat(d)==false)
                    node_queue.push(d);
                  //  cout<<"add  "<<p->son[a][b]->bucket[0]<<" "<<p->son[a][b]->bucket[1]<<" "<<p->son[a][b]->bucket[2]<<" "<<p->son[a][b]->bucket[3]<<" "<<a<<"!"<<b<<endl;
                }
            }
        }
        if(node_queue.size()<nodesize)
        {
            node *f=node_queue.front();
            node_queue.pop();
            create(f,nodesize);
        }

    }
}

void bucket_manage::output(node *p)
{
    if(p->parent==NULL&&p!=NULL)
    {
       p->output();
    }
    else
    {
       output(p->parent);
       p->output();
    }
}

void bucket_manage::bucket_start(int thread_num)
{
    s=clock();
    thread_size=thread_num;
    for(int a=0;a<thread_num;a++)
    {
        cout<<"开启线程"<<a<<"号"<<endl;
        QThread *d=new QThread();
        thread_object.append(d);
        tree   *f=new tree(a);
        tree_object.append(f);
        thread_busy.append(false);
        d->start();
        f->moveToThread(d);
        connect(this,SIGNAL(starttask(vector<vector<int> >,int,int)),f,SLOT(receivetask(vector<vector<int> >,int,int)));
        connect(this,SIGNAL(updata_mintreelen(int)),f,SLOT(updata_mintreelen(int)),Qt::DirectConnection);
        connect(f,SIGNAL(send_mintreelen(int,int)),this,SLOT(receive_minlentree(int,int)));
        connect(f,SIGNAL(request_newtask(int,vector<vector<int> >)),this,SLOT(receive_finishtask(int,vector<vector<int> >)));
        if(node_queue.size()>0)
        {
            node *p=node_queue.front();
            node_queue.pop();
            emit starttask(acquire_tree(p),min_treelen,a);
            thread_busy[a]=true;
        }
    }
}


void bucket_manage::receive_minlentree(int len,int num)
{
    if(len<min_treelen)
    {
        cout<<num<<"号线程最小长度为:"<<len<<endl;
        min_treelen=len;
        emit updata_mintreelen(min_treelen);
    }
}


vector<vector<int>>bucket_manage::acquire_tree(node *p)
{

    vector<vector<int>> data;
    while(p!=NULL)
    {
        vector<int> data1;
        for(int a=0;a<tasksize;a++)
        {
            data1.push_back(p->bucket[a]);

        }
        data.push_back(data1);
        p=p->parent;
    }
    reverse(data.begin(),data.end());

    return data;
}


bool bucket_manage::isrepeat(node *p)
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


void bucket_manage::receive_finishtask(int num, vector<vector<int> > tree_pathdata)
{
    if(node_queue.size()>0)
    {
        node *p=node_queue.front();
        node_queue.pop();
        emit starttask(acquire_tree(p),min_treelen,num);
        thread_busy[num]=true;
    }
    else
    {
        thread_busy[num]=false;
    }
   // cout<<tree_pathdata.size()<<"!!!!!!!!"<<endl;
    if(tree_pathdata.size()>0&&tree_pathdata.size()<=min_treelen)
    {
        this->tree_minpathdata.clear();
        vector<vector<int> >(tree_minpathdata).swap(tree_minpathdata);
        this->tree_minpathdata=tree_pathdata;

    }

    for(int a=0;a<thread_size;a++)
    {
        if(thread_busy[a]==true)
            break;
        if(a==thread_size-1)
        {
            output_tree_minpath();
            cout<<"执行完毕";
            e=clock()-s;
            printf("程序用时%.3fs\n",(double)e/1000);
        }

    }
}

void bucket_manage::output_tree_minpath()
{
   int pathsize=tree_minpathdata.size();
   for(int a=0;a<pathsize;a++)
   {
       for(int b=0;b<tasksize;b++)
       {
           cout<<tree_minpathdata[a][b]<<" ";
       }
       cout<<endl;
   }
}
