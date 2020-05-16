#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <fstream>
#include <curl/curl.h>
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

    cerr << "Enter bin count: ";
    size_t bin_count;
    cin >> bin_count;
    data.bin_count = bin_count;

    cerr << "Enter bin height: ";
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



int main(int argc, char* argv[]) {
    if(argc>1){

        CURL *curl = curl_easy_init();
        if(curl) {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            cout << res;
            curl_easy_cleanup(curl);
}
        return 0;
    }

    curl_global_init(CURL_GLOBAL_ALL);
    const auto input = read_input(cin,true);
    const auto bins = make_histogram(input.numbers,input.bin_count);
    show_histogram_svg(bins,input.bin_height,input.bin_count);
    return 0;
}
