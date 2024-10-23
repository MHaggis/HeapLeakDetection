#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

const size_t MB = 1024 * 1024;
const size_t ALLOCATION_SIZE = 50 * MB;  // Increased to 50MB chunks for faster growth

int main() {
    std::vector<char*> leaks;
    size_t totalAllocated = 0;

    std::cout << "Starting aggressive memory allocation..." << std::endl;

    while (true) {
        char* leak = new (std::nothrow) char[ALLOCATION_SIZE];
        if (leak == nullptr) {
            std::cout << "\nAllocation failed at: " << totalAllocated / MB << " MB" << std::endl;
            break;
        }

        // Write to memory to ensure it's committed
        memset(leak, 1, ALLOCATION_SIZE);
        leaks.push_back(leak);
        totalAllocated += ALLOCATION_SIZE;

        std::cout << "Allocated: " << totalAllocated / MB << " MB\r" << std::flush;

        // Access memory periodically to show it's being used
        if (totalAllocated % (500 * MB) == 0) {
            for (auto ptr : leaks) {
                memset(ptr, 2, ALLOCATION_SIZE);
            }
        }

        // Small sleep to prevent CPU thrashing but keep allocation aggressive
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\nKeeping allocations active. Press Ctrl+C to exit." << std::endl;
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
