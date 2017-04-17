#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>

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
    void print(int64_t);

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
    bool operator>(const Frac&);
    bool operator>=(const Frac&);
    bool operator<(const Frac&);
    bool operator<=(const Frac&);
    bool operator==(const Frac&);
    bool operator!=(const Frac&);

};

