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
        year = mon = day = hour = minute = second = 0;
    }

    //这个是标准格式下的系统时间转换函数
    todo_time(char time_input[20])
    {
        int y,m,d,h,mi,s;
        y=m=d=h=mi=s=0;
        cout<<endl;
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
    int task_id;//用hash算出唯一id
    int type;
    int prio;
    todo_time task_time;
public:
    task()
    {
        name= nullptr;
        task_id=type=prio=0;
        todo_time tmp;
        task_time=tmp;
    }

    task(char* a,int b,int c,todo_time d,int e)
    {
        name=a;
        type=b;
        prio=c;
        task_time=d;
        task_id=e;
    }

};


class user
{
private:
    char* id;
    int ps;
    int task_num;
    todo_time next_task;//下一个最先到期的任务的时间
    task tasks_group[100] ;

public:
    user()
    {
        id= nullptr;
        ps=0;
        task_num=1;
        get_task();//从文本中获取任务数组（任务数组初始化）
    }
    int idget_task(char name[100]);
    void insert_task();//增加任务
    void delete_task();//删除任务
    void print_task();//输出任务信息-可能会有多个函数
    todo_time remind(todo_time Time);//检查+提醒
    todo_time update();//获取最近任务时间
    void stock();
    void get_task();//从文本文件中获取任务数组
};
#endif //UNTITLED7_TASKS_H
