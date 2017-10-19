#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include "hash_table.hpp"
#include "../common/util.h"
using namespace std;


void test_hash_table() {
    HashTable<int, int> hash_table;
    hash_table.set(3, 5);
    hash_table.set(2, 6);
    hash_table.set(4, 7);
    hash_table.set(3, 8);
    int val = 30, ret;
    ret = hash_table.get(2, val);
    cout << val << endl;
    ret = hash_table.get(3, val);
    cout << val << endl;
}
void test_2() {
    HashTable<int, int> hash_table;
    for (int i = 0; i < 100; ++i) {
        hash_table.set(i, i * i + 10000);
    }
    int val;
    for (int i = 0; i < 100; ++i) {
        hash_table.get(i, val);
        cout << "(" << i << "," << val << ")\n";
    }
}
void test_3() {
    int n = 10000000;
    HashTable<int, int> hash_table;
    unordered_map<int, int> std_hash_table;
    time_t t1 = time(nullptr);
    for (int i = 0; i < n; ++i) {
        hash_table.set(i, i * i + 10000);
    }
    time_t t2 = time(nullptr);
    cout << "hash_table set time: " << t2 - t1 << endl;
    for (int i = 0; i < n; ++i) {
        std_hash_table.emplace(i, i * i + 10000);
    }
    time_t t3 = time(nullptr);
    cout << "std_hash_table set time: " << t3 - t2 << endl;
    int val1, val2;
    for (int i = 0; i < n; ++i) {
        hash_table.get(i, val1);
        val2 = std_hash_table[i];
        if (val1 != val2) {
            cout << "i " << ',' << val1 << ',' << val2 << endl;
            break;
        }
    }
    time_t t4 = time(nullptr);
    for (int i = 0; i < n; ++i) {
        hash_table.get(i, val1);
    }
    time_t t5 = time(nullptr);
    cout << "hash_table get time: " << t5 - t4 << endl;
    for (int i = 0; i < n; ++i) {
        val2 = std_hash_table[i];
    }
    time_t t6 = time(nullptr);
    cout << "std_hash_table get time: " << t6 - t5 << endl;
}

int main() {
    test_hash_table();
    test_2();
    test_3();
    return 0;
}
