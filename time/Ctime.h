#include <iostream>
#include <cstdlib>
#include <cmath>

class Ctime {
private:
    int hours;
    int minutes;
public:
    Ctime();
    void setTime(int, int); 
    void print();
    Ctime add(Ctime);
    Ctime diff(Ctime);
    int isLater(Ctime);
};

