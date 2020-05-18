#include <iostream>
#include <vector>
#include "histogram.h"
#include "Svg.h"
using namespace std;

vector<double> input(size_t number_count){
    vector<double> numbers(number_count);
    for (size_t i = 0; i < number_count; i++) {
        cin >> numbers[i];
    }
    return numbers;
}



vector<size_t> body(const vector<double>& numbers,size_t bin_count){
    // Обработка данных
    vector<size_t> bins(bin_count);
    double min;
    double max;
    find_minmax(numbers,min,max);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}


int main() {

    const char* name = "Commander Shepard";
    int year = 2154;
    printf("%s was born in %d.\n", name, year);

    printf("n = %08x\n", 0x1234567); // 01234567
    return 0;

    // Ввод данных
    size_t number_count;
    cin >> number_count;
    vector <double> numbers = input(number_count);
    size_t bin_count;
    cin >> bin_count;
    // Height
    double bin_height;
    cin >> bin_height;
    // Обработка данных
    const auto bins = body(numbers,bin_count);
    // Вывод данных

    show_histogram_svg(bins,bin_height,bin_count);
    return 0;
}
