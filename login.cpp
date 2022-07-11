//
// Created by faii on 2022/7/2.
//

#include "login.h"
using namespace  std;

//将本地的用户信息导入程序
void users::user_get()
{
    ifstream in;
    in.open("USERS.txt");
    int a1,a2,a3;
    a1=in.get()-48;
    a2=in.get()-48,a3=in.get()-48;
    user_num=100*a1+10*a2+a3;
    in.get();
    for(int i=1;i<=user_num;++i)
    {
        int a4,a5,a6;
        a4=in.get()-48;
        a5=in.get()-48,a6=in.get()-48;
        todo_mems[i].mem_no=100*a4+10*a5+a6;
        in.get();
        char x=in.get();
        int j=0;
        while(x!='\n')
        {
            todo_mems[i].mem_name+=x;
            x=in.get();
        }
        //todo_mems[i].mem_name+='\0';
        //这里以前有;'\0'
        j=0;
        x=in.get();
        while(x!='\n')
        {
            todo_mems[i].mem_pass[j++]=x;
            x=in.get();
        }
        a4=in.get()-48;
        a5=in.get()-48,a6=in.get()-48;
        todo_mems[i].mem_id=100*a4+10*a5+a6;
        x=in.get();
    }
}

//账号管理，登录，注册，退出
bool users::user_load()
{
    string in_order;
    int ord;
    int tmp;
    if(user_num==0)
    {
        cout<<"无账号"<<endl;
        cout<<"输入0，退出程序；输入1，注册新账号"<<endl;
        getline(cin,in_order,'\n');
        ord=in_order[0]-'0';
        if(ord==0)  return true;
        else if(ord==1)
        {
            tmp = reg();
            if (tmp == -1) {cout<<"该用户已存在"<<endl;return true;}
            else
            {
                mem_no=tmp;
                return false;
            }
        }
        else cout<<"命令错误"<<endl;
    }
    else
    {
        cout<<"输入0，退出程序；输入1，注册新账号，输入2，登录账号"<<endl;
        getline(cin,in_order,'\n');
        ord=in_order[0]-'0';
        if(ord==0)  return true;
        else if(ord==1)
        {
            tmp = reg();
            if (tmp == -1) {cout<<"该用户已存在"<<endl;return true;}
            else
            {
                mem_no=tmp;
                return false;
            }
        }
        else if(ord==2)
        {
            tmp = login();
            if (tmp == -1) return true;
            else
            {
                mem_no=tmp;
                return false;
            }
        }
        else cout<<"命令错误"<<endl;
        return true;
    }
}

//注册新账号
int users::reg()
{
    //user_num++;
    string user,password,pass;
    string tmp_name;
    int tmp[20];
    char name[20],id[10];
    cout<<"请输入用户名："<<endl;
    getline(cin,tmp_name,'\n');
    int x;
    bool repeat=false;
    for(x=1;x<=user_num;++x)
    {
        if(todo_mems[x].mem_name.compare(tmp_name)==0)
        {repeat=true;break;}
    }
    if(repeat)
    {
        return -1;
    }
    user_num++;
    todo_mems[user_num].mem_name=tmp_name;
    cout<<"新用户已创建，请输入密码：";
    getline(cin,password,'\n');
    int i;
    for (i=0;i<password.length();i++)
    {
        tmp[i]=((password[i])+23)%128;
    }
    for (int j=0;j<i;j++)
    {
        todo_mems[user_num].mem_pass[j]=char(tmp[j]);
    }
    todo_mems[user_num].mem_id=0;
    todo_mems[user_num].mem_no=user_num;
    user_help();
    return user_num;
}

//登录函数
int users::login()
{
    string user,password,pass;
    int tmp[20];
    char name[20],id[10];
    cout<<"请输入用户名："<<endl;
    getline(cin,user,'\n');
    //user+='\0';
    int i;
    for(i=1;i<=user_num;++i)
    {
        if(todo_mems[i].mem_name.compare(user)==0)
            break;
    }
    if(i>user_num)
    {
        cout<<"用户不存在"<<endl;
        return -1;
    }
    cout<<"请输入密码:"<<endl;
    int j;
    getline(cin,pass,'\n');
    for ( j=0;j<pass.length();j++)
    {
        if (char((pass[j]+23)%128)!=todo_mems[i].mem_pass[j])
        {cout<<"密码错误！";return -1;}
    }
    if (j<strlen(todo_mems[i].mem_pass))
    {cout<<"密码错误！";return -1;}
    cout<<endl;
    cout<<"密码正确"<<endl;
    cout<<endl;
    user_help();
    return i;
}

//输出帮助文档
void users::user_help()
{
    cout<<"*******************欢迎使用日程管理系统！***********************"<<endl;
    cout<<endl;
    cout<<"任务属性优先级从低到高为1，2，3；任务类型按类型学习，娱乐，生活分别为1，2，3"<<endl;
    cout<<endl;
    cout<<"****************输入数字指令进入相应软件功能：******************"<<endl;
    cout<<"0.退出               输入格式：0      退出并保存"<<endl;
    cout<<"1.添加任务            输入格式：1--类型-优先度-开始时间-提醒时间-任务名称"<<endl;
    cout<<"****例如：1--2 3 2022-07-07-14-30-00 2022-07-07-14-25-00-name（系统将自动为您生成对应id）"<<endl;
    cout<<"2.删除任务            输入格式：2--任务ID    例如：2--006（ID以3位数形式输入）"<<endl;
    cout<<"3.按时间打印任务       输入格式：3      将按输入的提醒时间从早到晚打印任务"<<endl;
    cout<<"4.按优先级打印任务      输入格式：4     将按优先级从高到低打印任务"<<endl;
    cout<<"5.按类型打印任务       输入格式：5      将按类型生活，娱乐，学习依次打印任务"<<endl;
    cout<<"6.取消               输入格式：6      取消输入内容，重新进入命令行"<<endl;
    cout<<"7.帮助               输入格式：7      输出程序帮助文档"<<endl;
    cout<<endl<<endl<<endl;
}

//将更改的用户信息存储于本地
void users::user_stock()
{
    fstream file("USERS.txt", ios::out);
    ofstream in;
    in.open("USERS.txt", ios::app);
    if (user_num <= 9)
        in << "00" << user_num;
    else {
        if (user_num >= 10 && user_num <= 99)
            in << '0' << user_num;
        else in << user_num;
    }
    in << '\n';
    int i;
    for (i = 1; i <= user_num; ++i)
    {

        if (todo_mems[i].mem_no <= 9)
            in << "00" << todo_mems[i].mem_no;
        else {
            if (todo_mems[i].mem_no >= 10 && todo_mems[i].mem_no <= 99)
                in << '0' << todo_mems[i].mem_no;
            else in << todo_mems[i].mem_no;
        }
        in<<"\n";
            in << todo_mems[i].mem_name << '\n';
            for (int j = 0; j < strlen(todo_mems[i].mem_pass); ++j)
                in << todo_mems[i].mem_pass[j];
            in << "\n";
            if (todo_mems[i].mem_id <= 9)
                in << "00" << todo_mems[i].mem_id;
            else {
                if (todo_mems[i].mem_id >= 10 && todo_mems[i].mem_id <= 99)
                    in << '0' << todo_mems[i].mem_id;
                else in << todo_mems[i].mem_id;
            }
            in << "\n";
        }
    }
