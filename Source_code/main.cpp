#include<io.h>
#include<direct.h>
#include"Header Files/CurrentPath.h"
#include"Header Files/FileName_Func.h"
#include"Header Files/NameList.h"
#include"Header Files/seq_algorithm.h"

int main() {
    //初始化路径
    char* path = (char*)CurrentPath();

    //Windows文件搜索函数<io.h>
    struct _finddata_t file;
    intptr_t   hFile;

    char filename_nonext[_MAX_PATH];

    //初始化名称列表
    List src_list;
    List dst_list;
    src_list.head = NULL;
    src_list.tail = NULL;
    dst_list.head = NULL;
    dst_list.tail = NULL;



    //mkv文件名称写入
    if (_chdir(path))
    {
        printf("open fail: %s\n", path);
    }
    //_findfirst为windows文件名搜索函数,第一个为filespec,第二个为fileinfo(需要path),当返回值为-1L时,则说明未匹配
    if ((hFile = _findfirst("*.mkv", &file)) != -1L) {


        //_findnext要接在_findfirst后用,参数为_findfirst保存下来的句柄和fileinfo(需要path),当返回值为0时,则说明未匹配
        do {
            add_name_inlist(&src_list, file.name);
        } while (_findnext(hFile, &file) == 0);
    }
    //_findclose要在_findfirst后用,参数为_findfirst保存下来的句柄,用于结束进程
    _findclose(hFile);




    //ass文件名称写入
    if (_chdir(path))
    {
        printf("open fail: %s\n", path);
    }
    //_findfirst为windows文件名搜索函数,第一个为filespec,第二个为fileinfo(需要path),当返回值为-1L时,则说明未匹配
    if ((hFile = _findfirst("*.ass", &file)) != -1L) {


        //_findnext要接在_findfirst后用,参数为_findfirst保存下来的句柄和fileinfo(需要path),当返回值为0时,则说明未匹配
        do {
            add_name_inlist(&dst_list, file.name);
        } while (_findnext(hFile, &file) == 0);
    }
    //_findclose要在_findfirst后用,参数为_findfirst保存下来的句柄,用于结束进程
    _findclose(hFile);


    //列出文件,查询是否有该文件
    printf("Current .mkv files:\n");
    list_list(&src_list);
    printf("Current .ass files:\n");
    list_list(&dst_list);



    //文件名称处理
    if (src_list.head != NULL) {
        number_extract(&src_list);
        match_algorithm(&src_list);
    }
    
    if (dst_list.head != NULL) {
        number_extract(&dst_list);
        match_algorithm(&dst_list);
    }

    if (src_list.head != NULL && dst_list.head != NULL) {
        rename_list(&src_list, &dst_list);
    }
    

    //文件名称替换
    int result = 1;
    if (dst_list.head != NULL) {
        Name* p = dst_list.head->next;
        if (_chdir(path))
        {
            printf("open fail: %s\n", path);
        }

        //_findfirst为windows文件名搜索函数,第一个为filespec,第二个为fileinfo(需要path),当返回值为-1L时,则说明未匹配
        if ((hFile = _findfirst("*.ass", &file)) != -1L) {


            //_findnext要接在_findfirst后用,参数为_findfirst保存下来的句柄和fileinfo(需要path),当返回值为0时,则说明未匹配
            do {
                result = rename(file.name, p->name);
                p = p->next;
            } while (_findnext(hFile, &file) == 0 && p != NULL);
        }
    }
    //_findclose要在_findfirst后用,参数为_findfirst保存下来的句柄,用于结束进程
    _findclose(hFile);

    printf("fianl outcome:\n");
    list_list(&dst_list);


    //清理链表,防止内存泄漏
    if (src_list.head != NULL && dst_list.head != NULL) {
        free_list(&src_list);
        free_list(&dst_list);
    }


    //返回结果,替换是否成功
    if (result == 0)
        printf("success\n");
    else
        printf("fail\n");

    system("pause");
    return 0;
}