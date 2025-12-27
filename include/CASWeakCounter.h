#ifndef CAS_WEAK_COUNTER_H
#define CAS_WEAK_COUNTER_H

#include "Counter.h"
#include <atomic>

class CASWeakCounter : public Counter {
private:
    std::atomic<long long> value;
public:
    CASWeakCounter();
    void increment() override;
    long long get() override;
    void reset() override;
};

#endif