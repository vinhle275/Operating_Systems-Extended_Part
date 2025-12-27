#include "../include/AtomicRelaxedCounter.h"

AtomicRelaxedCounter::AtomicRelaxedCounter() : value(0) {}

void AtomicRelaxedCounter::increment() {
    value.fetch_add(1, std::memory_order_relaxed);
}

long long AtomicRelaxedCounter::get() {
    return value.load(std::memory_order_relaxed);
}

void AtomicRelaxedCounter::reset() {
    value.store(0, std::memory_order_relaxed);
}