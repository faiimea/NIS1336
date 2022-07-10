//
// Created by faii on 2022/7/2.
//

#ifndef UNTITLED7_TASKS_H
#define UNTITLED7_TASKS_H
#pragma once
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
using namespace std;

struct  todo_time
{
    int year;
    int mon;
    int day;
    int hour;
    int minute;
    int second;
    todo_time()
    {
        year=2000;
        mon=1;
        day=1;
        hour=1;
        minute=1;
        second=1;
    }

    //这个是标准格式下的系统时间转换函数
    todo_time(char time_input[20])
    {
        int y,m,d,h,mi,s;
        y=m=d=h=mi=s=0;
        for(int i=0;i<4;++i)
        {
            y=y*10+time_input[i]-'0';
        }
        for(int i=5;i<7;++i)
        {
            m=m*10+time_input[i]-'0';
        }
        for(int i=8;i<10;++i)
        {
            d=d*10+time_input[i]-'0';
        }
        for(int i=11;i<13;++i)
        {
            h=h*10+time_input[i]-'0';
        }
        for(int i=14;i<16;++i)
        {
            mi=mi*10+time_input[i]-'0';
        }
        for(int i=17;i<19;++i)
        {
            s=s*10+time_input[i]-'0';
        }
        year = y;mon = m;day = d;hour = h;minute = mi;second = s;
    }
};

class task
{
public:
    char* name;
    int task_id;
    int type;
    int prio;
    string type_chinese;
    string prio_chinese;
    todo_time task_time;
    todo_time remind_time;
public:
    task()
    {
        name= "未命名";
        task_id=type=prio=1;
        todo_time tmp;
        task_time=tmp;
        remind_time=tmp;
    }

    task(char* a,int b,int c,todo_time d,todo_time e,int f)
    {
        name=a;
        type=b;
        prio=c;
        task_time=d;
        remind_time=e;
        task_id=f;
    }

};


class user
{
private:
    int ps;
    int task_num;
    task next_task;//下一个最先到期的任务
    task tasks_group[100] ;
    task taskbytime[100];
public:
    int no;
    char file_name[10];
    int id;
    char order[100];
    user()
    {
        id= 0;
        ps=0;
        task_num=0;
        next_task.task_time.year=9999;
        get_task();//从文本中获取任务数组（任务数组初始化）
    }
    void filename_get();
    bool load();//需要加载的命令有：增加任务，删除任务，输出任务信息1，2，3，退出程序
    todo_time getTime();
    int id_detect(int in_id);
    void insert_task(task in_task);//增加任务
    void delete_task(int in_id);//删除任务
    void print_task_bytime();//输出任务信息-可能会有多个函数
    void print_task_bytype();
    void print_task_byprio();
    void remind();//检查+提醒
    void update();//获取最近任务时间
    int stock();
    void get_task();//从文本文件中获取任务数组
    void sorttaskbytime();
    bool time_cmp(todo_time a,todo_time b);
};
#endif //UNTITLED7_TASKS_H
