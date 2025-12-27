#ifndef CAS_STRONG_COUNTER_H
#define CAS_STRONG_COUNTER_H

#include "Counter.h"
#include <atomic>

class CASStrongCounter : public Counter {
private:
    std::atomic<long long> value;
public:
    CASStrongCounter();
    void increment() override;
    long long get() override;
    void reset() override;
};

#endif