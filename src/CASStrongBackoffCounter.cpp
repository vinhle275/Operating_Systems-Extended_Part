#include "../include/CASStrongBackoffCounter.h"
#include <thread>
#include <chrono>

#define MAX_DELAY 1024 

CASStrongBackoffCounter::CASStrongBackoffCounter() : value(0) {}

void CASStrongBackoffCounter::increment() {
    long long expected = value.load();
    unsigned delay = 1;

    while (!value.compare_exchange_strong(expected, expected + 1)) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(delay));
        if (delay < MAX_DELAY) {
            delay *= 2;
        }
    }
}

long long CASStrongBackoffCounter::get() {
    return value.load();
}

void CASStrongBackoffCounter::reset() {
    value.store(0);
}