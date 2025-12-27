#include "../include/TicketLockCounter.h"
#include <thread> 

TicketLockCounter::TicketLockCounter() : value(0), next_ticket(0), now_serving(0) {}

void TicketLockCounter::lock() {
    int my_ticket = next_ticket.fetch_add(1, std::memory_order_relaxed);

    while (now_serving.load(std::memory_order_acquire) != my_ticket) {
        std::this_thread::yield();
    }
}

void TicketLockCounter::unlock() {
    int current = now_serving.load(std::memory_order_relaxed);
    now_serving.store(current + 1, std::memory_order_release);
}

void TicketLockCounter::increment() {
    lock();
    value++;
    unlock();
}

long long TicketLockCounter::get() {
    return value;
}

void TicketLockCounter::reset() {
    lock();
    value = 0;
    unlock();
}