#ifndef BUCKET_MANAGE_H
#define BUCKET_MANAGE_H
#include <node.h>
#include<iostream>
#include <QObject>
using namespace std;
#include <queue>
#include <tree.h>
#include <QThread>
#include <QDebug>
#include<time.h>
#define maxsize 4
class bucket_manage:public QObject
{
    Q_OBJECT
public:
    bucket_manage();
    clock_t e,s;
    int min_treelen=INT_MAX;
    queue <node *> node_queue;
    vector<vector<int> > tree_minpathdata;
    void create(node *p,int nodesize);
    void output(node *p);
    bool isrepeat(node *p);
    void output_tree_minpath();
    node *head=NULL;
    int tasksize=4;
    int thread_size=0;
    QList <QThread*> thread_object;
    QList <tree*>    tree_object;
    QList <bool>     thread_busy;
    int rongliang[maxsize]={21,11,8,5};
    void bucket_start(int thread_num);
    vector<vector<int>> acquire_tree(node *p);
   signals:
    void starttask(vector<vector<int> > data,int tree_minlen,int num);
    void updata_mintreelen(int tree_minlen);
private slots:
    void receive_minlentree(int len,int num);
    void receive_finishtask(int num,vector<vector<int>> tree_pathdata);

};

#endif // BUCKET_MANAGE_H
