#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<string>

using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
	// 可选内容：构造方法
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 声明
void init(ListNode* head);
void addNode(ListNode* head, int val, int index=-1);
void removeNodeByValue(ListNode* head, int val);
void removeNodeByIndex(ListNode* head, int index);
void reverseLinkList(ListNode* head);
void printList(ListNode* head);




void testLinkList()
{
    ListNode* head = new ListNode();
    init(head);
	printList(head);

	// // 根据值删除
	// removeNodeByValue(head, 12);
	// printList(head);

	// // 根据位置删除
	// addNode(head, 100,3);
	// addNode(head, 200);
	// printList(head);
	// removeNodeByIndex(head, 3);
	// removeNodeByIndex(head,4);
	// printList(head);

	// 反转链表
	reverseLinkList(head);
	printList(head);
}



//---------------------------- 初始化 ----------------------------//

void init(ListNode* head)
{
    addNode(head, 10);
    addNode(head, 20);
    addNode(head, 30);
    addNode(head, 40);
	// addNode(head, 12, 1);
	// addNode(head,12,0);
	addNode(head, 50);
}


void printList(ListNode* head)
{
	cout<<"\n输出链表:"<<endl;
	ListNode* cur = head->next;
	while (cur != nullptr)
	{
		printf("%d\t",cur->val);
		cur = cur->next;
	}
}



//---------------------------- 基本操作 ----------------------------// 

// 添加结点（默认添加至末尾）
void addNode(ListNode* head, int val, int index)
{
	if (head == nullptr)
    {
        head = new ListNode();
		head->next = new ListNode(val);
        return;
    }

    ListNode* pre = head;	// 插入目标位置的前驱
    if(index>-1)
    {
		// 插入到目标位置，先找到目标位置的前驱
		for (int i = 0; i < index; i++)
		{
			pre = pre->next;
			if (pre == nullptr) break;
		}
		ListNode* temp = pre->next;
		pre->next = new ListNode(val);
		pre->next->next = temp;
    }
	else
	{
        // 添加到末尾
		while (pre->next != nullptr) pre = pre->next;
		pre->next = new ListNode(val);
	}
}


void removeNodeByValue(ListNode* head, int val)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout<<"警告：链表为空"<<endl;
		return;
	}

	ListNode* pre = head;
	while (pre->next != nullptr)
	{
		if(pre->next->val == val)
		{
			// 删除结点
			ListNode* temp = pre->next;
			pre->next = pre->next->next;
			delete(temp);
		}
		else pre = pre->next;
	}
	
}
void removeNodeByIndex(ListNode* head, int index)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout<<"警告：链表为空"<<endl;
		return;
	}

	ListNode* pre = head;
	if(index>-1)
    {
		// 删除目标位置，先找到目标位置的前驱
		int i=0;
		while(i<index && pre->next != nullptr)
		{
			pre = pre->next;
			i++;
		}
		if(pre->next == nullptr)
		{
			cout<< "警告：index不存在 " << index <<endl;
			return;
		}

		// 删除结点
		ListNode* temp = pre->next;
		pre->next = pre->next->next;
		delete(temp);
    }
	else cout<< "警告：index不存在 " << index <<endl;
}


// 反转链表：3指针法
void reverseLinkList(ListNode* head)
{
	/*
		head：专用头节点，head->next指向链表首个节点
		prev：指向上一个被加入翻转链表的节点，也是当前反转链表的首节点
		cur：【当前】从原链表断开并【加入反转链表】的节点
		next：下一轮将要加入反转链表的节点
	*/
	ListNode *prev, *cur=head, *next=head->next;
	while(next!=nullptr)
	{
		// 移动至本轮操作的节点
		cur = next;
		next = cur->next;
		// 从原链表断开，加入反转链表
		cur->next = prev;
		prev = cur;
	}
	head->next = cur;
}
