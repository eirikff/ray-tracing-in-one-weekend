#include <iostream>
#include <vector>
#include <ranges>
#include <string>

void print_vector(const std::string &name, const std::vector<int> &vector) {
	std::cout << name << " = ";
	for (const int &value : vector) {
		std::cout << value << ", ";
	}
	std::cout << std::endl;
}

int main (int argc, char *argv[]) {
	std::vector<int> v1{1, 2, 3};
	std::vector<int> v2{4, 5, 6};

	std::cout << "Before swap:" << std::endl;
	print_vector("v1", v1);
	print_vector("v2", v2);

	std::ranges::swap(v1, v2);

	std::cout << "After swap:" << std::endl;
	print_vector("v1", v1);
	print_vector("v2", v2);

	return 0;
}
