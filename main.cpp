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

//string getTime()
//{
//    time_t timep;
//    time (&timep);
//    char tmp[64];
//    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep));
//    return tmp;
//}


int main(int argc,char **argv)
{
    user todos;
    bool stopped;
    //账户验证模块
    stopped=login(todos.id);
    //cout<<todos.id;
    //运行模块
    char buf[1024];
    int flags;
    todos.get_task();
    task unti;
    todos.insert_task(unti);
    todos.delete_task(67);
    todos.delete_task(24);
    todos.stock();

//    todos.sorttaskbytime();
//    todos.print_task_bytime();
//    cout<<endl;
//    todos.print_task_byprio();
//    cout<<endl;
//    todos.print_task_bytype();
//    cout<<endl;

    // 设置标准输入为非阻塞模式
    /*int fd = fileno(stdin);
    flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);

    memset(buf,0, sizeof(buf));

    // 循环等待输入
    if(!stopped)    printf("Enter name: ");
    while(!stopped)
    {
        int waitSeconds = 30;
        //这里的30s可以测试一下，我觉得1s就可以了ww
        while(waitSeconds > 0)
        {
            --waitSeconds;
            char *p;
            p = fgets(buf, sizeof(buf), stdin);
            if (p != nullptr)
                break;
            sleep(1);
        }
        //命令读取模块

        waitSeconds = 30;
    }
    todos.stock();*/
    return 0;
}