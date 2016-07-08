#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int DataType;

typedef struct distnode{
    DataType data;
    struct distnode *prior, *next;
}DListNode;

//创建双链表
DListNode *createDLink()
{
    DListNode *head, *p, *s;
    int x;
    head = (DListNode *)malloc(sizeof(DListNode));
    p = head;
    while(1)
    {
        printf("Please input the data: ");
        scanf("%d",&x);
        if(x != 0)
        {
            s = (DListNode *)malloc(sizeof(DListNode));
            s->data = x;
            s->prior = p;
            p->next = s;
            p = s;
        }
        else
            break;
    }
    p->next = NULL;
    head = head->next;
    head->prior = NULL;
}

//打印双链表
void printDLink(DListNode *head)
{
    DListNode *p, *s;
    p=head;

    printf("left to right: \n");
    while(p)
    {
        printf("%d ", p->data);
        s=p;
        p=p->next;
    }

    printf("\nright to left: \n");
    while(s)
    {
        printf("%d ", s->data);
        s = s->prior;
    }
    printf("\n\n");
}

//删除一个节点
DListNode *DeleteDLink(DListNode *head, int i)
{
    DListNode *p;
    p = head;
    
    if(p->data == i)     // i为头节点
    {
        head = p->next;
        head->prior = NULL;
        free(p);
        return head;
    }
     
    while(p)                   
    { 
        if(p->next == NULL && p->data == i)    //i 为尾节点
        {
            printf("p节点为尾节点.\n");
            p->prior->next = NULL;
            free(p);
            return head;

        }

        if(p->data == i)   //i 不为头结点且不为尾节点
        {
            p->prior->next = p->next;
            p->next->prior = p->prior;
            free(p);
            return head;
        }
        p = p->next;
        
    }
    printf("not found %d\n\n", i);
    return head;
}

//后插入操作
void DInsertBack(DListNode *head, DataType addr, DataType x)
{
    DListNode *p;
    p = head;

    while(p)
    {
        if(p->data == addr)
        {
            DListNode *s = (DListNode *)malloc(sizeof(DListNode));
            if(p->next != NULL)   //p不是尾节点
            {
                s->data = x;
                s->prior = p;
                s->next = p->next;
                p->next->prior = s;
                p->next = s;
            }
            else     //p为尾节点
            {
                s->data = x;
                s->prior = p;
                s->next = NULL;
                p->next = s;
            }
        }
        p = p->next;
    }
}

/* 在带头结点的双链表的前插入操作 在元素 addr 之前插入x元素*/
DListNode *DInsertBefore(DListNode *head, DataType addr, DataType x)
{
    DListNode *p;

    p = head;

    if(p->data == addr)
    {
        DListNode *s = (DListNode *)malloc(sizeof(DListNode));
        s->data = x;
        head = s;
        head->next=p;
        head->prior = NULL;
        p->prior = head;
        return head;
    }

    while(p)
    {
        if(p->data == addr)
        {
            DListNode *s = (DListNode *)malloc(sizeof(DListNode));
            s->data = x;
            s->prior = p->prior;  //s的前驱值指向 p原来的前驱
            s->next = p;
            p->prior->next = s;
            p->prior = s;
            return head;
        }
        p=p->next;
    }
    return head;
}

int main(int argc, char *argv[])
{
    DListNode *head;
    
    head = createDLink();
    printDLink(head);

    DInsertBack(head, 5, 11);  //2节点后插入11
    printDLink(head);

    head = DInsertBefore(head, 3, 9);  //把第一个等于3的节点之前插入9
    printDLink(head);

    head = DeleteDLink(head, 2); //删除等于2的节点
    printDLink(head);

    return 0;
}
