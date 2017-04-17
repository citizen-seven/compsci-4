#include "Ctime.h"

Ctime::Ctime() {
    hours = 0;
    minutes = 0;
};

void Ctime::print(){
    if (hours / 10) 
        std::cout << hours << ':';
    else 
        std::cout << '0' << hours << ':';
    if (minutes /10)
        std::cout << minutes << std::endl;
    else 
        std::cout << '0' << minutes << std::endl;
};

void Ctime::setTime(int setHours, int setMinutes) {
    if (setMinutes > 59 || setMinutes < 0) {
        std::cout << "Incorrect time!\n \
            Hours should be less than 24, Minutes should be less than 60";
        exit(1);
        }
    minutes = setMinutes;
    hours = setHours;
};

Ctime Ctime::add(Ctime toAdd) {
    Ctime tmp;
    tmp.minutes = (minutes + toAdd.minutes) % 60;
    tmp.hours = (hours + toAdd.hours + (minutes + toAdd.minutes) / 60 ) % 24;
    return tmp;
}

Ctime Ctime::diff(Ctime toDiff) {
    Ctime tmp;
    tmp.minutes = abs((toDiff.hours*60 + toDiff.minutes - minutes - hours*60) % 60);
    tmp.hours = abs(((toDiff.hours*60 + toDiff.minutes - minutes - hours*60) / 60 ) % 24);
    return tmp;
}

int Ctime::isLater(Ctime toCompare) {
    if (toCompare.hours*60 + toCompare.minutes > hours*60 + minutes) 
        return -1;
    else if (toCompare.hours*60 + toCompare.minutes < hours*60 + minutes) 
        return 1;
    else return 0;
}

int main() {
    Ctime time1, time2;
    time1.setTime(12, 20);
    time2.setTime(10, 12);
    time1.print();
    time2.print();
    std::cout << "The difference is: ";
    time1.diff(time2).print();
    if (time2.isLater(time1)) 
        std::cout << "First time is later" << std::endl;
    else 
        std::cout << "Second time is later" << std::endl;
}
