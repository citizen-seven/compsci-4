#include <iostream>
#include <cstdlib>
using namespace std;

class Frac{
private:
    signed long long quo, numer;
    int periodStart;
    unsigned long long denom;
    int remIsRepeated(int*);
    void normalize();
public:
    void simplify();
    Frac();
    Frac(int, int, int);
    // Setting a value 
    void setVal(int, int, int);
    // Print a common fraction
    void print();
    // Print a fraction as a decimal with n digits
    void print(int n); 
    // Print a fraction with parameter (* - standart)
    void print(char param); 
    // Redefined + operator for Fraction class
    Frac operator+(const Frac&);
    // Redefined + operator for Fraction class (with int)
    Frac operator+(const int&);
    // Redefined - operator for Fraction class
    Frac operator-(const Frac&); 
    // Redefined - operator for Fraction class (with int)
    Frac operator-(const int&);
    // Redefined ++ operator for Fraction class
    Frac& operator++(int);
    // Redefined -- operator for Fraction class
    Frac& operator--(int);
    // Get the reversed fraction
    Frac& operator!();

};

Frac::Frac(){
    quo = numer = 0;
    denom = 1; 
};

Frac::Frac(int q, int num, int den){
    periodStart = -1;
    quo = q;
    numer = num;
    denom = den;
    if (!denom) denom = 1; 
};

void Frac::normalize() {
    numer += denom*quo;
    quo = 0;
}

void Frac::simplify() {
    if (!numer) denom = 1; 
    if (denom) {
        quo += numer / denom;
        numer = numer % denom;
    }
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
    int remRep = 0;
    if (param == '*') {
        int power = 0;
        while (toCount.numer >= 10*toCount.denom) {
            toCount.denom *= 10;
            power++;
        }
        while (toCount.numer <toCount.denom) {
            toCount.numer *= 10;
            power--;
        }
        int* rem = new int[toCount.denom+1] ();
        int fracToDouble[128];     
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
        for (int i = 0; i < remRep; i++) {
            if (i == periodStart) {
                cout << '(';
            }
            cout << fracToDouble[i];
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

int Frac::remIsRepeated(int* array) {
    int i = 0;
    int last = 1;
    while (array[i] != 0) {
        last = i;
        i++;
    }
    if (!array[0]) return 1;
    //cout << "\n the last is:" << last << endl;
    for (int k = 1; k < last; k++)
        if (array[k] == array[last]) {
            //cout << "the last" << array[last-1] << endl;
            periodStart = k;
            return last;
        }
    return 0;
}

// print(int n) with a parameter - n is a number of digits after a point 
void Frac::print(int n){
    int c = quo * denom + numer;
    int b = denom;
    for(int i = 0; i < n + 1; i++){
        int pr = c / b;
        cout<<pr;
        if (i == 0)
            cout<<'.';
        int next = c % b;
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
    cout << "numer: " << tmp.numer << ", denom: " << tmp.denom << endl;
    tmp.simplify();
    return tmp;
}

Frac Frac::operator+(const int& toAdd) {
    Frac tmp(quo, numer, denom);
    tmp.quo += toAdd;
    return tmp;
}

Frac Frac::operator-(const Frac& toSub) { 
    return *this + Frac(-toSub.quo, -toSub.numer, -toSub.denom);
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

int main(){
    int rem = 0, numer = 0, denom = 1;
    cin >> rem >> numer >> denom;
    Frac a(rem, numer, denom);
    a.print();
    a.print('*');
    cin >> rem >> numer >> denom;
    Frac b(rem, numer, denom);
    b.print();
    b.print('*');
    Frac c;
    c = a + 2;
    c++;
    c--;
    c = c - 2;
    c.print();
    return 0;
}
