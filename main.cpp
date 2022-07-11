//
// Created by faii on 2022/7/2.
//

#include <fstream>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <time.h>
#include "tasks.h"
#include "login.h"
using namespace std;

//主函数
int main(int argc,char **argv)
{

    //————————————————————————————————————————账号登录阶段————————————————————————————————————————

    //初始化账号管理模块
    users admin;

    //初始化任务管理模块
    user todos;
    bool al_run;al_run=false;
    bool stopped=false;

    //获取程序已储存的用户信息
    admin.user_get();

    //登录注册阶段
    stopped=admin.user_load();
    todos.no=admin.mem_no;
    todos.id=admin.todo_mems[admin.mem_no].mem_id;
    if(stopped)
    {
        cout<<"程序退出"<<endl;
        return 0;
    }

    //从文本文件中获取该用户的任务信息
    todos.filename_get();
    todos.get_task();
    todos.update();

    //————————————————————————————————————————程序运行阶段————————————————————————————————————————

    // 非阻塞输入设置
    char buf[1024];
    int flags;
    int fd = fileno(stdin);
    flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);
    memset(buf,0, sizeof(buf));

    // 循环等待输入
    if(!stopped)    printf("请输入命令: ");
    while(!stopped)
    {
        int waitSeconds = 10;
        while(waitSeconds > 0)
        {
            --waitSeconds;
            char* p;
            p = fgets(buf, sizeof(buf), stdin);
            if (p != nullptr)
            {
                strcpy(todos.order,p);
                cout<<todos.order<<endl;
                al_run=true;
                break;
            }
            sleep(1);
        }
        //命令读取模块
        stopped=todos.load();
        //任务检测
        todos.remind();
        waitSeconds = 10;
        if(al_run&&!stopped)
        {
            printf("请输入命令: ");
            memset(todos.order,'\0',sizeof(todos.order));
            al_run=false;
        }
    }

    //将程序修改的内容重新存储回本地文件
    admin.todo_mems[admin.mem_no].mem_id=todos.stock();
    admin.user_stock();
    cout<<endl;
    cout<<"已成功保存"<<endl;
    cout<<"退出程序"<<endl;
    return 0;
}