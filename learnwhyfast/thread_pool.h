//
// Created by zgl on 19-4-9.
//

#ifndef ENGINE_THREAD_POOL_H
#define ENGINE_THREAD_POOL_H

#endif //ENGINE_THREAD_POOL_H


class ThreadPool {
public:
    explicit ThreadPool(size_t threads);

    template <class F, class ... Args>
            auto enqueue(F &&f, Args &&... args)

};
