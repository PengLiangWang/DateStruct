#include "STDLIST.h"

//初始化链表
LPSTDLIST StdListInit(LPSTDLIST lpList)
{
    lpList->lpHead = NULL;
    lpList->lpTail = NULL;
    return lpList;
}


//获取链表头节点
LPSTDNODE StdListGetHeadNode(LPSTDLIST lpList)
{
    return lpList->lpHead;
}

//获取链表尾节点
LPSTDNODE STdListGetTailNode(LPSTDLIST lpList)
{
    return lpList->lpTail;
}

//获取给定的下一个节点
LPSTDNODE StdListGetNextNode(LPSTDNODE lpNode)
{
    return lpNode->lpNext;
}

//获取给定节点的上一个节点
LPSTDNODE StdListGetPrevNode(LPSTDNODE lpNode)
{
    return lpNode->lpPrev;
}

//链表头部插入一个节点
void StdListPushFront(LPSTDLIST lpList, LPSTDNODE lpNode)
{
    lpNode->lpPrev = NULL;
    lpNode->lpNext = lpList->lpHead;

    if(lpList->lpHead)
        lpList->lpHead->lpPrev = lpNode;
    else
        lpList->lpTail = lpNode;

    lpList->lpHead = lpNode;
}

//链表尾部插入一个节点
void StdListPushBack(LPSTDLIST lpList, LPSTDNODE lpNode)
{
    lpNode->lpNext = NULL;
    lpNode->lpPrev = lpList->lpTail;

    if(lpList->lpTail)
        lpList->lpTail->lpNext = lpNode;
    else
        lpList->lpHead = lpNode;

    lpList->lpTail = lpNode;
}

//在给定节点之后插入一个节点
void StdListInsert(LPSTDLIST lpList, LPSTDNODE lpAfter, LPSTDNODE lpNode) 
{
    if(lpAfter) 
    {
        if(lpAfter->lpNext)
            lpAfter->lpNext->lpPrev = lpNode;
        else
            lpList->lpTail = lpNode;

        lpNode->lpPrev = lpAfter;
        lpNode->lpNext = lpAfter->lpNext;
        lpAfter->lpNext = lpNode;
    }
    else
    {
        StdListPushFront(lpList, lpNode);    
    }
}

//从链表头部弹出一个节点
LPSTDNODE StdListPopFront(LPSTDLIST lpList)
{
    if(lpList->lpHead)
    {
        LPSTDNODE lpNode = lpList->lpHead;
        if(lpList->lpHead->lpNext)
            lpList->lpHead->lpNext->lpPrev = NULL;
        else
            lpList->lpTail = NULL; 
         
        lpList->lpHead = lpList->lpHead->lpNext;
        lpNode->lpPrev = lpNode->lpNext = NULL; 
        return lpNode;
    }else
    {
        return NULL;   
    }

}
//从链表的尾部弹出一个节点
LPSTDNODE StdListPopBack(LPSTDLIST lpList)
{
    if(lpList->lpTail)
    {
        LPSTDNODE lpNode = lpList->lpTail;
        if(lpList->lpTail->lpPrev)
            lpList->lpTail->lpPrev->lpNext = NULL;
        else
            lpList->lpHead = NULL;

        lpList->lpTail = lpList->lpTail->lpPrev;
        lpNode->lpPrev = lpNode->lpNext = NULL;
       
        return lpNode;
    }
    else
    {
        return NULL;
    }
}

//从链表中删除给定节点
LPSTDNODE StdListRemove(LPSTDLIST lpList, LPSTDNODE lpNode)
{
    if(lpNode->lpPrev)
        lpNode->lpPrev->lpNext = lpNode->lpNext;
    else
        lpList->lpHead = lpNode->lpNext;

    if(lpNode->lpNext)
        lpNode->lpNext->lpPrev = lpNode->lpPrev;
    else
        lpList->lpTail = lpNode->lpPrev;

    return lpNode;
}

//检查链表是否为空
int StdListIsEmpty(LPSTDLIST lpList)
{
    if(lpList->lpHead || lpList->lpTail)
        return 0;
    else
        return 1;

}

//获取链表中的节点数
long StdListGetSize(LPSTDLIST lpList)
{
    long InSize = 0;
    LPSTDNODE lpNode = StdListGetHeadNode(lpList); 
    while(lpNode)
    {
        ++ InSize;
        lpNode = StdListGetNextNode(lpNode); 
    }
    return InSize;
}

//合并两个链表成一个
LPSTDLIST StdListCombine(LPSTDLIST lpList1, LPSTDLIST lpList2)
{
     if(!StdListIsEmpty(lpList2)) 
     {
         if(!StdListIsEmpty(lpList1))
         {
             lpList1->lpTail->lpNext = lpList2->lpHead;
             lpList2->lpHead->lpPrev = lpList1->lpTail;
             lpList1->lpTail = lpList2->lpTail;
         }
         else
         {
             lpList1->lpHead = lpList2->lpHead;
             lpList1->lpTail = lpList2->lpTail;
         }

         lpList2->lpHead = lpList2->lpTail = NULL;
     }
     return lpList1;
}
