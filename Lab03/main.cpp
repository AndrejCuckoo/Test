#include <iostream>
#include <vector>

using namespace std;

vector<double> input(size_t number_count){
    vector<double> numbers(number_count);
    for (size_t i = 0; i < number_count; i++) {
        cin >> numbers[i];
    }
    return numbers;
}

vector<double> minmaxe(vector<double>& numbers){
    //Поиск минимума и максимума соответственно
    vector<double> mimax(2,0);
    mimax[0] = numbers[0];
    mimax[1] = numbers[0];
    for (double number : numbers) {
        if (number < mimax[0]) {
            mimax[0] = number;
        }
        if (number > mimax[1]) {
            mimax[1] = number;
        }
    }
    return mimax;
}

vector<size_t> body(vector<double>& numbers,size_t bin_count){
    // Обработка данных
    vector<size_t> bins(bin_count);
    vector<double> mimax = minmaxe(numbers);
    for (double number : numbers) {
        size_t bin = (size_t)((number - mimax[0]) / (mimax[1] - mimax[0]) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

void Hist(vector<size_t>& bins){
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }
}

int main() {
    // Ввод данных
    size_t number_count;
    cin >> number_count;
    vector <double> numbers = input(number_count);
    size_t bin_count;
    cin >> bin_count;

    // Обработка данных
    vector<size_t>bins = body(numbers,bin_count);

    // Вывод данных
    Hist(bins);

    return 0;
}
