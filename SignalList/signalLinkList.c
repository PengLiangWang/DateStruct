#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int elemType;

typedef struct Node{
    elemType element;
    struct Node *next;
}Node;


/* 找到一个节点的上一个节点*/
static Node *findPre(Node *pHead, Node *p)
{
    Node *q;

    q = pHead;

    while(q->next != p)
    {
        q = q->next; 
    }
    return q;
}


/* 1.初始化线性表，即置单链表的表头指针为空 */
static void initList(Node **pNode)
{
    *pNode = NULL;
    printf("initList函数执行, 初始化成功\n");
}

/* 2.创建线性表，此函数输入负数终止读取数据*/
static Node *createList(Node *pHead)
{
    Node *p1;
    Node *p2;

    printf("创建链表,请输入整数值(<0退出)\n");
    p1=p2=(Node *)malloc(sizeof(Node));  //申请新节点
    if(p1 == NULL || p2 == NULL)
    {
        printf("内存分配失败\n");
        exit(0);
    }
    memset(p1, 0x00, sizeof(Node));
    scanf("%d", &p1->element);

    p1->next = NULL;   //(head)节点指向为空
    while(p1->element > 0) 
    {
        if(pHead == NULL)    //空表, 接入表头
        {
             pHead = p1;    //链表头指向 p1 的位置
        }
        else
        {
            p2->next = p1;
        }
        p2 = p1;   //将p2指向p1的位置，而p1去做其他事情
        p1 = (Node *)malloc(sizeof(Node));
        if(p1 == NULL || p2 == NULL)
        {
             printf("内存分配失败\n");
             exit(0);
        }
        memset(p1, 0x00, sizeof(Node));
        scanf("%d", &p1->element);
        p1->next = NULL;   //(head)节点指向为空
    }
    printf("链表创建成功\n");
    return pHead;
}

/*打印列表*/
static void printList(Node *pHead)
{
     if(NULL == pHead)
     {
         printf("PrintList执行成功, 链表为空\n");
     }
     else
     {
         printf("链表内容:\n");
         while(NULL != pHead)
         {
             if(NULL != pHead->next)
                 printf("%d->", pHead->element);
             else
                 printf("%d", pHead->element);
             pHead = pHead->next;
         }
         printf("\n");
     }

}

static void delete_linkList(Node *pHead)
{
    Node *p = pHead->next;
    if(p == NULL)
        return;
    pHead->next = p->next;  //相当于pHead->next 指向 pHead->next->next
    free(p);
    p=NULL;
    return;
}


static void clear_linkList(Node *pHead)
{
    while(pHead->next)
        delete_linkList(pHead);
    return;
}

static void display_linkList(Node *pHead)
{
    clear_linkList(pHead);
    free(pHead);    //先清空链表,再释放头结点
    pHead=NULL;
    return;
}

/*打印链表的长度*/
static int sizeList(Node *pHead)
{
    int size=0;

    while(NULL != pHead)
    {
        size ++;
        pHead = pHead->next;
    }
    return size;
}

/*判断链表是否为空*/
static  int isEmptyList(Node *pHead)
{
    if(pHead == NULL)
    {
        printf("链表为空\n");
        return 1;
    }
    printf("链表非空\n");
    return 0;
}

/*获取链表某个位置的值*/
static elemType getelement(Node *pHead, int pos)
{
    int i=0;

    if(pos < 1)
    {
        printf("pos值非法.\n");
        return 0;
    }
    if(NULL == pHead)
    {
        printf("链表为空.\n");
        return 0;
    }
    while(NULL != pHead)
    {
        ++i;
        if(i == pos)
        {
            break;
        }
        pHead = pHead->next;
    }
    if(i < pos)
    {
        printf("pos值超过链表的最大长度.\n");
        return 0;
    }
    return pHead->element;
}

