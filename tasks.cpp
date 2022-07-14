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

//时间比较
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

//选择该用户对应的txt
void user::filename_get()
{
  file_name[0]='f';
  file_name[1]=no+'0';
  file_name[2]='.';
  file_name[3]='t';
  file_name[4]='x';
  file_name[5]='t';
  file_name[6]='\0';
}

//这个是任务提醒函数
void user::remind()
{
    //周期性检查/提醒;
    todo_time Time=getTime();
    while(time_cmp(Time,next_task.remind_time))
    {
        cout<<"任务ID:"<<next_task.task_id<<' '<<"任务名称:"<<next_task.name<<' ';
        cout<<"该任务将于"<<next_task.task_time.year<<"年"<<next_task.task_time.mon<<"月"<<next_task.task_time.day
                     <<"日"<<next_task.task_time.hour<<"时"<<next_task.task_time.minute<<"分"<<next_task.task_time.second
                     <<"秒"<<"开始，请做好准备"<<endl;
        delete_task(next_task.task_id);
    }
}
void user::get_task()
{
    //从文本内容中导入任务到任务数组;
    ifstream in;
    in.open(file_name);
    int i=1;
    while(1)
    {

        int a1,a2,a3,a4;
        a1=in.get()-48;
        if(a1<0||a1>=10)    return;
        a2=in.get()-48,a3=in.get()-48;
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
        if(tasks_group[i].prio==1)
            tasks_group[i].prio_chinese="低";
        if(tasks_group[i].prio==2)
            tasks_group[i].prio_chinese="中";
        if(tasks_group[i].prio==3)
            tasks_group[i].prio_chinese="高";
        in.get();

        //任务开始时间
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

        //任务提醒时间
        a1=in.get()-48,a2=in.get()-48,a3=in.get()-48,a4=in.get()-48;
        tasks_group[i].remind_time.year=a1*1000+a2*100+a3*10+a4;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].remind_time.mon=a1*10+a2;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].remind_time.day=a1*10+a2;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].remind_time.hour=a1*10+a2;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].remind_time.minute=a1*10+a2;
        in.get();
        a1=in.get()-48,a2=in.get()-48;
        tasks_group[i].remind_time.second=a1*10+a2;
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

//读取任务指令,需要加载的命令有：增加任务，删除任务，输出任务信息1，2，3，退出程序，继续运行
bool user::load()
{
    int order_type=order[0]-'0';
    switch (order_type)
    {
        case 0:
        {
            //程序结束运行
            return true;
        }
        case 1:
        {
            task in_task;
            in_task.type=order[3]-48;
            if(in_task.type==1)
                in_task.type_chinese="学习";
            if(in_task.type==2)
                in_task.type_chinese="娱乐";
            if(in_task.type==3)
                in_task.type_chinese="生活";
            in_task.prio=order[5]-48;
            if(in_task.prio==1)
                in_task.prio_chinese="低";
            if(in_task.prio==2)
                in_task.prio_chinese="中";
            if(in_task.prio==3)
                in_task.prio_chinese="高";
            int a1,a2,a3,a4;
            a1=order[7]-48,a2=order[8]-48,a3=order[9]-48,a4=order[10]-48;
            in_task.task_time.year=a1*1000+a2*100+a3*10+a4;
            a1=order[12]-48,a2=order[13]-48;
            in_task.task_time.mon=a1*10+a2;
            a1=order[15]-48,a2=order[16]-48;
            in_task.task_time.day=a1*10+a2;
            a1=order[18]-48,a2=order[19]-48;
            in_task.task_time.hour=a1*10+a2;
            a1=order[21]-48,a2=order[22]-48;
            in_task.task_time.minute=a1*10+a2;
            a1=order[24]-48,a2=order[25]-48;
            in_task.task_time.second=a1*10+a2;
            a1=order[27]-48,a2=order[28]-48,a3=order[29]-48,a4=order[30]-48;
            in_task.remind_time.year=a1*1000+a2*100+a3*10+a4;
            a1=order[32]-48,a2=order[33]-48;
            in_task.remind_time.mon=a1*10+a2;
            a1=order[35]-48,a2=order[36]-48;
            in_task.remind_time.day=a1*10+a2;
            a1=order[38]-48,a2=order[39]-48;
            in_task.remind_time.hour=a1*10+a2;
            a1=order[41]-48,a2=order[42]-48;
            in_task.remind_time.minute=a1*10+a2;
            a1=order[44]-48,a2=order[45]-48;
            in_task.remind_time.second=a1*10+a2;
            int i;
            in_task.name=new char[20];
            for (i=47;i< strlen(order)-1;i++)
            in_task.name[i-47]=order[i];
            in_task.name[i-47]='\0';
            insert_task(in_task);
            //输入格式：1--2 3 2022-07-07-14-30-00 2022-07-07-14-25-00 faii
            break;
        }
        case 2:
        {
            int tar_id=0;
            int a,b,c;a=order[3]-'0';b=order[4]-'0';c=order[5]-'0';
            tar_id=a*100+b*10+c;
            delete_task(tar_id);
            //输入格式：2--010
            break;
        }
        case 3:
        {
            print_task_bytime();
            break;
        }
        case 4:
        {
            print_task_byprio();
            break;
        }
        case 5:
        {
            print_task_bytype();
            break;
        }
        case 6:
        {
            return false;
        }
        case 7:
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
            return false;
        }
    }
    return false;
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
    task_num++;id++;
    in_task.task_id=id;
    tasks_group[task_num]=in_task;
    update();
    cout<<"插入任务成功，当前任务："<<endl;
    print_task_bytime();
}

