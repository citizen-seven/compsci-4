#include <string>

class Pict {
    char* pic;
    const int height, width;
public:
    Pict(int, int);
    ~Pict();
    Pict(const Pict&);
    void getData(std::string filename);
    char* operator[](int);
    Pict operator!();
    Pict& operator=(const Pict&);
    bool operator==(const Pict&);
    void print();
    friend std::ostream& operator << (std::ostream& str, Pict& pict);
    std::string dump();
};
