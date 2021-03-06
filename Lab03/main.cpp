#include <iostream>
#include <vector>
#include "histogram.h"
//<<<<<<< HEAD

#include <fstream>
#include <curl/curl.h>
#include <sstream>
#include <string>
//=======
#include "Svg.h"
#include <windows.h>
//>>>>>>> lab04-2
using namespace std;


double bin_height;
size_t number_count;

vector<double> input_numbers(istream& in,size_t number_count)
{
    vector<double> numbers(number_count);
    for (size_t i = 0; i < number_count; i++)
    {
        in >> numbers[i];
    }
    return numbers;
}


Input read_input(istream& in,bool flag)
{
    Input data;
    if(flag)
    {
        cerr <<"Showing hints"<< endl;
    }
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    data.number_count = number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    size_t bin_count;
    in >> bin_count;
    data.bin_count = bin_count;

    cerr << "Enter bin height: ";
    double bin_height;
    in >> bin_height;
    data.bin_height = bin_height;

    return data;
}

vector<size_t> make_histogram(const vector<double>& numbers,size_t bin_count)
{
    // ��������� ������
    vector<size_t> bins(bin_count);
    double min;
    double max;
    find_minmax(numbers,min,max);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

//<<<<<<< HEAD
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
download(const string& address)
{
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl)
    {
        double speed;
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (!res)
        {
            res = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &speed);
            if (!res)
            {
                cerr << "Speed: " << speed << endl;
            }
            else
            {
                cout << curl_easy_strerror(res) << endl;
                exit(1);
            }
        }
        curl_easy_cleanup(curl);
        return read_input(buffer, false);
    }
}



    int main(int argc, char* argv[])
    {
//        double c = 125.64857;
//        printf("%10.1f", c);
        Input input;
        auto info = GetVersion();
        DWORD build;
//        printf("%x", 15);
//    printf("n = %u\n",info);
//    printf("n = %08x\n", info); // 01234567
//    printf("n = %08o\n", info); // 01234567
        DWORD mask = 0b00000000'00000000'11111111'11111111;
        DWORD version = info & mask;
        DWORD platform = info >> 16;
        DWORD version_major = version & 0x00ff;
        DWORD version_minor = version >> 8;
        if ((info & 0x80000000) == 0)
        {
            build = platform;
        }

//    printf("Windows v%lu.%lu (build %lu)\n",version_major,version_minor,build);
        string Ver = {"Windows v"};
        Ver.append(to_string(version_major));
        Ver.append(".");
        Ver.append(to_string(version_minor));
        Ver.append("  build: ");
        Ver.append(to_string(build));
        char buffer[256];
        unsigned long size = 256;
        GetComputerName( buffer, &size );

        // ���� ������

        if (argc > 1)
        {
            input = download(argv[1]);
        }
        else
        {
            input = read_input(cin, true);
        }

        // ��������� ������
        const auto bins = make_histogram(input.numbers,input.bin_count);
        // ����� ������

        show_histogram_svg(bins,input.bin_height,input.bin_count,buffer,Ver);

        return 0;
    }
