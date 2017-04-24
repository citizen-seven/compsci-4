#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include "tools.h"

using namespace std;

class Arithmetic {
private:
    unsigned char* digit;
    unsigned long long size; //current size
    unsigned long long n; //current number of elements
public:
    Arithmetic();
    Arithmetic(const char*); 
    Arithmetic(const Arithmetic&);
    Arithmetic(long double);
    ~Arithmetic();
    Arithmetic& operator=(const Arithmetic&);
    Arithmetic operator+(const Arithmetic&);
    Arithmetic operator+(long);    
    Arithmetic& operator+=(const Arithmetic&);
    Arithmetic operator-(const Arithmetic&);
    Arithmetic operator-(long);
    Arithmetic operator*(long);
    void print();
};


Arithmetic::Arithmetic(long double a) { 
    size = 16;
    n = (int)ceil(log(a) / log(100));
    digit = new unsigned char [size];
    long int casted = a; //implicit conversion to int
    for (int i = 0; i < n; i++) {
        digit[i] = casted % 100;
        casted /= 100;
    }
}


Arithmetic::Arithmetic() {
    n = 1;
    size = 16;
    digit = new unsigned char[size];
    for (int i = 0; i < size; i++) 
        digit[i] = 0;
    PRINT("Constructor")
}


Arithmetic::Arithmetic(const char* s) {
    size = 16;
    int len = strlen(s);
    n = (len % 2) ? (len >> 1) + 1: len >> 1;
    while (size < n) 
        size *= 2;
    digit = new unsigned char[size];
    for (int i = 0; i < size; i++)
        digit[i] = 0;
    len--;
    for (int i = 0; i < n; i++) {
        digit[i] = s[len--] - '0';
        if (len < 0) break;
        digit[i] += (s[len--] - '0') * 10;
   }
}

/*
unsigned char* temp = new unsigned char[size];
memcpy(temp, digit, sizeof(unsigned char)*n); 
delete[] digit;
digit = temp;
*/

Arithmetic Arithmetic::operator+(const Arithmetic& toSum) {
    Arithmetic temp;
    int mem = 0;
    temp.n = (n > toSum.n) ? n + 1 : toSum.n + 1;
    temp.size = (size > toSum.size) ? size: toSum.size;
    if (temp.n > temp.size)
        temp.size *= 2;
    temp.digit = new unsigned char[temp.size];
    for (int i = 0; i < temp.size; i++)
        temp.digit[i] = 0;
    for (int i = 0; i < temp.n; i++) {
        int sum = mem;
        if (i < toSum.n)        
            sum += (int)toSum.digit[i];
        if (i < n)
            sum += (int)digit[i];
        mem = 0;
        if (sum < 100) 
            temp.digit[i] = sum;
        else {
            mem = 1;
            temp.digit[i] = sum % 100;
        }
    }   
    return temp;
}


void Arithmetic::print() {
    int count = 0;
    PRINT("len = %d", n)      
    for (int i = n; i > 0; i--) {
        if (digit[i-1] || i != n) {
            if (!((int)digit[i-1] / 10) && count)
                cout << '0' << (int)digit[i-1] << ' ';
            else  
                cout << (int)digit[i-1] << ' ';
            count ++;
        }
    }
    cout << endl;
}


Arithmetic::Arithmetic(const Arithmetic& a) {
    size = a.size;
    digit = new unsigned char [size];
    n = a.n;
    memcpy(digit, a.digit, sizeof(unsigned char)*size); 
}


Arithmetic::~Arithmetic() {
    delete[] digit;
    PRINT("Destructor")
}


Arithmetic& Arithmetic::operator=(const Arithmetic& a) {
    delete[] digit;
    digit = new unsigned char[ a.n ];
    n = a.n;
    PRINT("size = %lu", sizeof(unsigned char)*n)
    memcpy(digit, a.digit, sizeof(unsigned char)*n); 
    return *this;
}


int main() {
    //Arithmetic *a = new Arithmetic();
    string input;
    cin >> input;
    Arithmetic b(input.c_str());
    cin >> input;
    Arithmetic c(input.c_str());
    Arithmetic test(b);
    //test = b;
    test.print();
    test = 753.198;
    test.print();
    (b + c).print();
    /*Arithmetic c(b);
    a->print();
    delete a;
    b.print();
    c.print();
    Arithmetic d;
    d = c;
    d.print();
    c = 21124;
    c.print();*/
    return 0;
}
