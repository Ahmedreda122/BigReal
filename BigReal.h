#ifndef BIGREAL_H_
#define BIGREAL_H_

#include "BigDecimalIntClass.h"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <iomanip>

class BigReal
{
private:
    string fullNum;
public:
    BigReal(double realNumber = 0.0); // Default constructor
    BigReal(string realNumber);
    BigReal(BigDecimalInt bigInteger);
    BigReal(const BigReal &other);       // Copy constructor
    BigReal(BigReal &&other);            // Move constructor
    BigReal& operator=(BigReal &other);  // Assignment operator
    BigReal& operator=(BigReal &&other); // Move assignment
    BigReal operator+(BigReal other);
    BigReal operator-(BigReal other);
    bool operator< (BigReal anotherReal);  
    bool operator> (BigReal anotherReal); 
    bool operator== (BigReal anotherReal); 
    int sign();
    int size();
    string getNum() {return fullNum;}  
    friend ostream &operator<<(ostream &out, BigReal num);
    friend istream &operator>>(istream &out, BigReal &num);
};

#endif