#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <format>

std::mutex mtx;

void worker(uint32_t id)
{
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << std::format("worker {}\n", id);
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main(int argc, char const *argv[])
{
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    
    t1.join();
    t2.join();
    return 0;
}