/*从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL*/
elemType *getElemAddr(Node *pHead, elemType x)
{

    elemType icount=1; 
    if(NULL == pHead)
    {
        printf("链表为空\n");
        return NULL;
    }
    if(x < 0)
    {
        printf("x值不合法\n");
    }

    while(pHead->element != x && NULL != pHead->next)
    {
        ++ icount ;
        pHead=pHead->next;
    }
    if(pHead->element != x && NULL != pHead)
    {
        printf("链表中不存在 %d\n", x);
        return NULL;
    }
    if(pHead->element == x)
    {
        printf("getElement函数执行, 元素 %d 的地址为 0x%x, 在链表中的位置: %d\n", x, &(pHead->element), icount);
    }

    return &(pHead->element);
}


/*把单链表中第pos个结点的值修改为x的值，若修改成功返回１，否则返回０*/
static int modifyElem(Node *pHead, int pos, elemType x)
{
    int i = 0;

    if(NULL == pHead)
    {
        printf("链表为空\n");
        return 0;
    }
    if(pos < 1)
    {
        printf("pos值非法\n");
        return 0;
    }

    while(pHead != NULL)
    {
        ++ i;
        if(i == pos)
        {
            break; 
        }
        pHead=pHead->next;
    }
    if(i<pos)
    {
        printf("pos值非法\n");
        return 0;
    }
    pHead->element = x;   //指针的位置没有改变, 只修改了存储内容
    return 1;
}

/*向单链表的表头插入一个元素*/
static int insertHeadList(Node **pNode, elemType insertElem)
{
    Node *pInsert;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert, 0x00, sizeof(Node));
    pInsert->element=insertElem;
    pInsert->next=*pNode;
    *pNode = pInsert;        
    printf("表头插入节点成功.\n");
    
    return 1;
}

/*向单链表的末尾添加一个元素*/
static int insertLastList(Node **pNode, elemType insertElem)
{
    Node  *pInsert;
    Node  *pHead;
    Node  *pTemp;     //定义一个临时链表用来存放第一个节点地址

    pHead = *pNode;
    pTemp = pHead;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert, 0x00, sizeof(Node));
    pInsert->element=insertElem;

    while(NULL != pHead->next)
    {
        pHead=pHead->next;
    }
    pHead->next=pInsert;
    *pNode = pTemp;
    printf("向链表尾部插入节点成功.\n");

    return 1;
}

/*向单链表中第pos个结点位置插入元素为x的结点，若插入成功返回１，否则返回０*/
static int insertPosList(Node **pNode, int pos,  elemType insertElem) 
{
    Node *pInsert;
    Node *pHead;
    Node *pTemp;
    int  i=1;

    pHead = *pNode;
    pTemp = pHead;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert, 0x00, sizeof(Node));
    pInsert->element=insertElem;

    if(NULL == pHead)
    {
        printf("链表为空\n");
        return 0;
    }
    if(pos < 1)
    {
        printf("pos值非法\n");
        return 0;
    }
    if(pos == 1)
    {
        insertHeadList(pNode, insertElem);   //如果pos等于1, 调用向表头insert一个新节点函数 
        return 1;
    }

    while(pHead != NULL)
    {
        ++ i;
        if(i == pos)
            break;
        pHead=pHead->next;
    }
    if(i<pos)
    {
        printf("pos值无效.\n");
        return 0;
    }
    pInsert->next = pHead->next;
    pHead->next = pInsert;
    *pNode = pTemp;

    return 1;
}

/* 13.向有序单链表中插入元素x结点，使得插入后仍然有序 */
static int insertOrderList(Node **pNode, elemType insertElem)
{
    Node *pInsert;
    Node *pHead;
    Node *pTemp;
    int  i=1;

    pHead = *pNode;
    pTemp = pHead;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert, 0x00, sizeof(Node));
    pInsert->element=insertElem;
    if(NULL == pHead)
    {
        printf("链表为空\n");
        return 0;
    }
    while(NULL != pHead)
    {
        ++i;
        if(pHead->element >= insertElem)
            break;
        pHead=pHead->next;
    }
    if(NULL == pHead)
    {
       insertLastList(pNode, insertElem);   //如果已经比较到链表最后, 直接调用插入新节点到链表最后    
       return 1;
    }

    insertPosList(pNode, --i, insertElem);    //找到前一个节点的位置，然后添加新节点
    
    return 1;
}
/* 14.从单链表中删除表头结点，并把该结点的值返回，若删除失败则停止程序运行 */
static int deleteHeadList(Node **pNode)
{
    Node       *pHead;
    elemType   elem;  
    pHead = *pNode;
    if(NULL == pHead)
    {
        printf("链表为空\n");
        return 0;
    }
    *pNode = pHead->next;
    elem = pHead->element;
    free(pHead);

    printf("已删除头节点: %d\n", elem);
    return elem;
}

