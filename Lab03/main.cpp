#include <iostream>
#include <vector>
#include "histogram.h"
#include "Svg.h"
#include <windows.h>
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
    auto info = GetVersion();
    DWORD build;
//    printf("n = %u\n",info);
//    printf("n = %08x\n", info); // 01234567
//    printf("n = %08o\n", info); // 01234567
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
//    cout << version << endl; // 518
    DWORD platform = info >> 16;
//    cout << platform << "  Build version" << endl;
    DWORD version_major = version & 0x00ff;
    DWORD version_minor = version >> 8;
//    cout << version_minor  << endl;
//    cout << version_major << endl;
//    printf("m_version10 = %lu\n",version_major);
//    printf("m_version16 = %08lx\n",version_major);
//    printf("M_version10 = %lu\n",version_minor);
//    printf("M_version16 = %08lx\n",version_minor);
    if ((info & 0b10000000'00000000'0000000'00000000) == 0) {
//        cout << "High-order bit is zero" << endl;
    }
    if ((info & 0x10000000) == 0) {
//        cout << "High-order bit is zero(16-bit)" << endl;
    }
//    printf("Windows v%lu.%lu (build %lu)\n",version_major,version_minor,build);
    string Ver ={"Windows v"};
    Ver.append(to_string(version_major));
    Ver.append(".");
    Ver.append(to_string(version_minor));
    Ver.append("  build: ");
    Ver.append(to_string(build));
    char buffer[256];
    unsigned long size = 256;
    GetComputerName( buffer, &size );

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

    show_histogram_svg(bins,bin_height,bin_count,buffer,Ver);
    return 0;
}
