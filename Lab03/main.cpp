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


void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}
void
show_histogram_svg(const vector<size_t>& bins) {
    svg_begin(400, 300);
    svg_end();
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
    show_histogram_svg(bins);

    return 0;
}
