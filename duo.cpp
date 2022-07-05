////
//// Created by faii on 2022/7/4.
////
//
//#include <stdio.h>
//#include <pthread.h>
//#include <unistd.h>
//
////线程函数1
//void *pthread_func1(void *arg)
//{
//    while(1) {
//        printf("线程函数1正在运行.....\n");
//        sleep(2);
//    }
//}
////线程函数2
//void *pthread_func2(void *arg)
//{
//    while(1) {
//        printf("线程函数2正在运行.....\n");
//        sleep(2);
//    }
//}
//int main(int argc,char **argv)
//{
//    pthread_t thread_id1;
//    pthread_t thread_id2;
///*1. 创建线程1*/
//    if(pthread_create(&thread_id1,NULL,pthread_func1,NULL)) {
//        printf("线程1创建失败!\n");
//        return -1;
//    }
///*2. 创建线程2*/
//    if(pthread_create(&thread_id2,NULL,pthread_func2,NULL)) {
//        printf("线程2创建失败!\n");
//        return -1;
//    }
///*3. 等待线程结束,释放线程的资源*/
//    pthread_join(thread_id1,NULL);
//    pthread_join(thread_id2,NULL);
//    return 0;