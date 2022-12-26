#pragma once
#include <iostream>
using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
    ListNode(int x) : val(x), next(NULL) { }
};


void printNodeList(ListNode* head)   //¥Ú”° ‰≥ˆ¡¥±Ì
{
    ListNode* p = head;
    while (p != NULL)
    {
        cout << p->val << endl;
        p = p->next;
    }
}


ListNode* CreateListNode()
{
    ListNode* pHead = new ListNode(0);
    ListNode* p = pHead;         

    for (int i = 1; i < 10; ++i)
    {
        ListNode* pNewNode = new ListNode(0);

        pNewNode->val = i;           
        pNewNode->next = NULL;

        p->next = pNewNode;
        p = pNewNode; 
    }

    return pHead;
}
