#ifndef SPINLOCK_COUNTER_H
#define SPINLOCK_COUNTER_H

#include "Counter.h"
#include <atomic>

class SpinLockCounter : public Counter {
private:
    long long value;
    std::atomic<bool> lock_flag;
    
    void lock();
    void unlock();

public:
    SpinLockCounter();
    void increment() override;
    long long get() override;
    void reset() override;
};

#endif