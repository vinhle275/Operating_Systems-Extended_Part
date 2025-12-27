#include "../include/CASWeakBackoffCounter.h"
#include <thread>
#include <chrono>

#define MAX_DELAY 1024 

CASWeakBackoffCounter::CASWeakBackoffCounter() : value(0) {}

void CASWeakBackoffCounter::increment() {
    long long expected = value.load();
    unsigned delay = 1;

    while (!value.compare_exchange_weak(expected, expected + 1)) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(delay));
        if (delay < MAX_DELAY) {
            delay *= 2;
        }
    }
}

long long CASWeakBackoffCounter::get() {
    return value.load();
}

void CASWeakBackoffCounter::reset() {
    value.store(0);
}