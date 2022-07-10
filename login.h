//
// Created by faii on 2022/7/2.
//

#ifndef UNTITLED7_LOGIN_H
#define UNTITLED7_LOGIN_H
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
//同任务模块，先读取，再清空，最后返回输入

struct mem
{
    int mem_no;
    string mem_name;
    char mem_pass[20];
    int mem_id;
};

class users
{
private:

public:
    int user_num;
    mem todo_mems[10];
    int id_num;
    int mem_no;
    void user_get();
    int login();
    int reg();
    bool user_load();
    void user_stock();
    void user_help();
};


#endif //UNTITLED7_LOGIN_H
