#include<chrono>
#include<iostream>

class SpendTime{
public:
    SpendTime():_curTimePoint(std::chrono::steady_clock::now()){}
    ~SpendTime(){
        auto cur_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - _curTimePoint);
        std::cout<<"This program spend "<<duration.count()<<"ms"<<std::endl;
    }

private:
    std::chrono::steady_clock::time_point _curTimePoint;
};