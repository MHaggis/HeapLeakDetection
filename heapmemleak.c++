#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

int main() {
    while (true) {
        int* leak = new int[1000];  // Allocate memory but don't free it
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Sleep for 10ms
    }
    return 0;
}
