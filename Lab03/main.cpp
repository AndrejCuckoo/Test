#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <fstream>
#include <curl/curl.h>
#include <sstream>
#include <string>
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

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input
download(const string& address) {
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res)
        {
            cout << curl_easy_strerror(res) << endl;
            exit(1);
        }
    }
   curl_easy_cleanup(curl);

    return read_input(buffer, false);
}

int main(int argc, char* argv[]) {
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }
    const auto bins = make_histogram(input.numbers,input.bin_count);
    show_histogram_svg(bins,input.bin_height,input.bin_count);
    return 0;
}
