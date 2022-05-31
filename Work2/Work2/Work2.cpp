#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_MAX 10000
void siftDown(int* numbers, int root, int bottom)
{
    int maxChild;
    int done = 0;
    while ((root * 2 <= bottom) && (!done))
    {
        if (root * 2 == bottom)
            maxChild = root * 2;
        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        if (numbers[root] < numbers[maxChild])
        {
            int temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        }
        else
            done = 1;
    }
}
void heapSort(int* numbers, int array_size)
{
    unsigned int start_time = clock();
    for (int i = (array_size / 2); i >= 0; i--)
        siftDown(numbers, i, array_size - 1);
    for (int i = array_size - 1; i >= 1; i--)
    {
        int temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i - 1);
    }
    unsigned int end_time = clock();
    unsigned int search_time = start_time - end_time;
    std::cout << "Time: " << search_time << std::endl;
}
void fill_array(int *a) {
    const uint32_t rand_value = 13;

    std::srand(rand_value);

    for (size_t i = 0; i < ARRAY_MAX; i++) {
        a[i] = rand() % ARRAY_MAX;
    }
}
int main()
{
    int a[ARRAY_MAX];
    fill_array(a);
    for (int i = 0; i < ARRAY_MAX; i++)
        printf("%d ", a[i]);
    printf("\n");
    heapSort(a, ARRAY_MAX);
    for (int i = 0; i < ARRAY_MAX; i++)
        printf("%d ", a[i]);
    printf("\n");
    getchar();
    return 0;
}