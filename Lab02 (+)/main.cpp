#include <iostream>
#include "Complex.h"

int main() {
	system("chcp 65001 > nul");

	Complex a, b;

	a.Init(10, 15);
	b.Init(56, 2);
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << a/b;
}