#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

const size_t MB = 1024 * 1024;

int main() {
    const int DURATION_MINUTES = 6;  // Run for 6 minutes to ensure at least one check
    const size_t ALLOCATION_SIZE = 10 * MB;  // Allocate 10MB at a time for finer control

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;

    // Calculate 5.1% of total physical memory (just above the 5% threshold)
    size_t targetMemory = static_cast<size_t>(totalPhysMem * 0.051);

    auto start_time = std::chrono::steady_clock::now();
    std::vector<char*> leaks;

    size_t totalAllocated = 0;

    while (true) {
        if (totalAllocated < targetMemory) {
            char* leak = new (std::nothrow) char[ALLOCATION_SIZE];
            if (leak == nullptr) {
                std::cout << "Memory allocation failed. Total allocated: " 
                          << totalAllocated / MB << " MB" << std::endl;
                break;
            }
            
            memset(leak, 1, ALLOCATION_SIZE);
            leaks.push_back(leak);
            totalAllocated += ALLOCATION_SIZE;

            std::cout << "Allocated: " << totalAllocated / MB << " MB\r" << std::flush;
        }

        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::minutes>(current_time - start_time).count();
        
        if (elapsed_time >= DURATION_MINUTES) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\nMemory leak simulation completed. Total leaked: " 
              << totalAllocated / MB << " MB" << std::endl;

    std::cout << "Keeping program alive. Press Ctrl+C to exit." << std::endl;
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
