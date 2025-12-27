#include "../include/MutexCounter.h"

MutexCounter::MutexCounter() : value(0) {}

void MutexCounter::increment() {
    std::lock_guard<std::mutex> lock(mtx);
    value++;
}

long long MutexCounter::get() {
    std::lock_guard<std::mutex> lock(mtx);
    return value;
}

void MutexCounter::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    value = 0;
}