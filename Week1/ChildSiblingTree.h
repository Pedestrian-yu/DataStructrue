#ifndef __CHILD_SIBLING_TREE_H__
#define __CHILD_SIBLING_TREE_H__

#include "ChildSiblingTreeNode.h"		// 孩子兄弟表示树结点类
#include <iostream>
// 孩子兄弟表示树类
template <class ElemType>
class ChildSiblingTree
{
protected:
//  树的数据成员:
	ChildSiblingTreeNode<ElemType> *root;			// 根指针 



public:
	ChildSiblingTree();									// 无参数的构造函数
	void Destroy(ChildSiblingTreeNode<ElemType> * &r);		// 销毁以r为根的树
	virtual ~ChildSiblingTree();						// 析构函数
	ChildSiblingTreeNode<ElemType> *CreateTreeGhelp(ElemType items[], int parents[], int r, int n);
		// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树，并 求树的根
	ChildSiblingTree(ElemType items[], int parents[], int n);
		// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
	int Height(ChildSiblingTreeNode<ElemType> *r) const;	// 求以r为根的树的高
	int	Height() const;									//  求树的高
	ChildSiblingTreeNode<ElemType> *FirstChild(ChildSiblingTreeNode<ElemType> *cur) const;	
		// 求树结点cur的第一个孩子
	ChildSiblingTreeNode<ElemType> *NextSibling(ChildSiblingTreeNode<ElemType> *cur) const;				
		// 求树结点cur的下一个兄弟
	int NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const;	    // 求结点cur的度
	int Degree(ChildSiblingTreeNode<ElemType> *r) const;	// 求以r为根的树的度
	int Degree() const;									            // 求树的度
	void CountLeafNodeHelp(ChildSiblingTreeNode<ElemType> *r,int &leafnum) const;
	int CountLeafNode() const;	
		
	
};

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree()
// 操作结果：构造一个空树
{
	root = NULL;					// 表示树为空
}

template <class ElemType>
void ChildSiblingTree<ElemType>::Destroy(ChildSiblingTreeNode<ElemType> * &r)
// 操作结果：销毁以r为根的树
{
    ChildSiblingTreeNode<ElemType> *p;
	if (r != NULL)	{
		for (p = FirstChild(r); p != NULL; p = NextSibling(p))
			Destroy(p);		// 销毁子树
		delete r;				// 销毁根结点
		r = NULL;
	}
}

template <class ElemType>
ChildSiblingTree<ElemType>::~ChildSiblingTree()
// 操作结果：销毁树--析造函数
{
	Destroy(root);
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::CreateTreeGhelp(ElemType elems[], int parents[], int r, int n)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树，并返回树的根
{
	if (r >= 0 && r < n){
		ChildSiblingTreeNode<ElemType> *rt = new ChildSiblingTreeNode<ElemType>(elems[r]);	// 复制根结点
		ChildSiblingTreeNode<ElemType> *subTreeRoot, *cur;
		for (int i = 0; i < n; i++)	{	// 查找r的孩子
			if (parents[i] == r)	{	// 建立以pos为根的子树
				subTreeRoot = CreateTreeGhelp(elems, parents, i, n);
				if (rt->firstChild == NULL)	{	// subTreeRoot为rt第一棵子树的根
					rt->firstChild = subTreeRoot;	
					cur = subTreeRoot;	        // cur最新复制的子树的根
				}
				else{	               // subTreeRoot为cur的下一个兄弟
					cur->nextSibling = subTreeRoot;
					cur = subTreeRoot;
				}
			}
		}
		return rt;
	}
	else return NULL;									// r非法，建立空树
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ElemType elems[], int parents[], int n)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为0,结点个数为n的树
{
	root = CreateTreeGhelp(elems, parents, 0, n);	// 用辅助函数建立树
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Height(ChildSiblingTreeNode<ElemType> *r) const
// 操作结果： 求以r为根的树的高
{
    ChildSiblingTreeNode<ElemType> *p;
	if (r == NULL)
		return 0;
	else	{
		int maxSubTreeHeight = 0, h;
		for (p = FirstChild(r); p != NULL;  p = NextSibling(p))	{	
			h = Height(p);	    	// 求各子树的高
			maxSubTreeHeight = (maxSubTreeHeight < h) ? h : maxSubTreeHeight;
				// 求各子树高的最大值
		}
		return maxSubTreeHeight + 1;	// 树高为各子树的最大值再加1
	}
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Height() const
// 操作结果： 求树的高
{
	return Height(root);
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::FirstChild(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：如cur无孩子,则返回NULL,否则返回树结点cur的第一个孩子,
{
	if (cur == NULL)
		return NULL;				// 空结点无孩子		
	else
		return cur->firstChild;		// firstChild为第一个孩子
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::NextSibling(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果：如果结点cur为空或没有下一个兄弟,则返回NULL,否则返回cur的下一个兄弟
{
	if (cur == NULL)
		return NULL;				// 空结点右兄弟
	else
		return cur->nextSibling;	// nextSibling为下一个兄弟
}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const
// 操作结果： 求结点cur的度
{
    ChildSiblingTreeNode<ElemType> *p;
	int count = 0;
	for (p = FirstChild(cur); p != NULL;    p = NextSibling(p))
		count++;					// 对孩子个数进行计数
	return count;
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Degree(ChildSiblingTreeNode<ElemType> *r) const
// 操作结果： 求以r为根的树的度
{
    ChildSiblingTreeNode<ElemType> *p;
	int d = 0;
	int maxSubTreeDegree = 0;	// 子树度的最大度 
	for (p = FirstChild(r); p != NULL;  p = NextSibling(p))	{	
		d++;					// 对孩子个数进行计数
		int subTreeDegree = Degree(p);	//  求以p为根的子树度
		maxSubTreeDegree = (maxSubTreeDegree < subTreeDegree) ? subTreeDegree : maxSubTreeDegree;
			// 求子树度最大值
	}
	return (d < maxSubTreeDegree) ? maxSubTreeDegree : d;
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Degree() const
// 操作结果： 求树的度
{
	return Degree(root);
}

template <class ElemType>
void ChildSiblingTree<ElemType>::CountLeafNodeHelp(ChildSiblingTreeNode<ElemType> *r,int &leafnum) const
{
    ChildSiblingTreeNode<ElemType> *p;
	if (r != NULL)	{	
		if (NodeDegree(r)==0)
		{
			leafnum++;
			cout<<r->data<<";";
		}			
		for (p = FirstChild(r); p != NULL;	p = NextSibling(p))
			CountLeafNodeHelp(p, leafnum);// 依次先根序遍历根结点的每棵子树
	}
}

template <class ElemType>
int ChildSiblingTree<ElemType>::CountLeafNode() const

{
	int leafnum=0;
	CountLeafNodeHelp(root,leafnum);
	cout<<"叶子节点数：";
	return leafnum;
}

#endif