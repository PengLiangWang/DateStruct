/*通用双链表*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagSTDNODE   STDNODE, *LPSTDNODE;
typedef struct tagSTDLIST   STDLIST, *LPSTDLIST;

//链表数据结构
struct tagSTDNODE{
    LPSTDNODE     lpPrev;
    LPSTDNODE     lpNext;
};

//链表节点结构
struct tagSTDLIST{
    LPSTDNODE  lpHead;
    LPSTDNODE  lpTail;
};

//用于链表扩展的宏
#define NODE_INITIALIAER  ((STDNODE){.lpPrev=NULL, .lpNext=NULL})
#define LIST_INITIALIAER  ((STDLIST){.lpHead=NULL, .lpTail=NULL})

#define DECLARELISTNODE()  STDNODE __snStdNode
#define INIT_LISTNODE()    __snStdNode = NODE_INITIALIAER


LPSTDLIST StdListInit(LPSTDLIST lpList);
LPSTDNODE StdListGetHeadNode(LPSTDLIST lpList);
LPSTDNODE STdListGetTailNode(LPSTDLIST lpList);
LPSTDNODE StdListGetNextNode(LPSTDNODE lpNode);
LPSTDNODE StdListGetPrevNode(LPSTDNODE lpNode);
void StdListPushFront(LPSTDLIST lpList, LPSTDNODE lpNode);
void StdListPushBack(LPSTDLIST lpList, LPSTDNODE lpNode);
void StdListInsert(LPSTDLIST lpList, LPSTDNODE lpAfter, LPSTDNODE lpNode);
LPSTDNODE StdListPopFront(LPSTDLIST lpList);
LPSTDNODE StdListPopBack(LPSTDLIST lpList);
LPSTDNODE StdListRemove(LPSTDLIST lpList, LPSTDNODE lpNode);
int StdListIsEmpty(LPSTDLIST lpList);
long StdListGetSize(LPSTDLIST lpList);
LPSTDLIST StdListCombine(LPSTDLIST lpList1, LPSTDLIST lpList2);



























