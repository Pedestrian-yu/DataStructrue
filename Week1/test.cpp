#include "ChildParentTree.h"			// 孩子双亲表示树类
#include "ChildSiblingTree.h"
#include <iostream>


int main(void)
{
        int r = 0, n;
		cout<<"输入节点个数：";
        cin>>n;
        char* items=new char[n];
        int * parents=new int[n];
		// char items[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
		// int parents[] = {-1, 0, 0, 0, 1, 1, 3, 3};
		cout<<"输入节点名称:"<<endl;
        for (int i = 0; i < n; i++)
        {
            cin>>items[i];
        }
        cout<<"按顺序输入对应的双亲:"<<endl;
        for (int i = 0; i < n; i++)
        {
            cin>>parents[i];
        }
		ChildParentTree<char> t(items, parents, r, n);
		ChildSiblingTree<char> s(items, parents,n);
        cout<<"顺序存储的树高度"<<t.Height()<<endl;
		cout<<"顺序存储的树的度"<<t.Degree()<<endl;
		cout<<"顺序存储的叶子节点："<<t.CountLeafNode()<<endl;
        cout<<"链式存储的树高度"<<s.Height()<<endl;
		cout<<"链式存储的树的度"<<s.Degree()<<endl;
        cout<<"链式存储的叶子节点："<<s.CountLeafNode()<<endl;
}