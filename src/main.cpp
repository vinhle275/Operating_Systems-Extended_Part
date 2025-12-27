#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>

#include "../include/Counter.h"

#include "../include/MutexCounter.h"
#include "../include/AtomicSeqCstCounter.h"   
#include "../include/AtomicRelaxedCounter.h"  
#include "../include/CASWeakCounter.h"        
#include "../include/CASStrongCounter.h"      
#include "../include/CASWeakBackoffCounter.h" 
#include "../include/CASStrongBackoffCounter.h" 
#include "../include/SpinLockCounter.h"
#include "../include/TicketLockCounter.h"
#include "../include/SemaphoreCounter.h" 

const int TOTAL_INCREMENTS = 1000000; 


void worker(Counter* counter, int num_increments) {
    for (int i = 0; i < num_increments; ++i) {
        counter->increment();
    }
}


double run_test(Counter* counter, int num_threads, const std::string& name) {
    counter->reset();
    std::vector<std::thread> threads;
    
    int increments_per_thread = TOTAL_INCREMENTS / num_threads;
    int remainder = TOTAL_INCREMENTS % num_threads;

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        int workload = increments_per_thread + (i < remainder ? 1 : 0);
        threads.emplace_back(worker, counter, workload);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    if (counter->get() != TOTAL_INCREMENTS) {
        std::cerr << " [ERROR] " << name << " failed! Expected " 
                  << TOTAL_INCREMENTS << " but got " << counter->get() << std::endl;
    }

    return elapsed.count();
}

int main() {
    MutexCounter             mutexCounter;
    AtomicSeqCstCounter      atomSeqCounter;     
    AtomicRelaxedCounter     atomRelCounter;     
    CASWeakCounter           casWeakCounter;     
    CASStrongCounter         casStrongCounter;   
    CASWeakBackoffCounter    casWeakBOCounter;   
    CASStrongBackoffCounter  casStrongBOCounter; 
    SpinLockCounter          spinLockCounter;
    TicketLockCounter        ticketLockCounter;
    SemaphoreCounter         semCounter; 

    std::vector<int> thread_counts;
    for (int i = 1; i <= 100; i += 5) {
        thread_counts.push_back(i);
    }
    
    std::cout << "========================================================================\n";
    std::cout << "      BENCHMARK SO SÁNH HIỆU NĂNG ĐỒNG BỘ HÓA (C++ CONCURRENCY)       \n";
    std::cout << "========================================================================\n";
    std::cout << "Cau hinh: " << TOTAL_INCREMENTS << " increments / luot chay.\n";
    std::cout << "Don vi thoi gian: Giay (Seconds) - Thap hon la tot hon.\n\n";
    
    std::cout << "--- GIAI THICH (LEGEND) ---\n";
    std::cout << " CAS Wk+Backoff : CAS Weak ket hop chien thuat 'Ngu' (Sleep) khi that bai\n";
    std::cout << " CAS Str+Backoff: CAS Strong ket hop chien thuat 'Ngu' (Sleep) khi that bai\n";
    std::cout << "------------------------------------------------------------------------\n\n";

    std::cout << std::left << std::setw(8) << "Threads" 
              << std::setw(10) << "Mutex" 
              << std::setw(12) << "Atom(Seq)" 
              << std::setw(12) << "Atom(Rel)"
              << std::setw(12) << "CAS(Weak)" 
              << std::setw(12) << "CAS(Str)" 
              << std::setw(16) << "CAS(Wk+BO)"
              << std::setw(16) << "CAS(Str+BO)"
              << std::setw(12) << "SpinLock"
              << std::setw(10) << "Ticket"
              << std::setw(12) << "Semaphore" 
              << std::endl;
    

    std::cout << std::string(134, '-') << std::endl;

    // 5. Chạy Test
    for (int t : thread_counts) {
        double t_mutex    = run_test(&mutexCounter, t, "Mutex");
        double t_atom_sc  = run_test(&atomSeqCounter, t, "Atomic(Seq)");
        double t_atom_rl  = run_test(&atomRelCounter, t, "Atomic(Rel)");
        
        double t_cas_wk   = run_test(&casWeakCounter, t, "CAS(Weak)");
        double t_cas_str  = run_test(&casStrongCounter, t, "CAS(Strong)");
        
        double t_wk_bo    = run_test(&casWeakBOCounter, t, "CAS(Wk+BO)");
        double t_str_bo   = run_test(&casStrongBOCounter, t, "CAS(Str+BO)");

        double t_spin     = run_test(&spinLockCounter, t, "SpinLock");
        double t_ticket   = run_test(&ticketLockCounter, t, "TicketLock");
        
        double t_sem      = run_test(&semCounter, t, "Semaphore"); 

        std::cout << std::left << std::setw(8) << t 
                  << std::setw(10) << std::fixed << std::setprecision(4) << t_mutex 
                  << std::setw(12) << t_atom_sc
                  << std::setw(12) << t_atom_rl
                  << std::setw(12) << t_cas_wk 
                  << std::setw(12) << t_cas_str
                  << std::setw(16) << t_wk_bo
                  << std::setw(16) << t_str_bo
                  << std::setw(12) << t_spin
                  << std::setw(10) << t_ticket
                  << std::setw(12) << t_sem 
                  << std::endl;
    }

    return 0;
}