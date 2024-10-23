#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

const size_t MB = 1024 * 1024;
const size_t ALLOCATION_SIZE = 10 * MB;  // 10MB chunks

int main() {
    std::vector<char*> leaks;
    size_t totalAllocated = 0;

    std::cout << "Starting continuous memory allocation..." << std::endl;

    // Continuous growth pattern with pauses to simulate real usage
    while (true) {
        char* leak = new (std::nothrow) char[ALLOCATION_SIZE];
        if (leak == nullptr) {
            std::cout << "Memory allocation failed at: " << totalAllocated / MB << " MB" << std::endl;
            break;
        }

        // Write to memory to ensure it's committed
        memset(leak, 1, ALLOCATION_SIZE);
        leaks.push_back(leak);
        totalAllocated += ALLOCATION_SIZE;

        std::cout << "Allocated: " << totalAllocated / MB << " MB\r" << std::flush;

        // Sleep between allocations to create a more natural growth pattern
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Simulate some memory access to show it's being used
        if (totalAllocated % (100 * MB) == 0) {
            for (auto ptr : leaks) {
                memset(ptr, 2, ALLOCATION_SIZE);  // Periodic access
            }
        }
    }

    std::cout << "\nKeeping program alive. Press Ctrl+C to exit." << std::endl;
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
