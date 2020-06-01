#include "histogram.h"
#include <iostream>
#include <cassert>
#include "Svg.h"

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
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

void
test_Scailing() {
    double t = scaling(700, 30,3);
    assert(t == 30);

}

test_Scailing_02() {
    double t = scaling(700,40,0);
    assert(t == 0);

}

int
main() {
    test_positive();
    test_negative();
    test_similar();
    test_one_number();
    test_empty_array();
    test_Scailing();
    test_Scailing_02();
}
