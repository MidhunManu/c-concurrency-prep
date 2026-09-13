#include <thread>
#include <format>
#include <iostream>
#include <string>
#include <fstream>
#include <mutex>
#include <condition_variable>

std::fstream file(
    "buffer.txt",
    std::ios::in |
    std::ios::out |
    std::ios::binary |
    std::ios::trunc
);

std::mutex file_mutex;
std::condition_variable cv;

bool data_ready = false;

void produce(std::string data)
{
    {
        std::lock_guard<std::mutex> lock(file_mutex);

        file << data;
        file.flush();

        data_ready = true;
    }

    cv.notify_one();
}

void consume()
{
    std::unique_lock<std::mutex> lock(file_mutex);

    cv.wait(lock, [] {
        return data_ready;
    });

    file.seekg(0);

    std::string data;
    file >> data;

    std::cout << std::format("consumed: {}\n", data);
}

int main()
{
    std::thread producer(produce, "hello");
    std::thread consumer(consume);

    producer.join();
    consumer.join();

    return 0;
}

