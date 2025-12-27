#ifndef ATOMIC_SEQ_CST_COUNTER_H
#define ATOMIC_SEQ_CST_COUNTER_H

#include "Counter.h"
#include <atomic>

class AtomicSeqCstCounter : public Counter {
private:
    std::atomic<long long> value;
public:
    AtomicSeqCstCounter();
    void increment() override;
    long long get() override;
    void reset() override;
};

#endif