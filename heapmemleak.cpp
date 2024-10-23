#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>

const size_t MB = 1024 * 1024;

int main() {
    const int DURATION_SECONDS = 30;  // Reduced runtime to 30 seconds
    const size_t ALLOCATION_SIZE = 100 * MB;  // Allocate 100MB at a time

    auto start_time = std::chrono::steady_clock::now();
    std::vector<char*> leaks;  // Store pointers to prevent optimization

    while (true) {
        char* leak = new char[ALLOCATION_SIZE];
        leaks.push_back(leak);  // Store the pointer
        
        // Fill the allocated memory to ensure it's not optimized away
        memset(leak, 1, ALLOCATION_SIZE);

        // Check if we've been running for DURATION_SECONDS
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
        
        if (elapsed_time >= DURATION_SECONDS) {
            break;  // Exit the loop after DURATION_SECONDS
        }

        // No sleep to make it faster
    }

    std::cout << "Memory leak simulation completed. Total leaked: " 
              << (leaks.size() * ALLOCATION_SIZE) / MB << " MB" << std::endl;

    // Intentionally not freeing the memory to simulate the leak
    return 0;
}
