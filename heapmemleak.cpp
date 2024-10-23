#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

const size_t MB = 1024 * 1024;
const size_t ALLOCATION_SIZE = 1 * MB;  // Allocate 1MB at a time

int main() {
    // Get system memory info
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    
    // Get total physical memory
    size_t totalPhysMem = memInfo.ullTotalPhys;

    // Calculate 5.1% of total physical memory
    size_t targetMemory = static_cast<size_t>(totalPhysMem * 0.051);

    // Increase the duration to ensure detection
    const int DURATION_MINUTES = 10;  // Increased from 6 to 10 minutes to ensure detection

    auto start_time = std::chrono::steady_clock::now();
    std::vector<char*> leaks;

    size_t totalAllocated = 0;

    while (true) {
        // Only check if we've hit our time limit
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::minutes>(current_time - start_time).count();
        
        if (elapsed_time >= DURATION_MINUTES) {
            break;
        }

        // Keep allocating until we hit our target
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

        // Small sleep to prevent CPU thrashing
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\nMemory leak simulation completed. Total leaked: " 
              << totalAllocated / MB << " MB" << std::endl;

    // Add cleanup code before infinite loop
    std::cout << "\nStarting cleanup phase..." << std::endl;
    for (char* ptr : leaks) {
        delete[] ptr;
    }
    leaks.clear();

    std::cout << "Keeping program alive. Press Ctrl+C to exit." << std::endl;
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
