#include <iostream>
#include <vector>
#include <map>
#include "rb_tree.hpp"
#include "avl_tree.hpp"
#include "treap.hpp"
#include "map.hpp"
#include "set.hpp"
#include "../common/util.h"
using namespace std;

void test_search_tree() {
    SearchTree<int> search_tree;
}
void test_rb_tree() {
    RbTree<int> int_tree;
    vector<int> p1 = {
        9, 5, 2, 3, 4
    };
    vector<int> p2 = {
        1, 2, 3, 4, 5
    };
    for (auto n : p1) {
        int_tree.insert(n);
    }
    for (auto n : p2) {
        auto it = int_tree.find(n);
        cout << n;
        cout << " : ";
        bool abc = (it == int_tree.end());
        cout << abc;
        cout << endl;
    }
}
void test_map() {
    abc::map<int, int> int_map;
    int_map.emplace(2, 3);
    int_map.emplace(3, 5);
    int p1[] = {
        1, 2, 3, 4
    };
    for (auto n : p1) {
        auto it = int_map.find(n);
        if (it == int_map.end()) {
            cout << "not found " << n << endl;
        }
        else {
            cout << "found " << n << ' ' << it->second << endl;
        }
    }
    abc::map<string, string> str_map;
    str_map.emplace("abc", "hello");
    str_map.emplace("w2", "world");
    string p2[] = {
        "abc", "hello", "w2", "world"
    };
    for (auto n : p2) {
        auto it = str_map.find(n);
        if (it == str_map.end()) {
            cout << "not found " << n << endl;
        }
        else {
            cout << "found " << n << ' ' << it->second << endl;
        }
    }
}

void test_maps() {
    abc::map<int, int>* p_map1 = new abc::map<int, int>;
    std::map<int, int>* p_map2 = new std::map<int, int>;
    int n = 10;
    for (int i = 0; i < n; ++i) {
        p_map1->emplace(i, i + 1);
    }
    // p_map1->print();
    for (auto it = p_map1->begin(); it != p_map1->end(); ++it) {
        cout << "key: " << it->first << ", value: " << it->second << endl;
    }
    n = 20000000;
    auto t1 = util::get_current_time();
    cout << "t1 " << t1 << endl;
    for (int i = 0; i < n; ++i) {
        p_map1->emplace(i, i + 1);
    }
    auto t2 = util::get_current_time();
    cout << "t2 " << t2 << endl;
    cout << "p_map1 emplace time: " << t2 - t1 << endl;
    for (int i = 0; i < n; ++i) {
        p_map2->emplace(i, i + 1);
    }

    int sum1 = 0;
    auto t3 = util::get_current_time();
    cout << "t3 " << t3 << endl;
    cout << "p_map2 emplace time: " << t3 - t2 << endl;
    for (auto it = p_map1->begin(); it != p_map1->end(); ++it) {
        sum1 += it->second;
        sum1 %= 1048923;
    }
    cout << "sum1: " << sum1 << endl;
    auto t4 = util::get_current_time();
    cout << "t4 " << t4 << endl;
    cout << "p_map1 iterator time: " << t4 - t3 << endl;
    int sum2 = 0;
    for (auto it = p_map2->begin(); it != p_map2->end(); ++it) {
        sum2 += it->second;
        sum2 %= 1048923;
    }
    cout << "sum2: " << sum2 << endl;
    auto t5 = util::get_current_time();
    cout << "t5 " << t5 << endl;
    cout << "p_map2 iterator time: " << t5 - t4 << endl;
    for (int i = 0; i < n; ++i) {
        auto it = p_map1->find(i);
        if (it == p_map1->end() || it->second != i + 1) {
            cout << "wrong in p_map1: " << i << endl;
        }
    }
    auto t6 = util::get_current_time();
    cout << "t6 " << t6 << endl;
    cout << "p_map1 find time: " << t6 - t5 << endl;
    for (int i = 0; i < n; ++i) {
        auto it = p_map2->find(i);
        if (it == p_map2->end() || it->second != i + 1) {
            cout << "wrong in p_map2: " << i << endl;
        }
    }
    auto t7 = util::get_current_time();
    cout << "t7 " << t7 << endl;
    cout << "p_map2 find time: " << t7 - t6 << endl;
    delete p_map1;
    auto t8 = util::get_current_time();
    cout << "t8 " << t8 << endl;
    delete p_map2;
    auto t9 = util::get_current_time();
    cout << "t9 " << t9 << endl;
}

int main() {
    test_rb_tree();
    test_map();
    test_maps();
    return 0;
}
