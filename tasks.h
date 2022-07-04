//
// Created by faii on 2022/7/2.
//

#ifndef UNTITLED7_TASKS_H
#define UNTITLED7_TASKS_H
#pragma once
#include <queue>
#include <iostream>
#include <unistd.h>

using namespace std;

struct task
{
    char* name;
    int type;
    int prio;
    int time;//提醒时间这里的变量类型未定
    int task_id;//用hash算出唯一id

};

struct  todo_time
{
    int ye;
    int mo;
    int da;
    int ho;
    int mi;
    int se;
};

class user
{
private:
    char* id;
    int ps;
    int next_task;//下一个最先到期的任务的时间
public:
    user()
    {
        id= nullptr;
        ps=next_task=0;
    }
    user(char* a, int b)
    {
        ;
    }
    void insert_task();//增加任务
    void delete_task();//删除任务
    void print_task();//输出任务信息-可能会有多个函数
    todo_time remind(todo_time Time);//利用多线程周期性检查+提醒，传进来的应该是时间字符串，内置一个时间转换函数
    todo_time update();//获取最近任务时间
    void test()//我用来测试的，不用管
    {
        sleep(3);
        std::cout<<"test!!"<<endl;
    }
};
#endif //UNTITLED7_TASKS_H
