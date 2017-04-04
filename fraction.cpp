#include <iostream>
#include <cstdlib>
using namespace std;

class Frac{
private:
    signed long long quo, numer;
    signed long long periodStart;
    unsigned long long denom;
    unsigned long long remIsRepeated(unsigned long long*);
    void normalize();
public:
    void simplify();
    Frac();
    Frac(signed long long, signed long long, unsigned long long);
    // Setting a value 
    void setVal(signed long long, signed long long, unsigned long long);

    // Print a common fraction
    void print();
    // Print a fraction as a decimal with n digits
    void print(unsigned long long n); 
    // Print a fraction with parameter (* - standart)
    void print(char param); 

    // Redefined + operator
    Frac operator+(const Frac&);
    // Redefined + operator (with int)
    Frac operator+(const int&);
    // Redefined ++ operator
    Frac& operator++(int);

    // Redefined - operator class
    Frac operator-(const Frac&); 
    // Redefined - operator (with int)
    Frac operator-(const int&);
    // Redefined -- operator
    Frac& operator--(int);
    
    //Redefined * operator
    Frac operator*(const Frac&);
    // Get the reversed fraction
    Frac operator!();
    //Redefined / operator
    Frac operator/(const Frac&);

    //Redefined comparison operators
    int operator>(const Frac&);
    int operator<(const Frac&);
    int operator==(const Frac&);
    int operator>(const signed long long&);
    int operator<(const signed long long&);
    int operator==(const signed long long&);

};

Frac::Frac(){
    quo = numer = 0;
    denom = 1; 
};

Frac::Frac(signed long long q, signed long long num, unsigned long long den){
    periodStart = -1;
    if ((q < 0) && (num < 0)) num *= -1;
    if (numer < 0) {
        q *= -1;
        num *= -1;
    }
    quo = q;
    numer = num;
    denom = den;
    if (!denom) denom = 1; 
};

void Frac::normalize() {
    if ((quo < 0) || (numer < 0)) {
        numer -= denom*quo;
        numer *= -1;
    }
    else numer += denom*quo;
    quo = 0;
}

void Frac::simplify() {
    bool sign = 0;
    if (numer < 0) {
        sign = 1;
        numer *= -1;
    }
    if (!numer) denom = 1; 
    if (denom) {
        quo += numer / denom;
        numer = numer % denom;
    }
    if (sign && !quo) numer *= -1;
    if (sign && quo) quo *= -1; 
}

// "Basic" print()
void Frac::print() {
    this->simplify();
    if (quo == 0) {
        if (denom == 1)
            cout << numer << endl;
        else if (numer != 0)
            cout << numer << '/' << denom << endl;
    } else { 
        if (denom == 1)
            cout << quo << endl;
        else if (numer != 0)
            cout << quo << " (" << numer << '/' << denom << ')' << endl;
    }
};

void Frac::print(const char param) {
    Frac toCount = Frac(quo, numer, denom);
    toCount.normalize();
    unsigned long long remRep = 0;
    bool sign = 0; //0 if positive, 1 is negative
    if (param == '*') {
        if (toCount.numer < 0) {
            sign = 1;
            toCount.numer *= -1;
        }
        int power = 0;
        while (toCount.numer >= 10*toCount.denom) {
            toCount.denom *= 10;
            power++;
        }
        while (toCount.numer < toCount.denom) {
            toCount.numer *= 10;
            power--;
        }
        unsigned long long* rem = new unsigned long long[toCount.denom+1] ();
        signed long long fracToDouble[128];     
        //cout << "numer" <<toCount.numer;
        if (toCount.denom > 0) {
            int i = 0;
            do {
                if (!(toCount.numer / toCount.denom)) 
                    toCount.numer *= 10;
                fracToDouble[i] = toCount.numer / toCount.denom;
                toCount.numer %= toCount.denom;
                rem[i] = toCount.numer;
                remRep = remIsRepeated(rem);
                if (!rem[i]) remRep = i+1;
                i++;
            //cout << "clause:" << remIsRepeated(rem) <<endl;
            } while (!remRep);
        }
        for (unsigned long long i = 0; i < remRep; i++) {
            if (i == periodStart) {
                cout << '(';
            }
            if (sign && !i) cout << '-' << fracToDouble[i];
            else  cout << fracToDouble[i];
            if (i == 0) 
                cout << '.';
        }
        if (periodStart >= 0) 
            cout << ')';
        cout << 'x' << 10 << '^' << power; //the quotient had been transformed to a proper form
        cout << endl;    
        delete[] rem;
    } else 
        this->print();
}

