#include "arithmetics.h"

using namespace std;

int main() {
    cout << "Please enter two integers " << endl;
    string input;
    cin >> input;
    Arithmetic custom1(input.c_str());
    cin >> input;
    Arithmetic custom2(input.c_str());
    //custom1.print();
    //custom2.print();
    /*cout << "Their sum is: ";
    custom1 += custom2;
    (custom1).print();*/
    cout << "Their difference is: ";
    (custom1 - custom2).print();

    // Tests
    Arithmetic a("99999999999999999999999999999999");
    Arithmetic b("1234");
    assert(a+b == Arithmetic("100000000000000000000000000001233"));
    assert(a-b == Arithmetic("99999999999999999999999999998765"));

    Arithmetic testDouble;
    testDouble = 753.381103;
    assert(testDouble == Arithmetic("753"));

    a += testDouble;
    assert(a == Arithmetic("100000000000000000000000000000752"));
    
    Arithmetic negative("-482");
    assert(negative == Arithmetic("482"));
    assert(b - negative == Arithmetic("1716"));
    assert(negative - b == Arithmetic("-1716"));

    assert(negative < testDouble);
    assert(b < a);
    assert(a > b);
    assert(testDouble > negative);
    return 0;
}
