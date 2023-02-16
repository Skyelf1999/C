#pragma once

#include <string>

using namespace std;

/*

*/



///////////////////////////// 普通数据单元 /////////////////////////////
template<class ValueT,class IndexT=int>
class Data
{
public:
    IndexT index;
    ValueT value;
    Data(IndexT index,ValueT value);
    ~Data();
};

template<class ValueT,class IndexT>
Data<ValueT,IndexT>::Data(IndexT index,ValueT value) : index(index) , value(value)
{

}



///////////////////////////// 链表节点 /////////////////////////////
struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};



///////////////////////////// 二叉树节点 /////////////////////////////
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0),left(nullptr),right(nullptr) {}
    TreeNode(int x) : val(x),left(nullptr),right(nullptr) {}
};