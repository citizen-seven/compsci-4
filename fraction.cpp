#include <iostream>
#include <cstdlib>
using namespace std;

class Frac{
private:
    signed long long quo, numer;
    int isPeriodic;
    unsigned long long denom;
    void simplify();
    int remIsRepeated(int*);
    void normalize();
public:
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
};
Frac::Frac(){
    quo = numer = 0;
    denom = 1; 
};
Frac::Frac(int q, int num, int den){
    isPeriodic = -1;
    quo = q;
    numer = num;
    denom = den;
};

void Frac::normalize() {
    numer += denom*quo;
    quo = 0;
}

void Frac::simplify() {
    if (denom != 0) {
        quo += numer/denom;
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
    normalize();
    if (param == '*') {
        int power = 0;
        while (numer >= 10*denom) {
            denom *= 10;
            power++;
        }
        while (numer < denom) {
            numer *= 10;
            power--;
        }
        int* rem = new int[denom] ();
        int fracToDouble[128];     
        if (denom > 0) {
            int i = 0;
            do {
                if (!(numer / denom)) 
                    numer *= 10;
                fracToDouble[i] = numer / denom;
                cout << "we've written" << fracToDouble[i] << endl;
                numer %= denom;
                rem[i] = numer;
                cout << "we've written" << rem[i] << endl;
                i++;
            cout << "clause:" << remIsRepeated(rem) <<endl;
            } while (!remIsRepeated(rem));
        }
        for (int i = 0; i < remIsRepeated(rem); i++) {
            if (i == isPeriodic) {
                cout << '(';
            }
            cout << fracToDouble[i];
            if (i == 0) 
                cout << '.';
        }
        if (isPeriodic >= 0) 
            cout << ')';
        cout << 'x' << 10 << '^' << power; //the quotient had been transformed to a proper form
        cout << endl;    
        delete[] rem;
    } else 
        this->print();
}

int Frac::remIsRepeated(int* array) {
    int i = 0;
    int last;
    while (array[i] != 0) {
            last = i;
            i++;
        }
    //cout << "\n the last is:" << last << endl;
    for (int i = 1; i < last; i++)
        if (array[i] == array[last]) {
            //cout << "the last" << array[last-1] << endl;
            isPeriodic = i;
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

int main(){
    Frac b(0,2,3);
    b.print();
    b.print('*');
    return 0;
}