/* 15.从单链表中删除表尾结点并返回它的值，若删除失败则停止程序运行 */
static int deleteLastList(Node **pNode)
{
    Node *pHead;
    Node *pTemp;

    pHead = *pNode;
    pTemp = pHead;
    
    if(NULL == pHead)
    {
        printf("链表为空.\n");
        return 0;
    }
    while(NULL != pHead->next->next)
    {
        pHead = pHead->next; 
    }
    //跳出循环是pHead指向尾节点的前一个节点
    printf("删除链表最后一个节点值: %d\n", pHead->next->element);   
    delete_linkList(pHead);    //调用删除下一个节点的函数
    /*
    Node *p=pHead->next;
    pHead->next = p->next;
    free(p);
    */
    *pNode = pTemp;
    return 1;
}

/* 16.从单链表中删除第pos个结点并返回它的值，若删除失败则停止程序运行 */
static int deletePosList(Node **pNode, int pos)
{   
    Node *pHead;
    Node *pTemp;
    int  i = 1;

    pHead = *pNode;
    pTemp = pHead;
    if(NULL == pHead)
    {
        printf("链表为空.\n");
        return 0;
    }
    if(pos == 1)
    {
        deleteHeadList(pNode);  //调用删除头节点
        return 1;
    }
    while(NULL != pHead->next)   
    {
        ++i;
        if(i == pos)
            break;
        pHead = pHead->next;
    } //i=5的时候, pHead才指向第4个
    if(i<pos)
    {
        printf("pos非法. i=%d, pos=%d\n", i, pos);
        return 0;
    }

    delete_linkList(pHead);    //调用删除下一个节点的函数
    *pNode = pTemp;

    return 1;
}


/* 17.从单链表中删除值为x的第一个结点，若删除成功则返回1,否则返回0 */
static int deleteEqualList(Node **pNode, elemType delelem)
{
    Node *pHead;
    Node *pTemp;
    int  i = 0;

    pHead = *pNode;
    pTemp = pHead;
    if(NULL == pHead)
    {
        printf("链表为空.\n");
        return 0;
    }
    while(NULL != pHead)
    {
        ++ i;
        if(pHead->element == delelem)
            break;
         pHead = pHead->next;
    }
    if(i == 1)
    {
        deleteHeadList(pNode);   //删除第一个节点
        return 1;
    }
    if(NULL == pHead)
    {
        printf("链表中未找到此节点值: %d\n", delelem);
        return 1;
    }

    *pNode = pTemp;
    //节点删除
    deletePosList(pNode, i);
    return 1;
}

/* 18.交换2个元素的位置 */
static int ChangePosList(Node *pHead, int pos1, int pos2)
{
    Node *p, *q;
    int  i=0, j=0;

    p = q = pHead;

    if(pHead == NULL)
    {
        printf("链表为空.\n");
        return 0;
    }
    if(pos1 < 1 || pos2 < 1 || pos1 > sizeList(pHead) || pos2 > sizeList(pHead))
    {
        printf("pos值非法.\n");
        return 0;
    }
    if(pos1 == 1 || pos2 == 1)
    {
        printf("其中一个节点为头节点, 不做交换.\n");
        return 0;
    }
    if(pos1 == pos2)
    {
        printf("两节点指向同一个地方, 不需交换.\n");
        return 0;
    }
    if(getelement(pHead, pos1) == getelement(pHead, pos2))
    {
        printf("两节点存放的内容相同, 不需交换.\n");
        return 0;
    }
    while(NULL != p)
    {
        ++ i;
        if(i == pos1) 
            break;
        p=p->next;
    }
    while(NULL != q)
    {
        ++ j;
        if(j == pos2)
            break;
        q=q->next;
    }
    
    if(p->next == q)
    {
        Node *pre_p=findPre(pHead, p);
        pre_p->next = q;
        p->next = q->next;
        q->next = p;
    }
    else if(q->next == p)
    {
        Node *pre_q = findPre(pHead, q);
        pre_q->next = p;
        q->next = p->next;
        q->next = q;
    }
    else
    {
        Node *pre_p = findPre(pHead, p);
        Node *pre_q = findPre(pHead, q);
        Node *after_p = p->next;

        p->next = q->next;
        q->next = after_p;
        pre_p->next = q;
        pre_q->next = p;
    }

    return 1;
}


