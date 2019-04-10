//
// Created by zhuguoliang on 2019-04-10.
//

#include "barrier.h"

#include <thread>
#include <iostream>


int main()
{

    std::condition_variable cv;
    std::mutex m;

    std::thread t([&](){
        std::cout<<"uere\n";
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk);
    });

    t.join();
    cv.notify_one();
    return 0;

}

