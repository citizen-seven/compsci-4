#include "arithmetics.h"

using namespace std;

Arithmetic::Arithmetic(long double a) { 
    size = 16;
    sign = 0;
    n = (int)ceil(log(a) / log(100));
    digit = new unsigned char [size];
    for (int i = 0; i < size; i++)
        digit[i] = 0;
    if (a < 0) {
        sign = 1;
        a *= -1;
    }
    long int casted = a; //implicit conversion to int
    for (int i = 0; i < n; i++) {
        digit[i] = casted % 100;
        casted /= 100;
    }
}


Arithmetic::Arithmetic() {
    n = 1;
    size = 16;
    sign = 0;
    digit = new unsigned char[size];
    for (int i = 0; i < size; i++) 
        digit[i] = 0;
    PRINT("Constructor")
}


Arithmetic::Arithmetic(const char* s) {
    size = 16;
    sign = 0;
    int len = strlen(s);
    if (s[0] == '-') {
        sign = 1;
        n = (len % 2) ? (len >> 1) : (len >> 1);
    } else 
        n = (len % 2) ? (len >> 1) + 1: len >> 1;
    while (size < n) 
        size *= 2;
    digit = new unsigned char[size];
    for (int i = 0; i < size; i++)
        digit[i] = 0;

    len--;
    for (int i = 0; i < n; i++) {
        digit[i] = s[len--] - '0';
        if (sign && len < 1) break;
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
    Arithmetic temp = *this;
    temp += toSum;
    return temp;
}

Arithmetic& Arithmetic::operator+=(const Arithmetic& toSum) {
    int mem = 0;
    int nUpd = (n > toSum.n) ? n + 1 : toSum.n + 1;
    size = (size > toSum.size) ? size: toSum.size;
    if (nUpd > size) {
        size *= 2;
        unsigned char* temp = new unsigned char[size];
        for (int i = 0; i < size; i++)
            temp[i] = 0;
        memcpy(temp, digit, sizeof(unsigned char)*n);
        delete[] digit;
        digit = temp;
    } 
    for (int i = 0; i < nUpd; i++) {
        int sum = mem;
        if (i < toSum.n)        
            sum += (int)toSum.digit[i];
        if (i < n)
            sum += (int)digit[i];
        mem = 0;
        if (sum < 100) 
            digit[i] = sum;
        else {
            mem = 1;
            digit[i] = sum % 100;
        }
    }   
    n = nUpd;
    return *this;
}

void Arithmetic::print() {
    int count = 0;
    PRINT("len = %d", n)      
    if (sign) cout << '-';
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
    sign = a.sign;
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
    size = a.size;
    n = a.n;
    sign = a.sign;
    digit = new unsigned char[size];
    for (int i = 0; i < size; i++)
        digit[i] = 0;
    PRINT("size = %lu", sizeof(unsigned char)*n)
    memcpy(digit, a.digit, sizeof(unsigned char)*n); 
    return *this;
}

bool Arithmetic::operator==(const Arithmetic& toComp) {
    uint64_t minSize = min(toComp.size, size);
    if (sign != toComp.sign) 
        return 1;
    for (int i = 0; i < minSize; i++) {
        if ((int)toComp.digit[i] != (int)digit[i]) {
            cout << "here\n" << (int)toComp.digit[i] << "and" << (int)digit[i];
            return 0;
        }
    }
    if (minSize < toComp.size) 
        for (unsigned long long i = minSize; i < toComp.size; i++)
            if ((int)toComp.digit[i] != 0)
                return 0;
    if (minSize < size)
        for (unsigned long long i = minSize; i < size; i++)
            if ((int)digit[i] != 0)
                return 0;
    return 1;
}
