#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include "tools.h"
#include <cassert>

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
    bool operator==(const Arithmetic&);
    void print();
};
