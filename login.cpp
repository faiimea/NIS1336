//
// Created by faii on 2022/7/2.
//
#include <iostream>
#include <fstream>
#include "login.h"
#include <cstring>
using namespace  std;
bool login(int &num)
{
    bool stop_flag;
    stop_flag=false;
    string user,password,pass;
    int tmp[20];
    char name[20],passwordhash[20],id[10];
    cout<<"请输入用户名：";
    getline(cin,user,'\n');
    FILE *f;
    f = fopen("USERS.txt", "r");
    fscanf(f,"%s\n",name);
    ofstream in;
    in.open("USERS.txt",ios::app);
    if (ftell(f)==0)
    {
        in<<"用户名："<<user<<'\n';
        cout<<"新用户已创建，请输入密码：";
        getline(cin,password,'\n');
        int i;
        for (i=0;i<password.length();i++)
        {
            tmp[i]=((password[i])+23)%128;
        }
        for (int j=0;j<i;j++)
        {
            passwordhash[j]=char(tmp[j]);
            in<<passwordhash[j];
        }
        in<<'\n';
        in<<"000";
        num=0;
    }
    else
    {
        cout<<"请输入密码:";
        getline(cin,pass,'\n');
        fscanf(f,"\n%s\n",passwordhash);
        int i;
        for ( i=0;i<pass.length();i++)
        {
            if (char((pass[i]+23)%128)!=passwordhash[i])
            {cout<<"密码错误！";return true;}
        }
        if (i<strlen(passwordhash))
        {cout<<"密码错误！";return true;}
        cout<<"****************密码正确，欢迎使用日程管理系统！****************"<<endl;
        cout<<"任务属性优先级从低到高为1，2，3；任务类型按类型学习，娱乐，生活分别为1，2，3"<<endl;
        cout<<"****************输入数字指令进入相应软件功能：******************"<<endl;
        cout<<"1.添加任务    输入格式：1--类型-优先度-开始时间-提醒时间"<<endl;
        cout<<"****例如：1--2 3 2022-07-07-14-30-00 2022-07-07-14-25-00（系统将自动为您生成对应id）"<<endl;
        cout<<"2.删除任务    输入格式：2--任务ID    例如：2--006（ID以3位数形式输入）"<<endl;
        cout<<"3.按时间打印任务    输入格式：3     将按输入的提醒时间从早到晚打印任务"<<endl;
        cout<<"4.按优先级打印任务   输入格式：4     将按优先级从高到低打印任务"<<endl;
        cout<<"5.按类型打印任务    输入格式：5     将按类型生活，娱乐，学习依次打印任务"<<endl;
        cout<<"6.取消            输入格式：6      取消输入内容，重新进入命令行"<<endl;
        cout<<"7.退出            输入格式：7      退出并保存"<<endl;
        fscanf(f,"%s\n",id);
        num=0;
        for (int j=0;j<strlen(id);j++)
        {
            num=10*num+id[j]-48;
        }
    }
    return false;
}
