#ifndef CAS_WEAK_BACKOFF_COUNTER_H
#define CAS_WEAK_BACKOFF_COUNTER_H

#include "Counter.h"
#include <atomic>

class CASWeakBackoffCounter : public Counter {
private:
    std::atomic<long long> value;
public:
    CASWeakBackoffCounter();
    void increment() override;
    long long get() override;
    void reset() override;
};

#endif