#include "pict.h"

int main() {
    Pict x(4, 5);
    x.getData("file.txt");
    (!x).print();
    return 0;
}
