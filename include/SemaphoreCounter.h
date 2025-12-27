#pragma once
#include "Counter.h"
#include <semaphore> 

class SemaphoreCounter : public Counter {
private:
    std::binary_semaphore sem_{1}; 
    volatile long long value_ = 0; 
public:
    SemaphoreCounter() = default;

    void increment() override;
    
    long long get() override; 
    
    void reset() override;
};