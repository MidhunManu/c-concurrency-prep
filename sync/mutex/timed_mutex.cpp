#include <iostream>
#include <mutex>
#include <thread>
#include <format>
#include <chrono>

std::timed_mutex mtx;

void worker(uint32_t id)
{
    if (mtx.try_lock_for(std::chrono::seconds(2)))
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << std::format("{} accuired lock\n", id);
        mtx.unlock();
    }
    else
    {
        std::cout << "deadline reached\n";
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);

    t1.join();
    t2.join();
    return 0;
}

