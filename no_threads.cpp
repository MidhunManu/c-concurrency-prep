#include <iostream>
#include <thread>

int main()
{
	unsigned int n = std::thread::hardware_concurrency();
	std::cout << std::this_thread::get_id() << "\n";
	std::cout << n << "\n";
}

