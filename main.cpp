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



string getTime()
{
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep));
    return tmp;
}


int main()
{
    user todos;
    string   time = getTime();
    cout << time << endl;
    bool stopped;
    //账户验证模块
    stopped=login();

    //运行模块
    char buf[1024];
    int flags;


    // 设置标准输入为非阻塞模式
    int fd = fileno(stdin);
    flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);

    memset(buf,0, sizeof(buf));

    // 循环等待输入
    if(!stopped)    printf("Enter name: ");
    while(!stopped)
    {
        int waitSeconds = 1;
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
        //分析指令：待完成
        todos.test();
        waitSeconds = 1;
    }

    return 0;
}