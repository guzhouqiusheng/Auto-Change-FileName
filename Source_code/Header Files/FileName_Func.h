#pragma once
#include<stdio.h>
#include<string.h>

char* FileName_Ext(char* FileName, char* ext) {
    if (FileName != NULL && ext != NULL) {
        for (int i = strlen(FileName) - 1; i > 0; i--) {
            if (FileName[i] == '.') {
                int cnt = i;
                for (int i = 0; i <= 4; i++) {
                    *(ext + i) = *(FileName + cnt + i);
                }
                break;
            }
        }
    }
    return ext;
}


//没有后缀的文件名
char* FileName_NonExt(char* FileName, char* filename_nonext) {
    if (FileName != NULL && filename_nonext != NULL) {
        for (int i = strlen(FileName) - 1; i > 0; i--) {
            if (FileName[i] == '.') {
                sprintf_s(filename_nonext, _MAX_PATH, "%s", FileName);
                filename_nonext[i] = '\0';
                break;
            }
        }
    }
    return filename_nonext;
}

//将后缀名添加上
char* FileName_AddExt(char* filename, char* ext) {
    char buf[_MAX_PATH];
    sprintf_s(buf, _MAX_PATH, "%s%s", filename, ext);
    sprintf_s(filename, _MAX_PATH, "%s", buf);
    return filename;
}