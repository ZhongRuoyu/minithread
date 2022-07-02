#include <chrono>
#include <iostream>
#include <thread>

#include <thread.h>

void independentThread() {
    std::cout << "Starting concurrent thread.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Exiting concurrent thread.\n";
}

void threadCaller() {
    std::cout << "Starting thread caller.\n";
    minithread::Thread t(independentThread);
    t.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Exiting thread caller.\n";
}

int main() {
    threadCaller();
    std::this_thread::sleep_for(std::chrono::seconds(5));
}