#include <thread>
#include <mutex>

std::mutex mtx;

void worker()
{
    std::lock_guard<std::mutex> lock1(mtx);
    std::lock_guard<std::mutex> lock2(mtx);
}

int main(int argc, char const *argv[])
{
    std::thread t1(worker);
    t1.join();   
    return 0;
}
