#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <format>

std::mutex machine_A;
std::mutex machine_B;

void try_run_jobs(uint32_t id)
{
    int result = std::try_lock(machine_A, machine_B);
    if (result != -1)
    {
        std::cout << "machines are busy";
        exit(EXIT_FAILURE);
    }

    std::cout << std::format("worker {} is running job\n", id);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    machine_A.unlock();
    machine_B.unlock();
}

int main(int argc, char const *argv[])
{
    std::thread workerA(try_run_jobs, 1);
    std::thread workerB(try_run_jobs, 2);
    workerA.join();
    workerB.join();
    return 0;
}

