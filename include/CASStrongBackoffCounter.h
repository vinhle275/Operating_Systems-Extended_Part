#ifndef CAS_STRONG_BACKOFF_COUNTER_H
#define CAS_STRONG_BACKOFF_COUNTER_H

#include "Counter.h"
#include <atomic>

class CASStrongBackoffCounter : public Counter {
private:
    std::atomic<long long> value;
public:
    CASStrongBackoffCounter();
    void increment() override;
    long long get() override;
    void reset() override;
};

#endif