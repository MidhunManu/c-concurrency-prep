#include <thread>
#include <format>
#include <iostream>
#include <vector>

std::vector<int> data {};

void put(int num)
{
	std::cout << std::thread::id() << " inserted " << num << "\n";
	data.push_back(num);
}

void put_even()
{
	for(int i = 0; i < 10; i++)
	{
		if (i % 2 == 0) {
			std::cout << std::format("thread {} put {}\n", std::this_thread::get_id(), i);
			data.push_back(i);
		}
	}
}

void put_odd()
{
	for(int i = 0; i < 10; i++)
	{
		if (i % 2 != 0) {
			std::cout << std::format("thread {} put {}\n", std::this_thread::get_id(), i);
			data.push_back(i);
		}
	}

}


int main()
{
	std::thread t1(put_even);
	std::thread t2(put_odd);

	t1.join();
	t2.join();
}

