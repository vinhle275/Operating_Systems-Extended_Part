#include "../include/AtomicSeqCstCounter.h"

AtomicSeqCstCounter::AtomicSeqCstCounter() : value(0) {}

void AtomicSeqCstCounter::increment() {
    value.fetch_add(1); 
}

long long AtomicSeqCstCounter::get() {
    return value.load();
}

void AtomicSeqCstCounter::reset() {
    value.store(0);
}