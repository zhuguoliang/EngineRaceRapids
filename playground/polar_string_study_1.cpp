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

    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2-t1);
    std::cout << "It took me " << time_span.count() << " seconds.";
    std::cout << std::endl;


}