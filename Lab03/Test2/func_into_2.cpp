#include "func_into_2.h"

long long int into_2(size_t num)
{
    long long int bin = 0, k = 1;

    while (num > 0)
    {
        bin += (num % 2) * k;
        k *= 10;
        num /= 2;
    }

    return bin;
}
string numbers_2(long long int num)
{
    string str= to_string(num);
    if(str.length()% 8 != 0)
    {
        size_t ost = 8 - (str.length() % 8);
        for(size_t i = 0; i < ost; i ++)
        {
            str.insert(0,"0");
        }
    }
    return str;
}