//已测试，删除任务
void user::delete_task(int in_id)
{
    int loc=id_detect(in_id);
    if(loc)
    {
        for(int i=loc;i<task_num;++i)
            tasks_group[i]=tasks_group[i+1];
        task_num--;
    }
    else
    {
        std::cout<<"该任务不存在"<<endl;
    }
    update();
}

//三类打印函数

void user::print_task_bytime()
{
    //打印前整理一遍
    sorttaskbytime();
    for (int i=1;i<=task_num;i++)
    {
        cout<<"id:"<<taskbytime[i].task_id<<' '<<"类型:"<<taskbytime[i].type_chinese<<' '<<"优先度:"<<taskbytime[i].prio_chinese<<' ';
        cout<<"名称:"<<taskbytime[i].name<<' ';
        cout<<"提醒时间:"<<taskbytime[i].remind_time.year<<"年"<<taskbytime[i].remind_time.mon<<"月"<<taskbytime[i].remind_time.day
            <<"日"<<taskbytime[i].remind_time.hour<<"时"<<taskbytime[i].remind_time.minute<<"分"<<taskbytime[i].remind_time.second
            <<"秒"<<' ';
        cout<<"开始时间:"<<taskbytime[i].task_time.year<<"年"<<taskbytime[i].task_time.mon<<"月"<<taskbytime[i].task_time.day
            <<"日"<<taskbytime[i].task_time.hour<<"时"<<taskbytime[i].task_time.minute<<"分"<<taskbytime[i].task_time.second
            <<"秒"<<endl;
    }
    cout<<endl;
    //输出任务信息;
}

void user::print_task_byprio()
{
    //这里感觉用原始数组好一些，不用重新排序
    for (int i=1;i<=task_num;i++)
        if (tasks_group[i].prio==3)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio_chinese<<' ';
            cout<<"名称:"<<tasks_group[i].name<<' ';
            cout<<"开始时间:"<<tasks_group[i].task_time.year<<"年"<<tasks_group[i].task_time.mon<<"月"<<tasks_group[i].task_time.day
                <<"日"<<tasks_group[i].task_time.hour<<"时"<<tasks_group[i].task_time.minute<<"分"<<tasks_group[i].task_time.second
                <<"秒"<<endl;}
    for (int i=1;i<=task_num;i++)
        if (tasks_group[i].prio==2)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio_chinese<<' ';
            cout<<"名称:"<<tasks_group[i].name<<' ';
            cout<<"开始时间:"<<tasks_group[i].task_time.year<<"年"<<tasks_group[i].task_time.mon<<"月"<<tasks_group[i].task_time.day
                <<"日"<<tasks_group[i].task_time.hour<<"时"<<tasks_group[i].task_time.minute<<"分"<<tasks_group[i].task_time.second
                <<"秒"<<endl;}
    for (int i=1;i<=task_num;i++)
        if (tasks_group[i].prio==1)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio_chinese<<' ';
            cout<<"名称:"<<tasks_group[i].name<<' ';
            cout<<"开始时间:"<<tasks_group[i].task_time.year<<"年"<<tasks_group[i].task_time.mon<<"月"<<tasks_group[i].task_time.day
                <<"日"<<tasks_group[i].task_time.hour<<"时"<<tasks_group[i].task_time.minute<<"分"<<tasks_group[i].task_time.second
                <<"秒"<<endl;}
    cout<<endl;
}

void user::print_task_bytype()
{
    for (int i=1;i<=task_num;i++)
        if (tasks_group[i].type==3)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio_chinese<<' ';
            cout<<"名称:"<<tasks_group[i].name<<' ';
            cout<<"开始时间:"<<tasks_group[i].task_time.year<<"年"<<tasks_group[i].task_time.mon<<"月"<<tasks_group[i].task_time.day
                <<"日"<<tasks_group[i].task_time.hour<<"时"<<tasks_group[i].task_time.minute<<"分"<<tasks_group[i].task_time.second
                <<"秒"<<endl;}
    for (int i=1;i<=task_num;i++)
        if (tasks_group[i].type==2)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio_chinese<<' ';
            cout<<"名称:"<<tasks_group[i].name<<' ';
            cout<<"开始时间:"<<tasks_group[i].task_time.year<<"年"<<tasks_group[i].task_time.mon<<"月"<<tasks_group[i].task_time.day
                <<"日"<<tasks_group[i].task_time.hour<<"时"<<tasks_group[i].task_time.minute<<"分"<<tasks_group[i].task_time.second
                <<"秒"<<endl;}
    for (int i=1;i<=task_num;i++)
        if (tasks_group[i].type==1)
        {cout<<"id:"<<tasks_group[i].task_id<<' '<<"类型:"<<tasks_group[i].type_chinese<<' '<<"优先度:"<<tasks_group[i].prio_chinese<<' ';
            cout<<"名称:"<<tasks_group[i].name<<' ';
            cout<<"开始时间:"<<tasks_group[i].task_time.year<<"年"<<tasks_group[i].task_time.mon<<"月"<<tasks_group[i].task_time.day
                <<"日"<<tasks_group[i].task_time.hour<<"时"<<tasks_group[i].task_time.minute<<"分"<<tasks_group[i].task_time.second
                <<"秒"<<endl;}
    cout<<endl;
}