/* 19.将对链表进行快速排序 ,冒泡排序*/
static int SortList(Node **pNode)
{
    Node *pHead;
    Node *pTemp;
    elemType Temp;
    int i, j;
     
    pHead = *pNode;
    pTemp = pHead;

    if(pHead == NULL)
    {
        printf("链表为空.\n");
        return 0;
    }
    for(i=1; i<=sizeList(pTemp); i++)
    {
        for(j=i+1; j<=sizeList(pTemp); j++)
        {
            if(getelement(pTemp, i) > getelement(pTemp, j))    
            {
                ChangePosList(pTemp, i, j);
            }
        }
    }
    *pNode = pTemp;
     return 1;
}

/*20. 链表反转 */
static int Reverse(Node **pNode)
{
    Node *p, *q;
    Node *pHead;

    pHead = *pNode;

    p = pHead->next;
    pHead->next = NULL;   //头节点和后面断开

    while(p != NULL)
    {
        q=p;
        p=p->next;
        q->next = pHead->next;  //截断放到新的pHead开头的链表中
        pHead->next = q;
    }
    elemType insertelem;
    insertelem = deleteHeadList(pNode);    //头结点删除
    insertLastList(pNode, insertelem);     //将头节点接连到链表的尾部
    return 1;
}


int main(int argc, char *argv[])
{
    
    Node *pList=NULL;
    int length=0;

    elemType posElem;

    printf("********初始化链表**********\n");
    initList(&pList);
    printList(pList);

    printf("\n********创建链表**********\n");

    pList = createList(pList);
    printList(pList);
   
    isEmptyList(pList);
    printf("sizeList函数执行, 链表长度: %d\n", sizeList(pList));

    printf("\n********获取链表某个位置的值**********\n");
    posElem = getelement(pList, 3);
    printf("在链表位置3的地方存放的数据是: %d\n", posElem);

    
    printf("\n********获取链表中某个值的地址**********\n");
    getElemAddr(pList, 8);


    printf("\n*********在插入新节点保持有序性*********\n");
    insertOrderList(&pList, 4);
    printList(pList);


    printf("\n*********修改某个节点的值*********\n");
    modifyElem(pList, 5, 99);
    printList(pList);

    printf("\n*********链表头插入节点*********\n");
    insertHeadList(&pList, 22);
    printList(pList);


    printf("\n*********链表尾部插入节点*********\n");
    insertLastList(&pList, 33); 
    printList(pList);

    printf("\n*********在pos的位置插入新节点*********\n");
    insertPosList(&pList, 2, 44);
    printList(pList);

    printf("\n*********删除头节点*********\n");
    deleteHeadList(&pList);
    printList(pList);

    printf("\n*********删除尾节点*********\n");
    deleteLastList(&pList);
    printList(pList);

    printf("\n*********删除pos位置的节点*********\n");
    deletePosList(&pList, 5);
    printList(pList);

    printf("\n*********删除值为x的第一个节点*********\n");
    deleteEqualList(&pList, 3);
    printList(pList);

    
    printf("\n*********链表反转*********\n");
    Reverse(&pList);
    printList(pList);

    
    printf("\n*********交换两个位置的值(除头节点)*********\n");
    ChangePosList(pList, 2,5);
    printList(pList);

    printf("\n*********链表排序(除头节点)*********\n");
    SortList(&pList);
    printList(pList);

    printf("\n*********清空链表*********\n");
    display_linkList(pList);
    pList=NULL;
    printList(pList);

    return 0;
}
