#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m;
//mutex 可以锁住代码块，让其他进程在上锁了的代码块出进行等待
//m.try_lock() 可以尝试上锁，上锁失败返回false

//lock若在for外锁，则表示for可以不受其他线程影响运行完
//下面代码lock锁的是cout那一句输出
void func1(int n){
    for(int i=0;i<n;i++){
        m.lock();
        cout<<"This  is thread1 with"<<i<<endl;
        m.unlock();
    }
}

void func2(int n){
    for(int i=0;i<n;i++){
        m.lock();
        cout<<"This  is thread2 with"<<i<<endl;
        m.unlock();
    }
}

int main(){
    thread t1(func1,1000);
    thread t2(func2,1000);
    t1.join();
    t2.join();
    return 0;
}