//存储函数，把数组中的东西存到txt中
int user::stock()
{
    fstream file(file_name, ios::out);//清空txt
    //在程序退出的时候，清空任务txt，然后将任务数组导入txt；
    //写一个for循环，次数为task_num，写入文本
    ofstream ofs;
    char name[100];
    char time[19],remindtime[19];
    int tp;
    int prio;
    int id_;
    for(int i=1;i<=task_num;++i)
    {
        tp=tasks_group[i].type;
        prio=tasks_group[i].prio;
        id_=tasks_group[i].task_id;
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

        remindtime[0]=(tasks_group[i].remind_time.year/1000)+'0';
        remindtime[1]=(tasks_group[i].remind_time.year/100-10*(tasks_group[i].remind_time.year/1000))+'0';
        remindtime[2]=(tasks_group[i].remind_time.year/10-10*(tasks_group[i].remind_time.year/100))+'0';
        remindtime[3]=(tasks_group[i].remind_time.year-10*(tasks_group[i].remind_time.year/10))+'0';
        remindtime[4]='_';
        if(tasks_group[i].remind_time.mon>=10)
            remindtime[5]='1';
        else remindtime[5]='0';
        remindtime[6]=(tasks_group[i].remind_time.mon%10)+'0';

        remindtime[7]='_';
        if(tasks_group[i].remind_time.day>=10)
            remindtime[8]=(tasks_group[i].remind_time.day/10)+'0';
        else remindtime[8]='0';
        remindtime[9]=(tasks_group[i].remind_time.day%10)+'0';

        remindtime[10]='_';
        if(tasks_group[i].remind_time.hour>=10)
            remindtime[11]=(tasks_group[i].remind_time.hour/10)+'0';
        else remindtime[11]='0';
        remindtime[12]=(tasks_group[i].remind_time.hour%10)+'0';

        remindtime[13]='_';
        if(tasks_group[i].remind_time.minute>=10)
            remindtime[14]=(tasks_group[i].remind_time.minute/10)+'0';
        else remindtime[14]='0';
        remindtime[15]=(tasks_group[i].remind_time.minute%10)+'0';

        remindtime[16]='_';
        if(tasks_group[i].remind_time.second>=10)
            remindtime[17]=(tasks_group[i].remind_time.second/10)+'0';
        else remindtime[17]='0';
        remindtime[18]=(tasks_group[i].remind_time.second%10)+'0';

        ofs.open(file_name,ios::app);
        if(id_<=9)
            ofs<<"00"<<id_<<',';
        else {
            if (id_ >= 10 && id_ <= 99)
                ofs << '0' << id_ << ',';
            else ofs << id_ << ',';
             }
        ofs<< tp<<","<<prio<<",";
        for(int j=0;j<19;++j)
            ofs<<time[j];
        ofs<<',';
        for(int j=0;j<19;++j)
            ofs<<remindtime[j];
        if(i!=task_num)
        ofs<<","<<name<<endl;
        else ofs<<','<<name;
        ofs.close();

    }
    ofs.close();
    if(task_num==0)
    {
        remove(file_name);
        cout << strerror(errno);
    }
    return id;
}

//找到目前最近的任务
void user::update()
{
    sorttaskbytime();
    if (task_num>0)
    next_task=taskbytime[1];
    else next_task.remind_time.year=9999;
}

//任务排序函数
void user::sorttaskbytime()
{
    struct cmp
    {
        bool operator()(task a,task b)
        {
            if (a.remind_time.year!=b.remind_time.year)
                return a.remind_time.year>b.remind_time.year;
            else if(a.remind_time.mon!=b.remind_time.mon)
                return a.remind_time.mon>b.remind_time.mon;
            else if(a.remind_time.day!=b.remind_time.day)
                return a.remind_time.day>b.remind_time.day;
            else if(a.remind_time.hour!=b.remind_time.hour)
                return a.remind_time.hour>b.remind_time.hour;
            else if(a.remind_time.minute!=b.remind_time.minute)
                return a.remind_time.minute>b.remind_time.minute;
            else if(a.remind_time.second!=b.remind_time.second)
                return a.remind_time.second>b.remind_time.second;
        }
    };
    priority_queue<task,vector<task>,cmp> pq;
    for (int i=1;i<=task_num;i++)
        pq.push(tasks_group[i]);
    for (int i=1;i<=task_num;i++)
    {taskbytime[i]=pq.top(); pq.pop();}
}