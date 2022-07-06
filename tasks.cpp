//
// Created by faii on 2022/6/30.
//
#include "tasks.h"
#include <queue>
#include <vector>
//获取系统时间
string sysTime()
{
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep));
    return tmp;
}
//将系统时间转换为todo_time格式
todo_time user::getTime()
{
    string tmp=sysTime();
    char time_list[20];
    strcpy(time_list, tmp.c_str());
    todo_time a(time_list);
    return a;
}
//时间比较（这个说实话。。。没测试过，只是把下面的东西copy上来，估计要大改）
bool user::time_cmp(todo_time a,todo_time b)
{
        if (a.year!=b.year)
            return a.year>b.year;
        else if(a.mon!=b.mon)
            return a.mon>b.mon;
        else if(a.day!=b.day)
            return a.day>b.day;
        else if(a.hour!=b.hour)
            return a.hour>b.hour;
        else if(a.minute!=b.minute)
            return a.minute>b.minute;
        else if(a.second!=b.second)
            return a.second>b.second;
}

//这个是任务提醒函数
void user::remind()
{
    //周期性检查/提醒;
    todo_time Time=getTime();
    if(time_cmp(Time,next_task.task_time))
    {
        cout<<next_task.task_id<<"已到期"<<endl;
        delete_task(next_task.task_id);
    }
}

void user::get_task()
{
    //从文本内容中导入任务到任务数组;
    ifstream in;
    in.open("file.txt");
    int i=1;
    while(1)
    {
        int a1,a2,a3,a4;
        a1=in.get()-48,a2=in.get()-48,a3=in.get()-48;
        tasks_group[i].task_id=100*a1+10*a2+a3;//默认存储时id为三位数，001，002类推
        in.get();
        tasks_group[i].type=in.get()-48;
        if(tasks_group[i].type==1)
            tasks_group[i].type_chinese="学习";
        if(tasks_group[i].type==2)
            tasks_group[i].type_chinese="娱乐";
        if(tasks_group[i].type==3)
            tasks_group[i].type_chinese="生活";
        in.get();
        tasks_group[i].prio=in.get()-48;
        in.get();
        a1=in.get()-48,a2=in.get()-48,a3=in.get()-48,a4=in.get()-48;
        tasks_group[i].task_time.year=a1*1000+a2*100+a3*10+a4;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].task_time.mon=a1*10+a2;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].task_time.day=a1*10+a2;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].task_time.hour=a1*10+a2;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].task_time.minute=a1*10+a2;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].task_time.second=a1*10+a2;
        in.get();
        char x=in.get();
        tasks_group[i].name=new char[20];
        int j=0;
        while(x!='\n'&&x!=EOF)
        {
            tasks_group[i].name[j++]=x;
            x=in.get();
        }
        tasks_group[i].name[j]='\0';
        if (x=='\n')
            i++;
        else {
            in.close();
            break;
        }
    }
    task_num=i;
}

//在删除的时候要用到，找到这个id的任务
int user::id_detect(int in_id)
{
    for(int i=1;i<=task_num;++i)
    {
        if(tasks_group[i].task_id==in_id)   return i;
    }
    return 0;
}

//已测试，在数组中添加任务
void user::insert_task(task in_task)
{
    //增加任务:只修改任务数组
    task_num++;id++;
    in_task.task_id=id;
    tasks_group[task_num]=in_task;
    update();
}

//已测试，删除任务
void user::delete_task(int in_id)
{
    //删除对应id的任务:只修改任务数组
    int loc=id_detect(in_id);
    if(loc)
    {
        for(int i=loc;i<=task_num;++i)
            tasks_group[i]=tasks_group[i+1];
        task_num--;
    }
    else
    {
        std::cout<<"该任务不存在"<<endl;
    }
    update();
}

void user::print_task_bytime()
{
    //打印前整理一遍
    sorttaskbytime();
    for (int i=1;i<task_num;i++)
    {
        cout<<"id:"<<taskbytime[i].task_id<<' '<<"类型:"<<taskbytime[i].type_chinese<<' '<<"优先度:"<<taskbytime[i].prio<<endl;
        cout<<taskbytime[i].task_time.year<<'-'<<taskbytime[i].task_time.mon<<'-'<<taskbytime[i].task_time.day
            <<'-'<<taskbytime[i].task_time.hour<<'-'<<taskbytime[i].task_time.minute<<'-'<<taskbytime[i].task_time.second
            <<' '<<taskbytime[i].name<<endl;
    }
    //输出任务信息;
}

void user::print_task_byprio()
{
    //这里感觉用原始数组好一些，不用重新排序
    for (int i=1;i<task_num;i++)
        if (tasks_group[i].prio==3)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio<<endl;
            cout<<tasks_group[i].task_time.year<<'-'<<tasks_group[i].task_time.mon<<'-'<<tasks_group[i].task_time.day
                <<'-'<<tasks_group[i].task_time.hour<<'-'<<tasks_group[i].task_time.minute<<'-'<<tasks_group[i].task_time.second
                <<' '<<tasks_group[i].name<<endl;}
    for (int i=1;i<task_num;i++)
        if (tasks_group[i].prio==2)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio<<endl;
            cout<<tasks_group[i].task_time.year<<'-'<<tasks_group[i].task_time.mon<<'-'<<tasks_group[i].task_time.day
                <<'-'<<tasks_group[i].task_time.hour<<'-'<<tasks_group[i].task_time.minute<<'-'<<tasks_group[i].task_time.second
                <<' '<<tasks_group[i].name<<endl;}
    for (int i=1;i<task_num;i++)
        if (tasks_group[i].prio==1)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio<<endl;
            cout<<tasks_group[i].task_time.year<<'-'<<tasks_group[i].task_time.mon<<'-'<<tasks_group[i].task_time.day
                <<'-'<<tasks_group[i].task_time.hour<<'-'<<tasks_group[i].task_time.minute<<'-'<<tasks_group[i].task_time.second
                <<' '<<tasks_group[i].name<<endl;}
}

