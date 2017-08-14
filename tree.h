#ifndef TREE_H
#define TREE_H
#include <node.h>
#define maxsize 4
#include <vector>
#include <QObject>
class tree:public QObject
{
    Q_OBJECT
public:

    tree(int a);
    int rongliang[maxsize]={21,11,8,5};
    //int item[maxsize]={0,7,7,7};
    int num;
    int item[maxsize]={7,7,7,0};
    int cishu=0;
    int tasksize=4;
    int min_treelen=INT_MAX;
    node *head=NULL;
    node *startnode=NULL;
    vector<vector<int> > tree_pathdata; //保存最短路径树
    void tree_start(node *p);
    bool isrepeat(node *p);
    void output(node *p);
    void init(vector <vector <int>> data);
    void clean_tree(node *p);
    void save_treepath(node *p);
private slots:
    void receivetask(vector<vector<int> > data,int tree_minlen,int num);
    void updata_mintreelen(int len);
signals:
    void send_mintreelen(int len,int num);
    void request_newtask(int num,vector<vector<int>> tree_pathdata);

};



#endif // TREE_H
