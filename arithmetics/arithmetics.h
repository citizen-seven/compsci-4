#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>

class Arithmetic {
private:
    unsigned char* digit;
    uint64_t size; //current size
    uint64_t n; //current number of elements
    bool sign;
    void getn();
    Arithmetic abs(const Arithmetic&);
    Arithmetic& add(const Arithmetic&);
    Arithmetic& sub(const Arithmetic&);
    void print_real() const;
public:
    Arithmetic();
    Arithmetic(const char*); 
    Arithmetic(const Arithmetic&);
    Arithmetic(long double);
    ~Arithmetic();
    void print() const;
    bool operator==(const Arithmetic&);
    bool operator>(const Arithmetic&);
    bool operator>=(const Arithmetic&);
    bool operator<(const Arithmetic&);
    bool operator<=(const Arithmetic&);
    Arithmetic& operator=(const Arithmetic&);
    Arithmetic operator+(const Arithmetic&);
    Arithmetic& operator+=(const Arithmetic&);
    Arithmetic& operator-=(const Arithmetic&);
    Arithmetic operator-(const Arithmetic&);
    Arithmetic operator-(long);
    Arithmetic operator*(long);
};
