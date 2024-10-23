#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

int main() {
    const int DURATION_SECONDS = 60;  // Run for 60 seconds
    const int ALLOCATION_SIZE = 1000000;  // Allocate 1 million integers each time

    auto start_time = std::chrono::steady_clock::now();

    while (true) {
        int* leak = new int[ALLOCATION_SIZE];  // Allocate more memory
        
        // Check if we've been running for DURATION_SECONDS
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
        
        if (elapsed_time >= DURATION_SECONDS) {
            break;  // Exit the loop after DURATION_SECONDS
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Sleep for 10ms
    }

    std::cout << "Memory leak simulation completed." << std::endl;
    return 0;
}