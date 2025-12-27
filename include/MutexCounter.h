#ifndef MUTEX_COUNTER_H
#define MUTEX_COUNTER_H

#include "Counter.h"
#include <mutex>

class MutexCounter : public Counter {
private:
    long long value;
    std::mutex mtx;
public:
    MutexCounter();
    void increment() override;
    long long get() override;
    void reset() override;
};

#endif