unsigned long long Frac::remIsRepeated(unsigned long long* array) {
    signed long long i = 0;
    signed long long last = 1;
    while (array[i] != 0) {
        last = i;
        i++;
    }
    if (!array[0]) return 1;
    //cout << "\n the last is:" << last << endl;
    for (signed long long k = 1; k < last; k++)
        if (array[k] == array[last]) {
            //cout << "the last" << array[last-1] << endl;
            periodStart = k;
            return last;
        }
    return 0;
}

// print(int n) with a parameter - n is a number of digits after a point 
void Frac::print(unsigned long long n){
    signed long long c = quo * denom + numer;
    unsigned long long b = denom;
    for(unsigned long long i = 0; i < n + 1; i++){
        signed long long pr = c / b;
        cout<<pr;
        if (i == 0)
            cout<<'.';
        signed long long next = c % b;
        next *= 10;
        while(next < b){
            next *= 10;
            i++;
            if (next >= b || i>=n) break;
            cout<<'0'; 
        }
        c = next;
    }
    cout<<endl;
};  

Frac Frac::operator+(const Frac& toAdd) {
    Frac tmp;
    normalize();
    tmp.numer = (toAdd.quo * toAdd.denom + toAdd.numer) * denom + numer * toAdd.denom;
    tmp.denom = toAdd.denom * denom;
    //cout << "numer: " << tmp.numer << ", denom: " << tmp.denom << endl;
    tmp.simplify();
    return tmp;
}

Frac Frac::operator+(const int& toAdd) {
    Frac tmp(quo, numer, denom);
    tmp.quo += toAdd;
    return tmp;
}

Frac Frac::operator-(const Frac& toSub) { 
    Frac tmp;
    normalize();
    tmp.numer = (numer * toSub.denom - (toSub.quo * toSub.denom + toSub.numer) * denom);
    tmp.denom = toSub.denom * denom;
    tmp.simplify();
    return tmp;
}

Frac Frac::operator-(const int& toAdd) {
    Frac tmp(quo, numer, denom);
    tmp.quo -= toAdd;
    return tmp;
}

Frac& Frac::operator++(const int iter) {
    quo += 1;
    return *this;
}

Frac& Frac::operator--(const int iter) {
    quo -= 1;
    return *this;
}

Frac Frac::operator*(const Frac& toMul) {
    Frac tmp(0, (toMul.quo * toMul.denom + toMul.numer) * (quo * denom + numer), denom * toMul.denom);
    tmp.simplify();
    return tmp;
}

Frac Frac::operator/(const Frac& toDiv) {
    Frac tmp(0, (quo * denom + numer) * toDiv.denom, (toDiv.quo * toDiv.denom + toDiv.numer) * denom);
    tmp.simplify();
    return tmp;
}

Frac Frac::operator!() {
    normalize();
    Frac tmp(0, denom, numer);
    simplify();
    tmp.simplify();
    return tmp;
}

int Frac::operator<(const Frac& toComp) {
    return (quo + (long double)numer / (long double)denom < toComp.quo +
            (long double)toComp.numer / (long double)toComp.denom);
}

int Frac::operator>(const Frac& toComp) {
    return (quo + (long double)numer / (long double)denom > toComp.quo +
            (long double)toComp.numer / (long double)toComp.denom);
}

int Frac::operator==(const Frac& toComp) {
    return (quo + (long double)numer / (long double)denom == toComp.quo +
            (long double)toComp.numer / (long double)toComp.denom);
}

int Frac::operator<(const signed long long& toComp) {
    return (quo + (long double)numer / (long double)denom < toComp);
}

int Frac::operator>(const signed long long& toComp) {
    return (quo + (long double)numer / (long double)denom > toComp);
}

int Frac::operator==(const signed long long& toComp) {
    return (quo + (long double)numer / (long double)denom == toComp);
}

int main() {
    int rem = 0, numer = 0, denom = 1;
    cin >> rem >> numer >> denom;
    Frac a(rem, numer, denom);
    a.print();
    a.print('*');
    cin >> rem >> numer >> denom;
    Frac b(rem, numer, denom);
    b.print();
    b.print('*');
    if (a > b) cout << "more" << endl;
    if (a < b) cout << "less" << endl;
    if (a == b) cout << "equal" << endl;
    if (a > 2) cout << "more" << endl;
    if (a < 2) cout << "less" << endl;
    if (a == 2) cout << "equal" << endl;
    //Frac c;
    //c = !a;
    //c.print();
    return 0;
}
