#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<string>

using namespace std;

void ldrTreadTree(TreeNode* root);
void ldrTread(TreeNode* root, ThreadTreeNode* pre);

// 二叉树
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0),left(nullptr),right(nullptr) {}
    TreeNode(int x) : val(x),left(nullptr),right(nullptr) {}
};

// 线索二叉树
struct ThreadTreeNode
{
    int val;
    ThreadTreeNode* left;
    int leftTag; // 0: left child, 1: left thread
    ThreadTreeNode* right;
    int rightTag; // 0: right child, 1: right thread

    ThreadTreeNode() : val(0),left(nullptr),right(nullptr) {}
    ThreadTreeNode(int x) : val(x),left(nullptr),right(nullptr) {}
};


// 二叉树线索化：中序遍历
void ldrTreadTree(ThreadTreeNode* root)
{
    // 连接前后用的结点指针
    ThreadTreeNode* pre = nullptr;
    if(root != nullptr)
    {
        ldrTread(root,pre);
        // 处理最后一个节点
        pre->right = nullptr;
        pre->rightTag = 1;
    }
}
void ldrTread(ThreadTreeNode* root, ThreadTreeNode* pre)
{
    if(root==nullptr) return;

    // 递归线索化左子树
    if(root->left != nullptr) ldrTread(root->left,pre);
    
    // 连接前驱与当前结点
    root->leftTag = 1;
    root->left = pre;
    if(pre!=nullptr)
    {
        pre->rightTag = 1;
        pre->right = root;
    }
    
    // 准备进行下一步
    pre = root;
    ldrTread(root->right,pre);
}