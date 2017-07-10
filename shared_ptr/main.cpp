#include <iostream>
#include "shared_ptr.hpp"
using namespace std;

void test1() {
    cout << "========================test1=====================\n";
    abc::shared_ptr<int> xx0 = new int();
    xx0 = new int();
    abc::shared_ptr<int> xx1(new int());
    abc::shared_ptr<int> xx2(nullptr);
    cout << "count2:" << xx2.shared_count() << endl;
    cout << "equal2nullptr: " << (xx2 == nullptr) << endl;
    cout << "equalnullptr2: " << (nullptr == xx2) << endl;
    cout << "noequal2nullptr: " << (xx2 != nullptr) << endl;
    /*
    cout << "equal2NULL: " << (xx2 == NULL) << endl;
    cout << "noequal2NULL: " << (xx2 != NULL) << endl;
    */
    cout << *xx1 << endl;
    *xx1 = 3;
    cout << *xx1 << endl;
    cout << "count2:" << xx2.shared_count() << endl;
    abc::shared_ptr<int> xx3 = xx1;
    cout << "equal13: " << (xx3 == xx1) << endl;
    cout << "noequal13: " << (xx3 != xx1) << endl;
    cout << "count2:" << xx2.shared_count() << endl;
    cout << "count3:" << xx3.shared_count() << endl;
    xx3 = nullptr;
    cout << "count3:" << xx3.shared_count() << endl;
    xx2 = nullptr;
    cout << "count2:" << xx2.shared_count() << endl;
    xx1 = nullptr;
    cout << "count1:" << xx1.shared_count() << endl;
}

void test2() {
    cout << "========================test2=====================\n";
    abc::shared_ptr<int> xx0(new int(0));
    abc::shared_ptr<const int> xx1(new int(1));
    // *xx1 = 0;
    const abc::shared_ptr<int> xx2(new int(2));
    *xx2 = 0;
    // xx2 = xx1;
    // const abc::shared_ptr<int> xx3 = xx1;
    const abc::shared_ptr<int> xx3 = xx0;
    *xx3 = 4;

}

// this will cause core dump
void test3() {
    cout << "========================test3=====================\n";
    int n = 1;
    abc::shared_ptr<int> xx2(&n);
}

void test4() {
    cout << "========================test4=====================\n";
    int *p = new int();
    abc::shared_ptr<int> xx(p);
}

int xy_n = 0;
class xy {
public:
    xy() {
        n = xy_n++;
        cout << "construct of xy " << n << endl;
        p = new int();
    }
    ~xy() {
        cout << "disctruct of xy " << n << endl;
        delete p;
    }
    int n;
    int data;
    int *p;
};

// this does not cause core dump, like std::shared_ptr, but I don't know why!"
void test5() {
    cout << "========================test5=====================\n";
    xy *p = new xy();
    abc::shared_ptr<xy> xx1(p);
    abc::shared_ptr<xy> xx2(p);
    delete p;
    delete p;
    delete p;
}

// this will cause core dump, like std::shared_ptr
void test6() {
    cout << "========================test6=====================\n";
    xy *p = new xy[1];
    abc::shared_ptr<xy> xx1(p);
    abc::shared_ptr<xy> xx2(p);
}

void test7() {
    cout << "========================test7=====================\n";
    abc::shared_ptr<int> x = new int();
    cout << "-------------\n";
    x = new int();
    cout << "-------------\n";
}

int main() {
    test1();
    test2();
    test4();
    test5();
    test7();
    return 0;
}
