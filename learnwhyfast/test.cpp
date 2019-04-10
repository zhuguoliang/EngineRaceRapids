//
// Created by zgl on 19-4-9.
//

#include "test.h"


#include <vector>
#include <future>
#include <thread>
#include <numeric>
#include <iostream>

void accumulate(std::vector<int>::iterator first,
        std::vector<int>::iterator last,
        std::promise<int> accumulate_promise)
{

    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);//提醒future

}

void do_work(std::promise<int > barrier)
{
std::this_thread::sleep_for(std::chrono::seconds(4));
barrier.set_value(1);
}


int main()
{


    std::vector<int> numbers = {1,2,3,4,5,6};

    std::promise<int> accumulate_promise;

    std::future<int> accumulate_future = accumulate_promise.get_future();

    std::thread work_thread(accumulate, numbers.begin(),numbers.end(),
            std::move(accumulate_promise));

    accumulate_future.wait();
    std::cout<<"result = "<< accumulate_future.get()<<'\n';
    work_thread.join();

    std::promise<int > barrier;
    std::future<int > barrier_future = barrier.get_future();
    std::thread new_work_thread(do_work, std::move(barrier));
    barrier_future.wait();
    std::cout<< "finally waited for it now possible to use future which is "<<barrier_future.get()<<'\n';
    new_work_thread.join();



}