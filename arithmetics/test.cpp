#include "arithmetics.h"

using namespace std;

int main() {
    cout << "Please enter two integers " << endl;
    string input;
    cin >> input;
    Arithmetic custom1(input.c_str());
    cin >> input;
    Arithmetic custom2(input.c_str());
    cout << "Their sum is: ";
    (custom1 + custom1).print(); 

    // Tests
    Arithmetic a("99999999999999999999999999999999");
    Arithmetic b("1234");
    assert(a+b == Arithmetic("100000000000000000000000000001233"));

    Arithmetic testFloat;
    testFloat = 753.381103;
    assert(testFloat == Arithmetic("753"));
    return 0;
}
