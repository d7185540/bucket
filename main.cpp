#include <QCoreApplication>
#include<iostream>
#include<time.h>
#include <node.h>
#include <tree.h>
#include <bucket_manage.h>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

     //tree *p=new tree();
     vector <vector <int>> data;
     vector<int > d1={21 ,0 ,0 ,0};
//     vector<int > d2={0 ,0, 11, 10};
//     vector<int > d3={5 ,0, 6, 10};
//     vector<int > d4={0 ,5 ,6 ,10};
//     vector<int > d5={5 ,5 ,1 ,10};
//     vector<int > d6={2 ,8 ,1, 10};
//     vector<int > d7={2, 0, 1, 18};
//     vector<int > d8={0 ,2 ,1 ,18};
//     vector<int > d9={1 ,2 ,0 ,18};
     data.push_back(d1);
//     data.push_back(d2);
//     data.push_back(d3);
//     data.push_back(d4);
//     data.push_back(d5);
//     data.push_back(d6);
//     data.push_back(d7);
//     data.push_back(d8);
//     data.push_back(d9);

//     p->init(data);
//     p->tree_start(p->startnode);
//     p->clean_tree(p->head);
     bucket_manage d;
     node *f=new node();
     for(int c=0;c<d1.size();c++)
         f->bucket[c]=d1[c];

     d.create(f,14);
     d.bucket_start(7);


    return a.exec();
}
