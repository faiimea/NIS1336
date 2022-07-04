//
// Created by faii on 2022/6/30.
//
#include "tasks.h"


void user::get_task()
{
    //从文本内容中导入任务到任务数组;
    ifstream in;
    in.open("file.txt");
    int i=1;
    while(1)
    {
        tasks_group[i].task_id=in.get()-48;
        in.get();
        tasks_group[i].type=in.get()-48;
        in.get();
        tasks_group[i].prio=in.get()-48;
        in.get();
        int a1=in.get()-48,a2=in.get()-48,a3=in.get()-48,a4=in.get()-48;
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

int user::idget_task(char name[100])
{
    int hash;
    for(int i=0;i<20;++i)
    {
        (hash=hash*7+name[i]*233)%21788233;
    }
    //这里是个hash，但还没写
    return hash;
}

void user::insert_task()
{
    //增加任务:只修改任务数组
}

void user::delete_task()
{
    //删除对应id的任务:只修改任务数组
}

void user::print_task()
{
    for (int i=1;i<task_num;i++)
    {
        cout<<tasks_group[i].task_id<<' '<<tasks_group[i].name<<' '<<tasks_group[i].type<<' '<<tasks_group[i].prio<<endl;
        cout<<tasks_group[i].task_time.year<<'-'<<tasks_group[i].task_time.mon<<'-'<<tasks_group[i].task_time.day
            <<'-'<<tasks_group[i].task_time.hour<<'-'<<tasks_group[i].task_time.minute<<'-'<<tasks_group[i].task_time.second<<endl;
    }
    //输出任务信息;
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
        ofs <<id<<","<< tp<<","<<prio<<","<<time<<","<<name<<endl;
        ofs.close();
    }
    ofs.close();
}
//输入格式：1 1 2022-07-04-12-11-14 faii

todo_time user::update()
{
    ;
}

