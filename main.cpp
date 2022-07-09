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

int main(int argc,char **argv)
{
    user todos;
    bool al_run;al_run=false;
    bool stopped=false;
    //账户验证模块
    stopped=login(todos.id);
    //运行模块
    char buf[1024];
    int flags;
    todos.get_task();
    todos.update();
    // 设置标准输入为非阻塞模式
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
        //记得把这里改回来10
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
        todos.remind();
        waitSeconds = 10;
        if(al_run&&!stopped)
        {
            printf("请输入命令: ");
            memset(todos.order,'\0',sizeof(todos.order));
            al_run=false;
        }
    }
    todos.stock();
    cout<<endl;
    cout<<"已成功保存"<<endl;
    cout<<"退出程序"<<endl;
    return 0;
}