void user::print_task_bytype()
{
    for (int i=1;i<task_num;i++)
        if (tasks_group[i].type==3)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio<<endl;
            cout<<tasks_group[i].task_time.year<<'-'<<tasks_group[i].task_time.mon<<'-'<<tasks_group[i].task_time.day
                <<'-'<<tasks_group[i].task_time.hour<<'-'<<tasks_group[i].task_time.minute<<'-'<<tasks_group[i].task_time.second
                <<' '<<tasks_group[i].name<<endl;}
    for (int i=1;i<task_num;i++)
        if (tasks_group[i].type==2)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio<<endl;
            cout<<tasks_group[i].task_time.year<<'-'<<tasks_group[i].task_time.mon<<'-'<<tasks_group[i].task_time.day
                <<'-'<<tasks_group[i].task_time.hour<<'-'<<tasks_group[i].task_time.minute<<'-'<<tasks_group[i].task_time.second
                <<' '<<tasks_group[i].name<<endl;}
    for (int i=1;i<task_num;i++)
        if (tasks_group[i].type==1)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio<<endl;
            cout<<tasks_group[i].task_time.year<<'-'<<tasks_group[i].task_time.mon<<'-'<<tasks_group[i].task_time.day
                <<'-'<<tasks_group[i].task_time.hour<<'-'<<tasks_group[i].task_time.minute<<'-'<<tasks_group[i].task_time.second
                <<' '<<tasks_group[i].name<<endl;}
}


//存储函数，把数组中的东西存到txt中
void user::stock()
{
    fstream file("file.txt", ios::out);//清空txt
    //在程序退出的时候，清空任务txt，然后将任务数组导入txt；
    //写一个for循环，次数为task_num，写入文本
    ofstream ofs;
    char name[100];
    char time[19];
    int tp;
    int prio;
    int id;
    for(int i=1;i<=task_num;++i)
    {
        tp=tasks_group[i].type;
        prio=tasks_group[i].prio;
        id=tasks_group[i].task_id;
        strcpy(name,tasks_group[i].name);
        //time
        time[0]=(tasks_group[i].task_time.year/1000)+'0';
        time[1]=(tasks_group[i].task_time.year/100-10*(tasks_group[i].task_time.year/1000))+'0';
        time[2]=(tasks_group[i].task_time.year/10-10*(tasks_group[i].task_time.year/100))+'0';
        time[3]=(tasks_group[i].task_time.year-10*(tasks_group[i].task_time.year/10))+'0';
        time[4]='_';
        if(tasks_group[i].task_time.mon>=10)
            time[5]='1';
        else time[5]='0';
        time[6]=(tasks_group[i].task_time.mon%10)+'0';

        time[7]='_';
        if(tasks_group[i].task_time.day>=10)
            time[8]=(tasks_group[i].task_time.day/10)+'0';
        else time[8]='0';
        time[9]=(tasks_group[i].task_time.day%10)+'0';

        time[10]='_';
        if(tasks_group[i].task_time.hour>=10)
            time[11]=(tasks_group[i].task_time.hour/10)+'0';
        else time[11]='0';
        time[12]=(tasks_group[i].task_time.hour%10)+'0';

        time[13]='_';
        if(tasks_group[i].task_time.minute>=10)
            time[14]=(tasks_group[i].task_time.minute/10)+'0';
        else time[14]='0';
        time[15]=(tasks_group[i].task_time.minute%10)+'0';

        time[16]='_';
        if(tasks_group[i].task_time.second>=10)
            time[17]=(tasks_group[i].task_time.second/10)+'0';
        else time[17]='0';
        time[18]=(tasks_group[i].task_time.second%10)+'0';

        ofs.open("file.txt",ios::app);
        if(id<=9)
            ofs<<"00"<<id<<',';
        else {
            if (id >= 10 && id <= 99)
                ofs << '0' << id << ',';
            else ofs << id << ',';
             }
        ofs<< tp<<","<<prio<<",";
        for(int i=0;i<19;++i)
            ofs<<time[i];
        ofs<<","<<name<<endl;
        ofs.close();
    }
    ofs.close();
}
//输入格式：1 1 2022-07-04-12-11-14 faii

//找到目前最近的任务
void user::update()
{
    sorttaskbytime();
    next_task=taskbytime[1];
}

void user::sorttaskbytime()
{
    struct cmp
    {
        bool operator()(task a,task b)
        {
            if (a.task_time.year!=b.task_time.year)
                return a.task_time.year>b.task_time.year;
            else if(a.task_time.mon!=b.task_time.mon)
                return a.task_time.mon>b.task_time.mon;
            else if(a.task_time.day!=b.task_time.day)
                return a.task_time.day>b.task_time.day;
            else if(a.task_time.hour!=b.task_time.hour)
                return a.task_time.hour>b.task_time.hour;
            else if(a.task_time.minute!=b.task_time.minute)
                return a.task_time.minute>b.task_time.minute;
            else if(a.task_time.second!=b.task_time.second)
                return a.task_time.second>b.task_time.second;
        }
    };
    priority_queue<task,vector<task>,cmp> pq;
    for (int i=1;i<=task_num;i++)
        pq.push(tasks_group[i]);
    for (int i=1;i<=task_num;i++)
    {taskbytime[i]=pq.top(); pq.pop();}
}
