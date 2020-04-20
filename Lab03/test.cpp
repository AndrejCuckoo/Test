#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 4}, min, max);
    assert(min == 1);
    assert(max == 4);
}
void
test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-2, -1, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void
test_similar() {
    double min = 0;
    double max = 0;
    find_minmax({2, 2, 2}, min, max);
    assert(min == 2);
    assert(max == 2);
}

void
test_one_number() {
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void
test_empty_array() {
    double min = 0;
    double max = 0;
    vector <double> arr = {};
    if (arr.size()>0){
    find_minmax({}, min, max);
    assert(min == 1);
    assert(max == 1);
    }
}

int
main() {
    test_positive();
    test_negative();
    test_similar();
    test_one_number();
    test_empty_array();
}
