#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#endif // HISTOGRAM_H_INCLUDED
#pragma once
#include <vector>

using namespace std;
struct Input {
    vector<double> numbers;
    size_t bin_count;
    size_t number_count;
    double bin_height;
};
void find_minmax(vector<double> numbers,double& min, double& max);
