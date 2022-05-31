#include <iostream>
#include <time.h>

using namespace std;

void quickSort(int* a, int size) {
    int i = 0;
    int j = size - 1;
    int mid = a[size / 2];

    do {
        while (a[i] < mid) {
            i++;
        }
        while (a[j] > mid) {
            j--;
        }
        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    } while (i <= j);


    if (j > 0) {
        quickSort(a, j + 1);
    }
    if (i < size) {
        quickSort(&a[i], size - i);
    }
}

void fill_array(int* a, int size) {
    const uint32_t rand_value = 13;

    std::srand(rand_value);

    for (size_t i = 0; i < size; i++) {
        a[i] = rand() % size;
    }
}

void reverseSort(int* a, int size) {
    quickSort(a, size);
    int middle = size / 2;
    for (int i = 0; i < middle; i++) {
        swap(a[i], a[size - i - 1]);

    }
}

void search(int* a, int size) {
    int countIterations = 0;
    int flag = 0;
    int symbol;
    cin >> symbol;
    for (int i = 0; i < size; i++) {
        countIterations++;
        if (a[i] == symbol) {
            countIterations++;
            flag = 1;
            cout << "Index: ";
            cout << i << endl;
            cout << "Iterations: " << countIterations << endl;
            break;
        }
    }
    if (flag == 0) {
        cout << "нет такого номера, выберите другой: " << endl;
        search(a, size);
    }
}

int main() {
    setlocale(0, "Rus");
    int size;
    cout << "Введите размер массива: ";
    cin >> size;
    int* a = new int[size];

    fill_array(a, size);
    
    cout << "Введите номер, чтобы выбрать вариант поиска:\n\
        1 - поиск в массиве, отсортированном по возрастания\n\
        2 - поиск в массиве, отсортированном по убыванию\n\
        3 - поиск в несортированном массиве" << endl;
    string choice;
    cin >> choice;

    if (choice == "1") {
        unsigned int start_time = clock();
        quickSort(a, size);
        unsigned int end_time = clock();
        unsigned int search_time = start_time - end_time;
        cout << "Time: " << search_time << endl;
    }
    if (choice == "2") {
        unsigned int start_time = clock();
        reverseSort(a, size);
        unsigned int end_time = clock();
        unsigned int search_time = start_time - end_time;
        cout << "Time: " << search_time << endl;
    }
    cout << "Введите число не выше 100: ";
    unsigned int start_time = clock();
    search(a, size);
    unsigned int end_time = clock();
    unsigned int search_time = start_time - end_time;
    cout << "Time: " << search_time << endl;
}