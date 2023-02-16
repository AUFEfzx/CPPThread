#include<iostream>
#include<thread>
#include<atomic>
#include<mutex>
#include"spendTime.h"

using namespace std;

//测试基准程序有问题，后续调整
//atomic 
//This program spend 50771ms

//mutex
//This program spend 47601ms


atomic<bool> a(false);

void func1(int n){
    while(n--){
        while(a) ;
        cout<<"This is thread1 1"<<endl;
        a = true;
    }

}

void func2(int n){
    while(n--){
        while(!a) ;
        cout<<"This is thread2 2"<<endl;
        a = false;
    }

}

// mutex m;
// void func1(int n){
//     while(n--){
//         m.lock();
//         cout<<"This is thread1 1"<<endl;
//         m.unlock();
//     }

// }

// void func2(int n){
//     while(n--){
//         m.lock();
//         cout<<"This is thread2 2"<<endl;
//         m.unlock();
//     }

// }

SpendTime st;
int main(){
    thread t1(func1,100000);
    thread t2(func2,100000);
    t1.join();
    t2.join();
    return 0;
}