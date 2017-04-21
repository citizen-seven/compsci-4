#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include "tools.h"

using namespace std;

class Arithmetic {
    unsigned char* digit;
    int n;
public:
    Arithmetic();
    Arithmetic(const char*); 
    ~Arithmetic();
    Arithmetic(const Arithmetic&);
    Arithmetic& operator=(const Arithmetic&);
    Arithmetic& operator=(int);
    Arithmetic& operator=(float);
	Arithmetic operator+(const Arithmetic&);
	Arithmetic operator+(int);    
    Arithmetic& operator+=(const Arithmetic&);
    Arithmetic operator-(const Arithmetic&);
    Arithmetic operator-(int);
    Arithmetic operator*(int);
    void print();
};


Arithmetic::Arithmetic() {
    n = 1;
    digit = new unsigned char;
    digit[0] = 0;
    PRINT("Constructor")
};

Arithmetic::Arithmetic(const char* s) {
    int i;
    int len = strlen(s);
    n = (len % 2) ? (len >> 1) + 1: len >> 1;
    digit = new unsigned char[n];
    len--;
    
    for (i = 0; i < n; i++) {
        digit[i] = s[len--] - '0';
        if (len < 0) break;
        digit[i] += (s[len--] - '0') * 10;
   }
};


Arithmetic Arithmetic::operator+(const Arithmetic& toSum) {
    Arithmetic temp;
    int mem = 0;
    temp.n = (n > toSum.n) ? n + 1 : toSum.n + 1;
    temp.digit = new unsigned char[temp.n];
    for (int i = 0; i < temp.n; i++) {
        int sum = (int)toSum.digit[i] + (int)digit[i] + mem;
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

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
void Arithmetic::print() {
    int i;
    PRINT("len = %d", n)      
    for (i = n; i > 0; i--) {
        cout << (int)digit[i-1] << ' ';
    }
    cout << endl;
};


Arithmetic::Arithmetic(const Arithmetic& a){
    digit = new unsigned char [a.n];
    n = a.n;
    memcpy(digit,a.digit, sizeof(unsigned char)*n); 
};


Arithmetic::~Arithmetic(){
    delete[] digit;
    PRINT("Destructor")
};


Arithmetic& Arithmetic::operator=(const Arithmetic& a){
    delete[] digit;
    digit = new unsigned char[ a.n ];
    n = a.n;
    PRINT("size = %lu", sizeof(unsigned char)*n)
    memcpy(digit, a.digit, sizeof(unsigned char)*n); 
    return *this;
};


Arithmetic& Arithmetic::operator=(int a){
    delete[] digit;
    n = (int)ceil(log(a)/log(100));
    digit = new unsigned char [n];
    for (int i = 0; i < n; i++) {
        digit[i] = a % 100;
        a /= 100;
    }
    return *this;
};


int main() {
    //Arithmetic *a = new Arithmetic();
    string input;
    cin >> input;
    Arithmetic b(input.c_str());
    cin >> input;
    Arithmetic c(input.c_str());
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
