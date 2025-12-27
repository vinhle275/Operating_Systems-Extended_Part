#ifndef TICKET_LOCK_COUNTER_H
#define TICKET_LOCK_COUNTER_H

#include "Counter.h"
#include <atomic>

class TicketLockCounter : public Counter {
private:
    long long value;
    std::atomic<int> next_ticket; 
    std::atomic<int> now_serving; 

    void lock();
    void unlock();

public:
    TicketLockCounter();
    void increment() override;
    long long get() override;
    void reset() override;
};

#endif