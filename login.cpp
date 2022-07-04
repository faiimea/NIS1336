//
// Created by faii on 2022/7/2.
//
#include <iostream>
#include <fstream>
#include "login.h"
#include <cstring>
using namespace  std;
bool login()
{
    bool stop_flag;
    stop_flag=false;
    string user,password,pass;
    int tmp[20];
    char name[20],passwordhash[20];
    cout<<"请输入用户名：";
    getline(cin,user,'\n');
    ofstream in;
    in.open("USERS.txt",ios::app);
    FILE *f;
    f = fopen("USERS.txt", "r");
    fscanf(f,"%s\n",name);
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
        cout<<"密码正确，请输入指令：";
        return false;
    }
}
