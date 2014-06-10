#ifndef UTILS_THREAD_HPP
#define UTILS_THREAD_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <vector>
#include <deque>

namespace utils
{
    namespace thread
    {
        class Pool
        {
            public:
                Pool(size_t number);
                ~Pool();

                template<typename F>
                void push(F f);


                size_t size();

                void wait(std::chrono::milliseconds d =std::chrono::milliseconds(500));


            private:
                std::atomic<bool> stop;
                std::deque<std::function<void()>> tasks;
                std::vector<std::thread> workers;
                //sync
                std::mutex mutex_tasks;
                std::condition_variable cv;
                std::condition_variable cv_end;


                class Worker
                {
                    public:
                        Worker(Pool& parent);
                        void operator()();
                    private:
                        Pool& parent;
                };


        };
    }
}
#include <utils/thread.tpl>
#endif
