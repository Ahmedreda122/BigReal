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
    char sign{};

public:
    BigReal(double realNumber = 0.0); // Default constructor
    BigReal(string realNumber);
    BigReal(BigDecimalInt bigInteger);
    //    BigReal(const BigReal &other);       // Copy constructor
    //    BigReal(BigReal &&other);            // Move constructor
    //    BigReal &operator=(BigReal &other);  // Assignment operator
    //    BigReal &operator=(BigReal &&other); // Move assignment

    BigReal(const BigReal &other);       // Copy constructor
    BigReal(BigReal &&other);            // Move constructor
    BigReal& operator=(BigReal &other);  // Assignment operator
    BigReal& operator=(BigReal &&other); // Move assignment

    BigReal operator+(BigReal &other);
    //    BigReal operator-(BigReal &other);
    //    int sign();
    string getNum()
    {
        return fullNum;
    }
};

#endif