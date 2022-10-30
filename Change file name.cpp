#include<io.h>
#include<direct.h>
#include"Header Files/CurrentPath.h"
#include"Header Files/FileName_Func.h"
#include"Header Files/NameList.h"
#include"Header Files/seq_algorithm.h"

int main() {
    //��ʼ��·��
    char* path = (char*)CurrentPath();

    //Windows�ļ���������<io.h>
    struct _finddata_t file;
    intptr_t   hFile;

    char filename_nonext[_MAX_PATH];

    //��ʼ�������б�
    List src_list;
    List dst_list;
    src_list.head = NULL;
    src_list.tail = NULL;
    dst_list.head = NULL;
    dst_list.tail = NULL;



    //mkv�ļ�����д��
    if (_chdir(path))
    {
        printf("open fail: %s\n", path);
    }
    //_findfirstΪwindows�ļ�����������,��һ��Ϊfilespec,�ڶ���Ϊfileinfo(��Ҫpath),������ֵΪ-1Lʱ,��˵��δƥ��
    if ((hFile = _findfirst("*.mkv", &file)) != -1L) {


        //_findnextҪ����_findfirst����,����Ϊ_findfirst���������ľ����fileinfo(��Ҫpath),������ֵΪ0ʱ,��˵��δƥ��
        do {
            add_name_inlist(&src_list, file.name);
        } while (_findnext(hFile, &file) == 0);
    }
    //_findcloseҪ��_findfirst����,����Ϊ_findfirst���������ľ��,���ڽ�������
    _findclose(hFile);




    //ass�ļ�����д��
    if (_chdir(path))
    {
        printf("open fail: %s\n", path);
    }
    //_findfirstΪwindows�ļ�����������,��һ��Ϊfilespec,�ڶ���Ϊfileinfo(��Ҫpath),������ֵΪ-1Lʱ,��˵��δƥ��
    if ((hFile = _findfirst("*.ass", &file)) != -1L) {


        //_findnextҪ����_findfirst����,����Ϊ_findfirst���������ľ����fileinfo(��Ҫpath),������ֵΪ0ʱ,��˵��δƥ��
        do {
            add_name_inlist(&dst_list, file.name);
        } while (_findnext(hFile, &file) == 0);
    }
    //_findcloseҪ��_findfirst����,����Ϊ_findfirst���������ľ��,���ڽ�������
    _findclose(hFile);


    //�г��ļ�,��ѯ�Ƿ��и��ļ�
    printf("Current .mkv files:\n");
    list_list(&src_list);
    printf("Current .ass files:\n");
    list_list(&dst_list);



    //�ļ����ƴ���
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
    

    //�ļ������滻
    int result = 1;
    if (dst_list.head != NULL) {
        Name* p = dst_list.head->next;
        if (_chdir(path))
        {
            printf("open fail: %s\n", path);
        }

        //_findfirstΪwindows�ļ�����������,��һ��Ϊfilespec,�ڶ���Ϊfileinfo(��Ҫpath),������ֵΪ-1Lʱ,��˵��δƥ��
        if ((hFile = _findfirst("*.ass", &file)) != -1L) {


            //_findnextҪ����_findfirst����,����Ϊ_findfirst���������ľ����fileinfo(��Ҫpath),������ֵΪ0ʱ,��˵��δƥ��
            do {
                result = rename(file.name, p->name);
                p = p->next;
            } while (_findnext(hFile, &file) == 0 && p != NULL);
        }
    }
    //_findcloseҪ��_findfirst����,����Ϊ_findfirst���������ľ��,���ڽ�������
    _findclose(hFile);

    printf("fianl outcome:\n");
    list_list(&dst_list);


    //��������,��ֹ�ڴ�й©
    if (src_list.head != NULL && dst_list.head != NULL) {
        free_list(&src_list);
        free_list(&dst_list);
    }


    //���ؽ��,�滻�Ƿ�ɹ�
    if (result == 0)
        printf("success\n");
    else
        printf("fail\n");

    system("pause");
    return 0;
}