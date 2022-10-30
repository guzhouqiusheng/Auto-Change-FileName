#pragma once
#include"Namelist.h"

int pow(int number, int n);

void number_extract(List* pList) {
    Name* p = (Name*)malloc(sizeof(Name));
    p = pList->head;
    if (p != NULL) {
        for (p = p->next; p; p = p->next) {
            int seq = 0;
            for (int i = 0; i < _MAX_PATH && p->name[i] != '\0'; i++) {
                if (p->name[i] >= '0' && p->name[i] <= '9') {
                    int cnt = i;
                    int seq_num = 0;
                    while (p->name[cnt] >= '0' && p->name[cnt] <= '9') {
                        cnt++;
                    }
                    for (int x = i; x < cnt; x++) {
                        //char型数字,数值为48起始char表示0
                        seq_num += (p->name[x] - 48) * pow(10, cnt - x - 1);
                    }
                    if (seq_num != 0) {
                        i = cnt - 1;
                        p->seq_num[seq] = seq_num;
                        seq++;
                    }
                }
            }
        }
    }
    else
        printf("no linked list\n");
}

void match_algorithm(List* pList) {
    Name* p = (Name*)malloc(sizeof(Name));
    Name* q = (Name*)malloc(sizeof(Name));
    p = pList->head;
    int seq = 0;
    while (q) {
        p = pList->head;
        for (p = p->next; p->next; p = p->next) {
            int cnt = 0;
            if (p->seq_num[seq] == p->next->seq_num[seq]) {
                cnt++;
            }
            if (cnt == 0) {
                q = pList->head;
                for (q = q->next; q; q = q->next) {
                    q->seq = q->seq_num[seq];
                }
            }
        }
        seq++;
    }
}

int pow(int number, int n) {
    int result = 1;
    while (n) {
        result *= number;
        n--;
    }
    return result;
}