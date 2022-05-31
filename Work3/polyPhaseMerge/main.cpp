#include <iostream>
#include "polyPhaseMerge.h"
#include "testsHelper.h"

#define N 50000	
#define INPUT "input.txt"
#define OUTPUT "input(sorted).txt"

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");
	generator(INPUT, N);
	unsigned int start_time = clock();
	polyPhaseMerge(INPUT);
	unsigned int end_time = clock();
	unsigned int search_time = start_time - end_time;
	cout << "Time: " << search_time << endl;
	check(OUTPUT);
}
