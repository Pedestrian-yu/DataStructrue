#ifndef __CHILD_PARENT_TREE_H__
#define __CHILD_PARENT_TREE_H__

#include "ChildParentTreeNode.h"	// 孩子双亲表示树结点类
#include <iostream>
#define DEFAULT_SIZE 1000
using namespace std;

// 孩子双亲表示树类
template <class ElemType>
class ChildParentTree
{
protected:
//  树的数据成员:
	ChildParentTreeNode<ElemType> *nodes;			// 存储树结点
	int maxSize;									// 树结点最大个数 
	int root, num;									// 根的位置及结点数

public:
	ChildParentTree();								// 无参构造函数
	virtual ~ChildParentTree();						// 析构函数
	ChildParentTree(ElemType items[], int parents[], int r, int n, int size =DEFAULT_SIZE);
		// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
	int FirstChild(int cur) const;					// 返回结点cur的第一个孩子
	int RightSibling(int cur) const;				// 返回结点cur的右兄弟
	int HeightHelp(int r) const;					// 返回以r为根的高
	int	Height() const;								// 返回树的高
	int NodeDegree(int cur) const;					// 返回结点cur的度
	void CountLeafNodeHelp(int r,int &leafnum) const;								//计算叶子节点
	int CountLeafNode() const;								//计算叶子节点
	int DegreeHelp(int r) const;					// 返回以r为根的树的度
	int Degree() const;								// 返回树的度
};

template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree()
// 操作结果：构造一个空树
{
	maxSize = 0;								// 树结点最大个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];	// 分配存储空间
	root = -1;											// 表示不存在根
	num = 0;											// 空树的结点个数为0
}

template <class ElemType>
ChildParentTree<ElemType>::~ChildParentTree()
// 操作结果：释放存储空间
{
    Node<int> *p;
    for (int n = 0; n < num; n++) {
       p = nodes[n].childLkList;
       while ( p!= NULL) {
          nodes[n].childLkList = p->next;
          delete p;
          p = nodes[n].childLkList;
       }
    }   
	delete []nodes;										// 释放存储空间
}

template <class ElemType>
ChildParentTree<ElemType>::ChildParentTree(ElemType items[], int parents[], int r, int n, int size)
{
	maxSize = size;													// 最大结点个数
	if (n > maxSize)	{
	    cout<<"结点个数太多!"<<endl;
		return;
	}								
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
	for (int i = 0; i < n; i++)
	{	
		nodes[i].data = items[i];								// 数据元素值
		nodes[i].parent = parents[i];							// 双亲位置
		if (parents[i] != -1)		{							//创建孩子表
           Node<int> *p, *newnode;
	       newnode = new Node<int>(i, NULL);						
	       if (nodes[parents[i]].childLkList == NULL)
	          nodes[parents[i]].childLkList = newnode;				//首个孩子为给节点的双亲节点添加孩子表
           else {
              p =  nodes[parents[i]].childLkList;  					
	          while (p->next != NULL)
	             p = p->next;
	          p->next = newnode;									//其余孩子依次添加
            }   
		}
	}
	root = r;														// 根
	num = n;														// 结点个数
}

template <class ElemType>
int ChildParentTree<ElemType>::FirstChild(int cur) const
// 操作结果：如cur无孩子,则返回-1,否则返回树结点cur的第一个孩子,
{
    Node<int> *p;
	if (cur < 0 || cur >= num)	
		return -1;						// 结点cur不存在,返回-1表示无孩子
	
	if (nodes[cur].childLkList == NULL)	// 无孩子
		return -1;
	else
		return nodes[cur].childLkList->data;	// 取出第一个孩子
}

template <class ElemType>
int ChildParentTree<ElemType>::RightSibling(int cur) const
// 操作结果：如果结点cur无右兄弟,则返回-1,否则返回cur的右兄弟
{
	if (cur < 0 || cur >= num)						
		return -1;						// 结点cur不存在,返回-1表示无孩子

	int pt = nodes[cur].parent;			// cur的双亲
    Node<int> * p = nodes[pt].childLkList;
    while (p != NULL && p->data != cur)
       p = p->next;
    if ( p == NULL || p->next == NULL)
		return -1;				// 反回右兄弟
	else
		return p->next->data;	// 表示无右兄弟
}

template <class ElemType>
int ChildParentTree<ElemType>::HeightHelp(int r) const
// 操作结果：返回以r为根的树的高
{
    int child, h, maxSubTreeHeight = 0;
	if (r < 0 || r >= num)
		return 0;
	else	{
		for (child = FirstChild(r); child != -1; child = RightSibling(child)) {
			h = HeightHelp(child);			// 求各子树的高
			maxSubTreeHeight = (maxSubTreeHeight < h) ? h : maxSubTreeHeight;
				// 求各子树高的最大值
		}
		return maxSubTreeHeight + 1;			// 树高为各子树的最大值再加1
	}
}

template <class ElemType>
int ChildParentTree<ElemType>::Height() const
// 操作结果：返回树的高
{
	return HeightHelp(root);					// 调用辅助函数实现返回树的高
}

template <class ElemType>
int ChildParentTree<ElemType>::NodeDegree(int cur) const
// 操作结果：返回结点cur的度
{
	int d = 0;						// 临时变量,用于对孩子个数进行计数
	for (int child = FirstChild(cur); child != -1; child = RightSibling(child))
		d++;						// 对孩子个数进行计数
	return d;
}

template <class ElemType>
void ChildParentTree<ElemType>::CountLeafNodeHelp(int r,int &leafnum) const
{
	if (r >=0 && r < num)	{	// r范围合法
		if (NodeDegree(r)==0)
		{
			leafnum++;
			cout<<nodes[r].data<<";";
		}
		for (int child = FirstChild(r); child != -1; child = RightSibling(child))
			CountLeafNodeHelp(child,leafnum);// 依次先根序遍历每棵子树,
	}
}

template <class ElemType>
int ChildParentTree<ElemType>::CountLeafNode() const
{
	int leafnum=0;
	CountLeafNodeHelp(root,leafnum);
	cout<<"叶子节点数：";
	return leafnum;
}

template <class ElemType>
int ChildParentTree<ElemType>::DegreeHelp(int r) const
// 操作结果：返回以r为根的树的度
{

	int d = 0;						// 用于统计结点r的孩子个数
	int maxSubTreeDegree = 0;		// 子树中度的最大值
	for (int child = FirstChild(r); child != -1; child = RightSibling(child)) { 
		d++;						// 对r的孩子个数进行计数
		int subTreeDegree = DegreeHelp(child);	// 子树的度
		maxSubTreeDegree = (maxSubTreeDegree < subTreeDegree) ? subTreeDegree : maxSubTreeDegree;
			// 求子树度最大值
	}
	return (d < maxSubTreeDegree) ? maxSubTreeDegree : d;
}

template <class ElemType>
int ChildParentTree<ElemType>::Degree() const
// 操作结果：返回树的度
{
	return DegreeHelp(root);
}
#endif