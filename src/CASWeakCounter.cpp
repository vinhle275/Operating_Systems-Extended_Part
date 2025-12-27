#include "../include/CASWeakCounter.h"
#include <thread> 

CASWeakCounter::CASWeakCounter() : value(0) {}

void CASWeakCounter::increment() {
    long long expected = value.load();
    while (!value.compare_exchange_weak(expected, expected + 1)) {
    }
}

long long CASWeakCounter::get() {
    return value.load();
}

void CASWeakCounter::reset() {
    value.store(0);
}