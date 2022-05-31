#pragma once
#include <vector>


class Fibonacci
{
public:
	std::vector <unsigned int> row;
	std::vector <unsigned int> sum;
	int end = 0;
	int oder;
	Fibonacci(int _oder);
	unsigned int next();
	unsigned int get() const;
	int getOder() const;
	int operator[](int i) const;
};