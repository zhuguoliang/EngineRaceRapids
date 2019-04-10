//
// Created by zhuguoliang on 2019-04-07.
//

#include "polar_string.h"
#include "log.h"

#include<chrono>
#include<iostream>

using namespace polar_race;

int64_t polar_str_to_int64(PolarString ps) {
    int64_t int3;
    memcpy(&int3, ps.data(), sizeof(int64_t));
    return int3;
}

void TestConversion() {
    int64_t int1 = -10;
    int64_t int2 = -11;

    auto ps = PolarString(reinterpret_cast<char *>(&int1), sizeof(int64_t));
    auto ps2 = PolarString(reinterpret_cast<char *>(&int2), sizeof(int64_t));

    log_info("match status: %d", ps.compare(ps2));

    log_info("%lld", polar_str_to_int64(ps));
    log_info("%lld", polar_str_to_int64(ps2));
    log_info("%.*s", 8, ps2.data());

}

int main() {
    char *chars = new char[8];
    for (int i = 0; i < 8; i++) {
        chars[i] = static_cast<char>('a' + i);
    }

    //polarstring to int64_t
    int64_t int1 = polar_str_to_int64(PolarString(chars, sizeof(int64_t)));
    //int64_t to polarString
    auto ps = PolarString(reinterpret_cast<char *>(&int1), sizeof(int64_t));
    for (int i = 0; i < 8; i++) {
        log_info("%c", ps.data()[i]);
    }

    //char array to int64_t
    char chars_tmp[8];
    memcpy(chars_tmp, &int1, sizeof(int64_t));
    for (int i = 0; i < 8; i++) {
        log_info("%c", ps.data()[i]);
    }

    std::cout<<"==================================================================="<<std::endl;
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    auto a = PolarString(chars, sizeof(int64_t));
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2-t1);
    std::cout << "It takes " << time_span.count() << " seconds to cast char * to PolarString.";
    std::cout << std::endl;

    t1 = high_resolution_clock::now();
    int64_t int2 = polar_str_to_int64(a);
    t2 = high_resolution_clock::now();

    time_span = duration_cast<duration<double>>(t2-t1);
    std::cout << "It takes " << time_span.count() << " seconds to cast PolarString to int64_t.";
    std::cout << std::endl;


    t1 = high_resolution_clock::now();
    //int64_t int3 = polar_str_to_int64(a);
    auto ps1 = PolarString(reinterpret_cast<char *>(&int1), sizeof(int64_t));
    t2 = high_resolution_clock::now();

    time_span = duration_cast<duration<double>>(t2-t1);
    std::cout << "It takes " << time_span.count() << " seconds to cast int64_t to PolarString.";
    std::cout << std::endl;


    t1 = high_resolution_clock::now();
    memcpy(chars, &int1, sizeof(uint64_t));
    PolarString polar(chars,8);
    t2 = high_resolution_clock::now();

    time_span = duration_cast<duration<double>>(t2-t1);
    std::cout << "It takes " << time_span.count() << " seconds to cast int64_t to PolarString.";
    std::cout << std::endl;



//conclusion: after several runs we can see that cast from char * to PolarString is the most slow



}