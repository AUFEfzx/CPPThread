#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

mutex m;
condition_variable cv;
int flag = 1;

//条件变量是可以做到阻塞线程并由其他线程进行唤醒的
//条件变量的wait需要一个unique_lock，其包了一层mutex
//但条件变量有两个坑，唤醒丢失和虚假唤醒
//唤醒丢失就是t1执行完，预期是唤醒阻塞着的t2，但此时t2还没来得及阻塞，
//然后t2拿到cpu再阻塞，就嗝屁了

void func1(int n){
    unique_lock<mutex> l(m);
    while(n--){
        while(flag != 1) cv.wait(l);
        cout<<"thread1 1"<<endl;
        flag++;
        cv.notify_all();
    }
}

void func2(int n){
    unique_lock<mutex> l(m);
    while(n--){
        while(flag != 2)
            cv.wait(l);
        cout<<"thread2 2"<<endl;
        flag++;
        cv.notify_all();
    }
}

void func3(int n){
    unique_lock<mutex> l(m);
    while(n--){
        while(flag != 3) cv.wait(l);
        cout<<"thread3 3"<<endl;
        flag=1;
        cv.notify_all();
    }
}


int main(){
    thread t1(func1,100);
    thread t2(func2,100);
    thread t3(func3,100);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}