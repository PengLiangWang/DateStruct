#include "STDLIST.h"
//通过双链表实现消息队列

//定义消息节点
typedef struct tagMSGNODE{
     DECLARELISTNODE();
     int   id;
     int   age;
     char  name[10];
}MSGNODE, *LPMSGNODE;


STDLIST  lstMsgQueue;


int main(int argc, char *argv[])
{
    int i;

    for(i=1; i<10; i++)
    {
        LPMSGNODE lpMsgNode = (LPMSGNODE)malloc(sizeof(MSGNODE));
        lpMsgNode->INIT_LISTNODE();
        lpMsgNode->id = i;
        lpMsgNode->age = i*10 + 1;
        strcpy(lpMsgNode->name, "Wang");
        StdListPushBack(&lstMsgQueue, (LPSTDNODE)lpMsgNode);  //从前往后往队里放数据
    }

    //从消息队列中取出一条数据
    LPMSGNODE GetMsgNode1 = (LPMSGNODE)StdListPopFront(&lstMsgQueue);
    printf("id: %d\nage: %d\nname:%s\n\n\n", GetMsgNode1->id, GetMsgNode1->age, GetMsgNode1->name);

    //删除队列中id等于2的人的信息
    LPMSGNODE lpTemp = (LPMSGNODE)StdListGetHeadNode(&lstMsgQueue);
    while(lpTemp)
    {
        LPMSGNODE lpNext = (LPMSGNODE)StdListGetNextNode((LPSTDNODE)lpTemp); 
        if(lpTemp->id == 2)
        {
            printf("删除节点id: %d\nage: %d\nname: %s\n\n\n", lpTemp->id, lpTemp->age, lpTemp->name);
            StdListRemove(&lstMsgQueue, (LPSTDNODE)lpTemp);
        }
        free(lpTemp);

        lpTemp = lpNext;
    }
    int iNum=0;
    iNum = StdListGetSize(&lstMsgQueue);
    printf("此时队列的节点数：%d\n\n", iNum);
    LPMSGNODE GetMsgNode2 = (LPMSGNODE)StdListPopFront(&lstMsgQueue);
    printf("id: %d\nage: %d\nname:%s\n\n", GetMsgNode2->id, GetMsgNode2->age, GetMsgNode2->name);
    iNum = StdListGetSize(&lstMsgQueue);
    printf("此时队列的节点数：%d\n\n", iNum);
    return 0;
}
