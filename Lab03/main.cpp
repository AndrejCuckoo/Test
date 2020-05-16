#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <fstream>
using namespace std;


vector<double> input_numbers(istream& in,size_t number_count){
    vector<double> numbers(number_count);
    for (size_t i = 0; i < number_count; i++) {
        in >> numbers[i];
    }
    return numbers;
}

Input read_input(istream& in,bool flag) {
    Input data;
    if(flag){
        cerr <<"Showing hints"<< endl;
    }
    cerr << "Enter number count: ";
    size_t number_count;
    cin >> number_count;
    data.number_count = number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    size_t bin_count;
    cin >> bin_count;
    data.bin_count = bin_count;

    double bin_height;
    cin >> bin_height;
    data.bin_height = bin_height;

    return data;
}

vector<size_t> make_histogram(const vector<double>& numbers,size_t bin_count){
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
    const auto input = read_input(cin,true);
    const auto bins = make_histogram(input.numbers,input.bin_count);
    show_histogram_svg(bins,input.bin_height,input.bin_count);
    return 0;
}
