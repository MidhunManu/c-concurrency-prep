#include <thread>
#include <iostream>
#include <vector>

std::vector<int> nums {};
std::mutex mtx;

void add(int num)
{
    if (mtx.try_lock())
    {
        nums.push_back(num);
        mtx.unlock();
    }
}

int main(int argc, char const *argv[])
{
    std::thread t1(add, 3);
    std::thread t2(add, 8);

    t1.join();
    t2.join();

    for(auto& num: nums)
    {
        std::cout << num << "\n";
    }
    return 0;
}
