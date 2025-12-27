# Operating_Systems-Extended_Part

Dự án này là một bộ công cụ đo lường hiệu năng nhằm so sánh tốc độ và hiệu quả của các cơ chế đồng bộ hóa khác nhau trong lập trình đa luồng C++.

Dự án cài đặt và kiểm thử từ các loại khóa cơ bản (Mutex, Semaphore) đến các kỹ thuật nâng cao không khóa (Lock-free), Atomic, và các chiến thuật tối ưu hóa (Backoff strategies).

## 📋 Danh sách các kỹ thuật được cài đặt

Dự án bao gồm 10 biến thể của bộ đếm (`Counter`) an toàn luồng:

### 1. Cơ chế khóa (Blocking & Spinning)
* **MutexCounter:** Sử dụng `std::mutex` của hệ điều hành (Blocking lock).
* **SemaphoreCounter:** Sử dụng `std::binary_semaphore` (C++20) để quản lý truy cập.
* **SpinLockCounter:** Sử dụng `std::atomic_flag` với thuật toán Test-Test-And-Set (TTAS) để busy-wait (tốt cho critical section ngắn).
* **TicketLockCounter:** Cơ chế khóa công bằng (Fair lock) đảm bảo thứ tự trước-sau (FIFO), tránh hiện tượng "đói" tài nguyên (starvation).

### 2. Atomic & Memory Ordering (Lock-free)
* **AtomicSeqCstCounter:** Sử dụng `std::atomic` với mô hình bộ nhớ mặc định (Sequentially Consistent - An toàn nhất).
* **AtomicRelaxedCounter:** Sử dụng `std::memory_order_relaxed`. Hiệu năng cao nhất do cho phép CPU sắp xếp lại lệnh, chỉ đảm bảo tính nguyên tử.

### 3. Compare-And-Swap (CAS)
* **CASStrongCounter:** Sử dụng `compare_exchange_strong`.
* **CASWeakCounter:** Sử dụng `compare_exchange_weak` (Có thể thất bại giả nhưng nhanh hơn trên một số kiến trúc CPU).

### 4. Optimized CAS (Backoff Strategies)
* **CASStrongBackoffCounter:** CAS Strong kết hợp chiến thuật "Backoff" (ngủ theo hàm mũ) để giảm tranh chấp bus bộ nhớ khi tải cao.
* **CASWeakBackoffCounter:** CAS Weak kết hợp chiến thuật "Backoff".

---

## 📂 Cấu trúc Thư mục


```text
.
├── Makefile                
├── README.md               
├── include/               
│   ├── Counter.h
│   ├── MutexCounter.h
│   ├── SpinLockCounter.h
│   ├── TicketLockCounter.h
│   ├── SemaphoreCounter.h
│   ├── AtomicSeqCstCounter.h
│   ├── AtomicRelaxedCounter.h
│   ├── CASStrongCounter.h
│   ├── CASWeakCounter.h
│   ├── CASStrongBackoffCounter.h
│   └── CASWeakBackoffCounter.h
└── src/                    
    ├── main.cpp            
    ├── MutexCounter.cpp
    ├── SpinLockCounter.cpp
    ├── TicketLockCounter.cpp
    ├── SemaphoreCounter.cpp
    ├── AtomicSeqCstCounter.cpp
    ├── AtomicRelaxedCounter.cpp
    ├── CASStrongCounter.cpp
    ├── CASWeakCounter.cpp
    ├── CASStrongBackoffCounter.cpp
    └── CASWeakBackoffCounter.cpp
```

## 🛠 Yêu cầu Hệ thống
* **Hệ điều hành: Linux (Ubuntu, Debian...) hoặc WSL trên Windows.
* **Trình biên dịch: g++ (GCC) hỗ trợ chuẩn C++20 (bắt buộc vì dùng <semaphore> và <atomic>).
* **Kiểm tra version: g++ --version (Nên dùng version 10 trở lên).
* **Công cụ: make.

## 🚀 Hướng dẫn Biên dịch và Chạy

Bước 1:

Mở terminal tại thư mục gốc của dự án (nơi chứa file Makefile) và gõ lệnh:
```text
make all
```

Bước 2:

Sau khi biên dịch xong, gõ lệnh sau để bắt đầu test:

```text
./run
```












