#include "arithmetics.h"

using namespace std;

void Arithmetic::getn() {
    for (int i = 0; i < size; i++) {
        if ((int)digit[i] != 0)
            n = i+1;
    }
}

Arithmetic::Arithmetic() {
    n = 1;
    size = 16;
    sign = 0;
    digit = new unsigned char[size];
    for (int i = 0; i < size; i++) 
        digit[i] = 0;
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

Arithmetic::Arithmetic(const Arithmetic& a) {
    size = a.size;
    sign = a.sign;
    digit = new unsigned char [size];
    n = a.n;
    memcpy(digit, a.digit, sizeof(unsigned char)*size); 
}

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

Arithmetic::~Arithmetic() {
    delete[] digit;
}

void Arithmetic::print_real() const {
    for (int i = 0; i < size; i++) {
        cout << (int)digit[i] << " ";
    }
    cout << endl;
}

void Arithmetic::print() const {
    int count = 0;
    if (sign) cout << '-';
    for (int i = n; i > 0; i--) {
        if (digit[i-1] || i != n) {
            if (!((int)digit[i-1] / 10) && count)
                cout << '0' << (int)digit[i-1] << ' ';
            else  
                cout << (int)digit[i-1] << ' ';
            count ++;
        } else if (!(int)digit[0] && i == n)
            cout << '0';
    }
    cout << endl;
}

bool Arithmetic::operator==(const Arithmetic& toComp) {
    uint64_t minSize = min(toComp.size, size);
    if (sign != toComp.sign) 
        return 1;
    for (int i = 0; i < minSize; i++) {
        if ((int)toComp.digit[i] != (int)digit[i]) {
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

bool Arithmetic::operator<(const Arithmetic& toComp) {
    uint64_t minSize = min(toComp.size, size);
    if (sign > toComp.sign) //this is negative, toComp is positive
        return 1;
    if (sign < toComp.sign) //this is positive, toComp is negative
        return 0;
    bool ret = 0; //now both have the same sign
    if (*this == toComp)
        return 0;
    for (int i = minSize - 1; i >= 0; i--) {
        if ((int)digit[i] < (int)toComp.digit[i]) {
            ret = 1;
            break;
        } else if ((int)digit[i] > (int)toComp.digit[i]) {
            ret = 0;
            break;
        }
    }
    if (minSize < size)
        for (unsigned long long i = minSize; i < size - 1; i++)
            if ((int)digit[i] != 0) {
                ret = 0;
                break;
            }
    if (minSize < toComp.size)
        for (unsigned long long i = minSize; i < toComp.size - 1; i++)
            if ((int)toComp.digit[i] != 0) {
                ret = 1;
                break;
            }
    return  sign ? !ret : ret;
}

bool Arithmetic::operator>(const Arithmetic& toComp) {
    uint64_t minSize = min(toComp.size, size);
    if (sign > toComp.sign) //this is negative, toComp is positive
        return 0;
    if (sign < toComp.sign) //this is positive, toComp is negative
        return 1;
    bool ret = 0; //now both have the same sign
    if (*this == toComp)
        return 0;
    for (int i = minSize - 1; i >= 0; i--) {
        if ((int)digit[i] > (int)toComp.digit[i]) {
            ret = 1;
            break;
        } else if ((int)digit[i] < (int)toComp.digit[i]) {
            ret = 0;
            break;
        }
    }
    if (minSize < size)
        for (unsigned long long i = minSize; i < size - 1; i++)
            if ((int)digit[i] != 0) {
                ret = 1;
                break;
            }
    if (minSize < toComp.size)
        for (unsigned long long i = minSize; i < toComp.size - 1; i++)
            if ((int)toComp.digit[i] != 0) {
                ret = 0;
                break;
            }
    return  sign ? !ret : ret;
}

bool Arithmetic::operator<=(const Arithmetic& toComp) {
    if (*this == toComp || *this < toComp)
        return 1;
    else return 0;
}

bool Arithmetic::operator>=(const Arithmetic& toComp) {
    if (*this == toComp || *this > toComp)
        return 1;
    return 0;
}

Arithmetic& Arithmetic::operator=(const Arithmetic& a) {
    delete[] digit;
    size = a.size;
    n = a.n;
    sign = a.sign;
    digit = new unsigned char[size];
    for (int i = 0; i < size; i++)
        digit[i] = 0;
    memcpy(digit, a.digit, sizeof(unsigned char)*n); 
    return *this;
}

Arithmetic Arithmetic::abs(const Arithmetic& toAbs) {
    Arithmetic temp = toAbs;
    temp.sign = 0;
    return temp;
}

Arithmetic& Arithmetic::add(const Arithmetic& toSum) {
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

Arithmetic& Arithmetic::sub(const Arithmetic& toSub) { //find the absolute difference
    bool reverse = 0;
    int carry = 0;
    Arithmetic minu, subt;
    if (abs(*this) < abs(toSub)) {
        reverse = 1;
        minu = toSub;
        subt = *this;
    } else {
        minu = *this;
        subt = toSub;
    } 
    for (int i = 0; i < minu.size; i++) {
        if (carry) {
            if ((int)minu.digit[i] >= carry) {
                minu.digit[i] = (int)minu.digit[i] - carry;
                carry = 0;
            } else {
                minu.digit[i] = 100 - carry;
                carry = 1;
            }
            if ((int)minu.digit[i] >= ((i > subt.size - 1) ? 0 : (int)subt.digit[i])) {
                digit[i] = (int)minu.digit[i] - ((i > subt.size - 1) ? 0 : (int)subt.digit[i]);
            } else {
                digit[i] = 100 + minu.digit[i] - carry - ((i > subt.size - 1) ? 0 : subt.digit[i]);
                carry = 1;
            } 
        } else {   
            if ((int)minu.digit[i] >= ((i > subt.size - 1) ? 0 : (int)subt.digit[i])) {
                digit[i] = (int)minu.digit[i] - ((i > subt.size - 1) ? 0 : (int)subt.digit[i]);
            } else {
                carry = 1;
                digit[i] = 100 + (int)minu.digit[i] - ((i > (int)subt.digit[i]) ? 0 : (int)subt.digit[i]);
            } 
        }    
    }
    getn();
    return *this;
}

Arithmetic Arithmetic::operator+(const Arithmetic& toSum) {
    Arithmetic temp = *this;
    temp += toSum;
    return temp;
}

Arithmetic& Arithmetic::operator+=(const Arithmetic& toSum) {
    if (!(sign^toSum.sign))
        add(toSum); //the sign is being preserved implicitly
    else 
        sub(toSum);
    return *this;
}

Arithmetic Arithmetic::operator-(const Arithmetic& toSub) {
    Arithmetic temp = *this;
    temp -= toSub;
    return temp;
}

Arithmetic& Arithmetic::operator-=(const Arithmetic& toSub) {
    if (!(sign^toSub.sign)) {
        sign = !(*this >= toSub);
        sub(toSub); 
    }
    else 
        add(toSub);
    return *this;
}
