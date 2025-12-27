#ifndef COUNTER_H
#define COUNTER_H

class Counter {
public:
    virtual void increment() = 0; 
    virtual long long get() = 0;  
    virtual void reset() = 0;     
    virtual ~Counter() {}
};

#endif