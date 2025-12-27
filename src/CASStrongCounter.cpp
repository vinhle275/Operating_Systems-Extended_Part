#include "../include/CASStrongCounter.h"

CASStrongCounter::CASStrongCounter() : value(0) {}

void CASStrongCounter::increment() {
    long long expected = value.load();
    while (!value.compare_exchange_strong(expected, expected + 1)) {
    }
}

long long CASStrongCounter::get() {
    return value.load();
}

void CASStrongCounter::reset() {
    value.store(0);
}