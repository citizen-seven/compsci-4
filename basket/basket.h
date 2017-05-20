#include <cstdlib>
#include <string>
#include <vector>


#define HOURS_IN_DAY 24
#define WORKER_START 8
#define WORKER_END 17
#define CROW_START 6
#define CROW_END 18
#define BASKET_SIZE 50

class Anybody {
    unsigned apple;
protected:
    static unsigned basket;
public:
    Anybody();
    Anybody(unsigned = 0);
    virtual ~Anybody() {};
    unsigned getApple();
    
    virtual std::string dump() = 0;
    virtual void act() = 0;
    unsigned getBasket() { return basket; };
};

typedef void (Anybody::*Action)();

class Worker: public Anybody {
public:
    Worker(unsigned = 0);
    std::string dump();
    void act();
};

class Crow: public Anybody {
public:
    Crow(unsigned = 0);
    std::string dump();
    void act();
};

class Clock {
    Anybody* entity;
    unsigned freq;
    unsigned begin_hour;
    unsigned end_hour;
    unsigned steps;
    Clock();
public:
    Clock(Anybody* _entity, unsigned _begin_hour,
           unsigned _end_hour, unsigned _freq = 0);
    bool step(Action action, unsigned hour);
    void deleteEntity();
    std::string dump();
    unsigned getBasket() { return entity->getBasket(); };
};

class Clocks {
    std::vector< Clock > clocks;
    unsigned hour;
    Clocks();
    void step(std::ostream&);
    unsigned getBasket() { return clocks.begin() -> getBasket(); };
public:
    Clocks(unsigned workers, unsigned crows);
    ~Clocks();
    void run(std::ostream& );
};
