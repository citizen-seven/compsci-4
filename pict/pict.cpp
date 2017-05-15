#include "pict.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Pict::Pict(int _height, int _width): height(_height), width(_width){
    assert(width > 0);
    assert(height > 0);
    pic = new char[height*width];
}

Pict::~Pict() {
    delete pic;
}

Pict::Pict(const Pict& pict): height(pict.height), width(pict.width) {
    pic = new char[height*width];
    memcpy(pic, pict.pic, height*width*sizeof(char));
}

char* Pict::operator[](int line) {
    assert(line >= 0);
    assert(line < height);
    return pic + line * width;
}

void Pict::getData(string filename) {
    ifstream input;
    input.open(filename);
    assert(input.is_open());
    for (int i = 0; i < height; i++) {
        input.read((*this)[i], width);
        input.ignore(1, '\n');
    }
}

Pict& Pict::operator = (const Pict& pict) {
    assert(height == pict.height);
    assert(width == pict.width);
    memcpy(pic, pict.pic, height*width*sizeof(char));
    return *this;
}

bool Pict::operator == (const Pict& pict) {
    if ((height != pict.height) || (width != pict.width))
        return false;
    else
        return !memcmp(pic, pict.pic, height*width);
}

void Pict::print() {
    cout << *this;
}

string Pict::dump() {
    ostringstream oss;
    for (int i = 0; i < height; i++) {
        oss.write((*this)[i], width);
        oss << endl;
    }
    return oss.str();
}

ostream& operator << (ostream& stream, Pict& pict) {
    return stream << pict.dump();
}

Pict Pict::operator ! () {
    Pict res(width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            res[j][i] = (*this)[i][j];
        }
    }
    return res;
}
