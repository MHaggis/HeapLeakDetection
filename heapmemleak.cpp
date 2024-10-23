#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <windows.h>

const size_t MB = 1024 * 1024;
const size_t ALLOCATION_SIZE = 100 * MB;  // Increased to 10MB chunks for faster allocation

int main() {
    std::vector<char*> leaks;
    size_t totalAllocated = 0;

    std::cout << "Starting continuous memory allocation..." << std::endl;

    while (true) {
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

        // Slightly longer sleep to give Windows time to detect
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\nKeeping program alive to maintain allocations. Press Ctrl+C to exit." << std::endl;
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
