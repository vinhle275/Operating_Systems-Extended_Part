#include "../include/SemaphoreCounter.h"

void SemaphoreCounter::increment() {
    sem_.acquire();
    
    value_ = value_ + 1;
    
    sem_.release();
}

long long SemaphoreCounter::get() {
    return value_;
}

void SemaphoreCounter::reset() {
    value_ = 0;
}