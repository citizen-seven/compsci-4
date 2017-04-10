#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
using namespace std;

class Frac{
private:
    int64_t quo, numer;
    int64_t periodStart;
    uint64_t denom;
    uint64_t remIsRepeated(uint64_t*);
    void normalize();
public:
    void simplify();
    Frac();
    Frac(int64_t);
    Frac(int64_t, int64_t, uint64_t);
    // Setting a value 
    void setVal(int64_t, int64_t, uint64_t);

    // Print a common fraction
    void print();
    // Print a fraction as a decimal with n digits
    void print(uint64_t n); 
    // Print a fraction with parameter (* - standart)
    void print(char param); 

    // Redefined + operator
    Frac operator+(const Frac&);
    // Redefined ++ operator
    Frac& operator++(); //++Frac
    Frac operator++(int); //Frac++

    // Redefined - operator class
    Frac operator-(const Frac&); 
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

};

Frac::Frac() {
    quo = numer = 0;
    denom = 1; 
};

Frac::Frac(int64_t q) {
    periodStart = -1;
    quo = q;
    numer = 0;
    denom = 1;
}

Frac::Frac(int64_t q, int64_t num, uint64_t den) {
    periodStart = -1;
    if (!den) throw overflow_error("Denumerator can't be zero");
    if ((q < 0) && (num < 0)) num *= -1;
    quo = q;
    numer = num;
    denom = den;
};

void Frac::setVal(int64_t q, int64_t num, uint64_t den) {
    periodStart = -1;
    if (!den) throw overflow_error("Denumerator can't be zero");
    if ((q < 0) && (num < 0)) num *= -1;
    quo = q;
    numer = num;
    denom = den;
};


void Frac::normalize() {
    bool sign = 0;
    if (quo < 0) {
        sign = 1;
        quo *= -1;
    }
    if (numer < 0) {
        sign = 1;
        numer *= -1;
    }
    numer += denom*quo;
    quo = 0; 
    if (sign) numer *= -1; 
}

void Frac::simplify() {
    bool sign = 0;
    normalize();
    if (numer < 0) {
        sign = 1;
        numer *= -1;
    }
    uint64_t n = denom, m = numer, rem = 0;
    while (n) {
        rem = m % n;
        m = n;
        n = rem;
    }
    denom /= m;
    numer /= m;
    quo += numer / denom;
    numer = numer % denom;
    if (sign && !quo) numer *= -1;
    if (sign && quo) quo *= -1; 
}

// "Basic" print()
void Frac::print() {
    simplify();
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
    uint64_t remRep = 0;
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
        uint64_t* rem = new uint64_t[toCount.denom+1] ();
        int64_t fracToDouble[128];     
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
        for (uint64_t i = 0; i < remRep; i++) {
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

uint64_t Frac::remIsRepeated(uint64_t* array) {
    int64_t i = 0;
    int64_t last = 1;
    while (array[i] != 0) {
        last = i;
        i++;
    }
    if (!array[0]) return 1;
    //cout << "\n the last is:" << last << endl;
    for (int64_t k = 1; k < last; k++)
        if (array[k] == array[last]) {
            //cout << "the last" << array[last-1] << endl;
            periodStart = k;
            return last;
        }
    return 0;
}

// print(int n) with a parameter - n is a number of digits after a point 
void Frac::print(uint64_t n){
    int64_t c = quo * denom + numer;
    uint64_t b = denom;
    for(uint64_t i = 0; i < n + 1; i++){
        int64_t pr = c / b;
        cout<<pr;
        if (i == 0)
            cout<<'.';
        int64_t next = c % b;
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

/*Frac Frac::operator+(const int& toAdd) {
    return *this + Frac(0, toAdd, 1);
}*/

Frac Frac::operator-(const Frac& toSub) { 
    Frac tmp(0, 0, 1);
    normalize();
    tmp.numer = (numer * toSub.denom - (toSub.quo * toSub.denom + toSub.numer) * denom);
    tmp.denom = toSub.denom * denom;
    tmp.simplify();
    return tmp;
}

Frac& Frac::operator++() {
    quo += 1;
    return *this;
}

Frac Frac::operator++(int) {
    Frac temp = *this;
    quo += 1;
    return temp;
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
    if (!(toDiv.quo * toDiv.denom + toDiv.numer))
        throw overflow_error("Zero division error");
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

void climb() {
    uint64_t n = 0, k = 0;
    int m = 0;
    cin >> n >> k >> m;
    Frac height(0, 1, 1), currentHeight;
    Frac toClimb, toSlide;
    for (int i = 0; i < m; i++) {
        toClimb = (currentHeight - 1) * (-1) / (n);
        toSlide = (currentHeight - toClimb) / k;
        if (toSlide < 0) toSlide = toSlide * (-1);
        currentHeight = currentHeight + toClimb - toSlide;
        /*cout << "toClimb: "; 
        toClimb.print();
        cout << "toSlide: ";
        toSlide.print();
        cout << "currentHeight: ";
        currentHeight.print();*/
        if (i == m-1) {
            height = !((currentHeight - 1) * (-1));
            cout << "The Mountain height is: ";
            height.print();
        }
     }
} 

int main() {
    //some tests
    int64_t rem = 0, numer = 0;
    uint64_t denom = 1;
    cin >> rem >> numer >> denom;
    Frac a, b;
    try {
        a.setVal(rem, numer, denom);
    } catch (overflow_error e) {
        cout << e.what() << endl;
        exit(1);
    }
    a.print();
    cin >> rem >> numer >> denom;
    try {
        b.setVal(rem, numer, denom);
    } catch (overflow_error e) {
        cout << e.what() << endl;
        exit(1);
    }
    b.print();
    if (a > b) cout << "first is greater" << endl;
    if (a < b) cout << "first is smaller" << endl;
    if (a == b) cout << "fractions are equal" << endl;
    if (a > 2) cout << "first is greater than 2" << endl;
    if (a < 2) cout << "first is smaller than 2" << endl;
    if (a == 2) cout << "first is 2" << endl;
    cout << "Sum is: ";
    (a + 1).print();

    cout << "Differrence is: ";
    (a - b).print();
    
    cout << "Mult is: ";
    (a * b).print();

    try {
        cout << "Div is: ";
        (a / b).print();
    } catch (overflow_error e) {
        cout << e.what() << endl;
        exit(1);
    }
    cout << "++Frac is: ";
    (a++).print();

    cout << "Frac++ is: ";
    (++a).print();

    //Task 3
    //climb(); 
    
    return 0;
}
