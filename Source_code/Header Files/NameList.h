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





//������������ļ�����
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

        //��head��tail������List name��
        pList->head = head;
        pList->tail = tail;
    }
    else {
        Name* p = (Name*)malloc(sizeof(Name));
        if (p != NULL) {
            sprintf_s(p->name, _MAX_PATH, "%s", FileName_NonExt(filename, p->name));
            sprintf_s(p->ext, 5, "%s", FileName_Ext(filename, p->ext));
            //����p��ַ������p��ַ��last��
            p->last = pList->tail;
            p->next = NULL;
            //��p��ַ�е�next��������p��ַ
            pList->tail->next = p;
            //tail�����ĵ�ַ��Ϊ��p�����ĵ�ַ
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
    //��head����head->next,Ȼ���ͷ�p,Ҳ����ԭ�ȵ�head,ֱ��tail,��ʱtail��δ���ͷ�
    for (pList->head = pList->head->next; pList->head; pList->head = pList->head->next)
    {
        free(p);
        p = pList->head;
    }
    //�ͷŸո�δ���ͷŵ�tail
    free(pList->tail);
    //ʹ��headΪNULL,��ֹ�κ��ڴ�й©
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