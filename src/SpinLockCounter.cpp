#include "../include/SpinLockCounter.h"
#include <thread> 

SpinLockCounter::SpinLockCounter() : value(0), lock_flag(false) {}

void SpinLockCounter::lock() {

    while (true) {
        while (lock_flag.load(std::memory_order_relaxed)) {
             std::this_thread::yield(); 
        }

        if (!lock_flag.exchange(true, std::memory_order_acquire)) {
            return; 
        }
        std::this_thread::yield();
    }
}

void SpinLockCounter::unlock() {
    lock_flag.store(false, std::memory_order_release);
}

void SpinLockCounter::increment() {
    lock();
    value++;
    unlock();
}

long long SpinLockCounter::get() {
    lock(); 
    long long v = value;
    unlock();
    return v;
}

void SpinLockCounter::reset() {
    lock();
    value = 0;
    unlock();
}