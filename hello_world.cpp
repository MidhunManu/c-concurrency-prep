#include <iostream>
#include <thread>

void hello()
{
	std::cout << "hello concurrent world\n";
}

int main()
{
	std::thread t(hello);

	try
	{
		throw std::runtime_error("err");
	}
	catch(const std::exception& e)
	{
		t.join();
	}
}

