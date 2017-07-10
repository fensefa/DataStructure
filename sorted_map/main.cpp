#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <sys/stat.h>
#include <nark/easy_use_hash_map.hpp>
#include <sys/time.h>

#define private public
#include "sorted_map.hpp"

using namespace std;

int64_t get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main() {
    cout << sizeof(pair<uint64_t, float>) << endl;
    cout << sizeof(size_t) << endl;
    cout << (bitset<64>(17316452917345324619ull))<< endl;
    cout << (bitset<64>(17316452917345324619ull >> 1))<< endl;
    cout << (bitset<64>(17316452917345324619ull >> 63))<< endl;
    cout << (bitset<64>(17316452917345324619ull >> 64))<< endl;
    ifstream in("data.bin", std::ifstream::binary);
    in.seekg(0, in.end);
    int length = in.tellg();
    in.seekg(0, in.beg);
    char *buffer = new char[length];
    in.read(buffer, length);
    cout << "length: " << length << endl;
    size_t t1 = time(nullptr);
    sorted_map<uint64_t, float> my_map;
    my_map.init(buffer, size_t(length / 12));
    cout << "size: " << my_map.size() << endl;
    size_t t2 = time(nullptr);
    cout << "time1: " << t2 - t1 << endl;
    /*
    map<uint64_t, float> stl_map;
    stl_map.insert(my_map._data.begin(), my_map._data.end());
    */
    unordered_map<uint64_t, float> uno_map;
    uno_map.insert(my_map._data.begin(), my_map._data.end());
    nark::easy_use_hash_map<uint64_t, float> nak_map;
    for (const auto& abc : my_map) {
        nak_map.insert(abc);
    }
    int i = 0;
    int count = 0;
    for (auto item : my_map._data) {
        bitset<64> abc(item.first);
        cout << i++ << '\t' << abc << '\t' << item.second << endl;
        float value;
        int ret;
        ret = my_map.get(item.first - 2, value);
        cout << "ret:" << ret << ",value:" << value << endl;
        ret = my_map.get(item.first, value);
        cout << "ret:" << ret << ",value:" << value << endl;
        ret = my_map.get(item.first + 1, value);
        cout << "ret:" << ret << ",value:" << value << endl;
        count += 3;
    }
    cout << "count: " << count << endl;
    size_t t3 = time(nullptr);
    cout << "time2: " << t3 - t2 << endl;
    for (auto item: my_map._buckets) {
        cout << item << endl;
    }

    t1 = get_time();
    for (auto& item : my_map._data) {
        auto p = my_map.find(item.first - 1);
        my_map.find(item.first);
        my_map.find(item.first + 4);
    }
    t2 = get_time();
    cout << "time of my map: " << t2 - t1 << endl;

    /*
    t1 = get_time();
    for (auto& item : my_map._data) {
        stl_map.find(item.first - 1);
        stl_map.find(item.first);
        stl_map.find(item.first + 4);
    }
    t2 = get_time();
    cout << "time of stl map: " << t2 - t1 << endl;
    */

    t1 = get_time();
    for (auto& item : my_map._data) {
        uno_map.find(item.first - 1);
        uno_map.find(item.first);
        uno_map.find(item.first + 4);
    }
    t2 = get_time();
    cout << "time of uno map: " << t2 - t1 << endl;

    t1 = get_time();
    for (auto& item : my_map._data) {
        nak_map.find(item.first - 1);
        nak_map.find(item.first);
        nak_map.find(item.first + 4);
    }
    t2 = get_time();
    cout << "time of nak map: " << t2 - t1 << endl;

    return 0;
}
