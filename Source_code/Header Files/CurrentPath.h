#pragma once
#include<stdio.h>
#include<Windows.h>

//获取当前路径
char* CurrentPath() {
	char* path = (char*)malloc(sizeof(char) * 260);
	if (path != NULL) {
		GetModuleFileNameA(NULL, path, 260);
	}
	else {
		printf("not enough memory!");
		return 0;
	}
	if (path != NULL) {
		for (int i = strlen(path) - 1; i > 0; i--) {
			if (path[i] == '\\') {
				path[i] = '\0';
				break;
			}
		}
	}
	else {
		printf("not enough memory!");
		return 0;
	}
	return path;
}