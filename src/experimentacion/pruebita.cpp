#include <iostream>
#include <chrono>


int main(int argc, char const *argv[])
{
	srand(time(0));
	for(unsigned i = 0; i < 10; ++i) {
		std::cout << "Numero aleatorio " << i << ": " << rand() << std::endl;
	}

	return 0;
}