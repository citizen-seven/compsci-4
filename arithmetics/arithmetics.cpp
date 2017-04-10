#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "tools.h"

using namespace std;

class Arithmetic{
    unsigned char* digit;
    int n;
  
public:
    Arithmetic();
    Arithmetic(const char*); 
    ~Arithmetic();
    Arithmetic(const Arithmetic&);
    Arithmetic& operator=(const Arithmetic&);
    Arithmetic& operator=(int n);
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
    n = ( len % 2 )? (len >> 1) + 1: len >> 1;
    digit = new unsigned char[n];
    len--;
    
    for (i = 0; i < n; i++) {
        digit[i] = s[len--] - '0';
        if (len < 0) break;
        digit[i] += (s[len--] - '0') * 10;
   }
};

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
    digit = new unsigned char;
    n = 1;
    digit[0] = a;
    return *this;
};

int main() {
    Arithmetic *a = new Arithmetic();
    Arithmetic b("12359");
    Arithmetic c(b);
    a->print();
    delete a;
    b.print();
    c.print();
    Arithmetic d;
    d = c;
    d.print();
    c = 5;
    c.print();
    return 0;
}