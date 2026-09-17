#include <iostream>
#include <mutex>
#include <thread>
#include <format>

std::recursive_mutex mtx;

void worker(uint8_t id)
{
    mtx.lock();
    mtx.lock();
    std::cout << "locked\n";
    mtx.unlock();
    mtx.unlock();
    std::cout << "unlocked\n";
}

int main(int argc, char const *argv[])
{
    std::thread t1(worker, 1);
    t1.join();
    return 0;
}
