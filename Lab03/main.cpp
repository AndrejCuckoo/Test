#include <iostream>
#include <vector>
#include "histogram.h"
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

void svg_text(double left,double baseline, string text)
{
    cout<< "<text x='" << left << "' y='" << baseline << "'>"<< text<< "</text>";
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


void svg_end() {
    cout << "</svg>\n";
}
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout<< "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='"<< stroke <<"' fill='"<<fill<<"'/>";
}

double scaling(double IMAGE_HEIGHT,double BIN_HEIGHT,double bin_count){
    double height = bin_count*BIN_HEIGHT;
    if(height<=IMAGE_HEIGHT &&height>0){
        height = IMAGE_HEIGHT/bin_count;
    }
    return height;
}

void show_histogram_svg(const vector<size_t>& bins,double BIN_HEIGHT,double bin_count) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 700;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
//    const auto BLOCK_WIDTH = 1;
    const auto STROKE = "aqua";
    const auto FILL = "darkblue";
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    double top = 0;
    double maxima=-1;
    for (size_t bin : bins) {
            if(maxima <bin){
                maxima = bin;
            }
    }
    for (size_t bin : bins) {
        const double bin_width = IMAGE_WIDTH *bin/ maxima;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,STROKE,FILL);
        top += BIN_HEIGHT;
    }
    svg_end();
}


int main() {
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
