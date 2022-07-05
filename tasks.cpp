//
// Created by faii on 2022/6/30.
//
#include "tasks.h"
#include <queue>
#include <vector>

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


void user::insert_task()
{
    //增加任务:只修改任务数组
}

void user::delete_task()
{
    //删除对应id的任务:只修改任务数组
}

void user::print_task_bytime()
{
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
    for (int i=1;i<task_num;i++)
        if (taskbytime[i].prio==3)
        {cout<<"id:"<<taskbytime[i].task_id<<' '<<"类型:"<<taskbytime[i].type_chinese<<' '<<"优先度:"<<taskbytime[i].prio<<endl;
            cout<<taskbytime[i].task_time.year<<'-'<<taskbytime[i].task_time.mon<<'-'<<taskbytime[i].task_time.day
                <<'-'<<taskbytime[i].task_time.hour<<'-'<<taskbytime[i].task_time.minute<<'-'<<taskbytime[i].task_time.second
                <<' '<<taskbytime[i].name<<endl;}
    for (int i=1;i<task_num;i++)
        if (taskbytime[i].prio==2)
        {cout<<"id:"<<taskbytime[i].task_id<<' '<<"类型:"<<taskbytime[i].type_chinese<<' '<<"优先度:"<<taskbytime[i].prio<<endl;
            cout<<taskbytime[i].task_time.year<<'-'<<taskbytime[i].task_time.mon<<'-'<<taskbytime[i].task_time.day
                <<'-'<<taskbytime[i].task_time.hour<<'-'<<taskbytime[i].task_time.minute<<'-'<<taskbytime[i].task_time.second
                <<' '<<taskbytime[i].name<<endl;}
    for (int i=1;i<task_num;i++)
        if (taskbytime[i].prio==1)
        {cout<<"id:"<<taskbytime[i].task_id<<' '<<"类型:"<<taskbytime[i].type_chinese<<' '<<"优先度:"<<taskbytime[i].prio<<endl;
            cout<<taskbytime[i].task_time.year<<'-'<<taskbytime[i].task_time.mon<<'-'<<taskbytime[i].task_time.day
                <<'-'<<taskbytime[i].task_time.hour<<'-'<<taskbytime[i].task_time.minute<<'-'<<taskbytime[i].task_time.second
                <<' '<<taskbytime[i].name<<endl;}
}

void user::print_task_bytype()
{
    for (int i=1;i<task_num;i++)
        if (taskbytime[i].type==3)
        {cout<<"id:"<<taskbytime[i].task_id<<' '<<"类型:"<<taskbytime[i].type_chinese<<' '<<"优先度:"<<taskbytime[i].prio<<endl;
            cout<<taskbytime[i].task_time.year<<'-'<<taskbytime[i].task_time.mon<<'-'<<taskbytime[i].task_time.day
                <<'-'<<taskbytime[i].task_time.hour<<'-'<<taskbytime[i].task_time.minute<<'-'<<taskbytime[i].task_time.second
                <<' '<<taskbytime[i].name<<endl;}
    for (int i=1;i<task_num;i++)
        if (taskbytime[i].type==2)
        {cout<<"id:"<<taskbytime[i].task_id<<' '<<"类型:"<<taskbytime[i].type_chinese<<' '<<"优先度:"<<taskbytime[i].prio<<endl;
            cout<<taskbytime[i].task_time.year<<'-'<<taskbytime[i].task_time.mon<<'-'<<taskbytime[i].task_time.day
                <<'-'<<taskbytime[i].task_time.hour<<'-'<<taskbytime[i].task_time.minute<<'-'<<taskbytime[i].task_time.second
                <<' '<<taskbytime[i].name<<endl;}
    for (int i=1;i<task_num;i++)
        if (taskbytime[i].type==1)
        {cout<<"id:"<<taskbytime[i].task_id<<' '<<"类型:"<<taskbytime[i].type_chinese<<' '<<"优先度:"<<taskbytime[i].prio<<endl;
            cout<<taskbytime[i].task_time.year<<'-'<<taskbytime[i].task_time.mon<<'-'<<taskbytime[i].task_time.day
                <<'-'<<taskbytime[i].task_time.hour<<'-'<<taskbytime[i].task_time.minute<<'-'<<taskbytime[i].task_time.second
                <<' '<<taskbytime[i].name<<endl;}
}

todo_time user::remind(todo_time Time)
{
    //周期性检查/提醒;
}

void user::stock()
{
    fstream file("file.txt", ios::out);//清空txt
    //在程序退出的时候，清空任务txt，然后将任务数组导入txt；
    //写一个for循环，次数为task_num，写入文本
    ofstream ofs;
    char name[100];
    char time[20];
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
        ofs<< tp<<","<<prio<<","<<time<<","<<name<<endl;
        ofs.close();
    }
    ofs.close();
}
//输入格式：1 1 2022-07-04-12-11-14 faii

todo_time user::update()
{
    ;
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
