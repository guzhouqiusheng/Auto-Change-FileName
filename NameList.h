#pragma once
#include<stdlib.h>
#include"FileName_Func.h"

//define a struct linked list
typedef struct _name {
    char name[_MAX_PATH];
    char ext[5];
    int seq_num[10];
    int seq;
    //the pointer point to last structure
    struct _name* last;
    //the pointer point to next structure
    struct _name* next;
}Name;

//define a struct list,record num_head and num_tail
typedef struct _list {
    Name* head;
    Name* tail;
}List;





//向链表内添加文件名称
void add_name_inlist(List* pList, char* filename) {
    if (pList->head == NULL) {
        Name* head = (Name*)malloc(sizeof(Name));
        Name* tail = (Name*)malloc(sizeof(Name));
        Name* p = (Name*)malloc(sizeof(Name));

        if (p != NULL) {
            sprintf_s(p->name, _MAX_PATH, "%s", FileName_NonExt(filename, p->name));
            sprintf_s(p->ext, 5, "%s", FileName_Ext(filename, p->ext));
            p->last = head;
            p->next = NULL;
        }

        if (head != NULL)
            head->next = tail = p;

        //将head与tail传出至List name中
        pList->head = head;
        pList->tail = tail;
    }
    else {
        Name* p = (Name*)malloc(sizeof(Name));
        if (p != NULL) {
            sprintf_s(p->name, _MAX_PATH, "%s", FileName_NonExt(filename, p->name));
            sprintf_s(p->ext, 5, "%s", FileName_Ext(filename, p->ext));
            //将旧p地址存入新p地址的last里
            p->last = pList->tail;
            p->next = NULL;
            //旧p地址中的next连接至新p地址
            pList->tail->next = p;
            //tail变量的地址即为新p变量的地址
            pList->tail = p;
        }
    }
}


void rename_list(List* src_pList, List* dst_pList) {
    Name* p = (Name*)malloc(sizeof(Name));
    Name* q = (Name*)malloc(sizeof(Name));
    p = src_pList->head;
    for (p = p->next; p; p = p->next) {
        q = dst_pList->head;
        for (q = q->next; q; q = q->next) {
            if (p->seq == q->seq) {
                sprintf_s(q->name, _MAX_PATH, "%s%s", p->name, q->ext);
                break;
            }
        }
    }
}

void free_list(List* pList) {
    Name* p = (Name*)malloc(sizeof(Name));
    if (p != NULL)
        p = pList->head;
    //让head等于head->next,然后释放p,也就是原先的head,直至tail,此时tail并未被释放
    for (pList->head = pList->head->next; pList->head; pList->head = pList->head->next)
    {
        free(p);
        p = pList->head;
    }
    //释放刚刚未能释放的tail
    free(pList->tail);
    //使得head为NULL,防止任何内存泄漏
    //free(pList->head);
}

void list_list(const List* pList) {
    Name* p = pList->head;
    if (pList->head) {
        for (p = p->next; p; p = p->next) {
            printf_s("%s%s\n", p->name,p->ext);
        }
    }
    else
        printf("fial to find files");
    printf_s("\n");
}