#ifndef ATOMIC_RELAXED_COUNTER_H
#define ATOMIC_RELAXED_COUNTER_H

#include "Counter.h"
#include <atomic>

class AtomicRelaxedCounter : public Counter {
private:
    std::atomic<long long> value;
public:
    AtomicRelaxedCounter();
    void increment() override;
    long long get() override;
    void reset() override;
};

#endif