// This file partly originated from the textbook "Data Structures and Algorithm Analysis in C++" 's official website
// https://www.cise.ufl.edu/~sahni/dsaac/
#ifndef currency_
#define currency_

#include <iostream>

using namespace std;

enum class signType { plus,
    minus };

class currency {
public:
    // constructor
    currency(signType theSign = signType::plus,
        unsigned long theDollars = 0,
        unsigned int theCents = 0);
    // destructor
    ~currency() { }
    void setValue(signType, unsigned long, unsigned int);
    void setValue(double);
    signType getSign() const { return sign; }
    unsigned long getDollars() const { return dollars; }
    unsigned int getCents() const { return cents; }
    currency add(const currency&) const;
    currency& increment(const currency&);
    void output() const;

    // below are funcs added as the homework
    void input();
    currency& subtract(const currency& x);
    currency percent(double x);
    currency multiply(double x);
    currency divide(double x);

private:
    signType sign; // sign of object
    unsigned long dollars; // number of dollars
    unsigned int cents; // number of cents
};

#endif
