#ifndef BIGREAL_H_
#define BIGREAL_H_

#include "BigDecimalIntClass.h"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <iomanip>

int cary = 0;
int caryminus = 0;
bool zerosminus = false;

class BigReal
{
private:
    BigDecimalInt intPart;
    BigDecimalInt fracPart;

public:
    BigReal(double realNumber = 0.0); // Default constructor
    BigReal(string realNumber);
    BigReal(BigDecimalInt bigInteger);
    BigReal(const BigReal &other);       // Copy constructor
    BigReal(BigReal &&other);            // Move constructor
    BigReal &operator=(BigReal &other);  // Assignment operator
    BigReal &operator=(BigReal &&other); // Move assignment
    BigReal operator+(BigReal &other);
    BigReal operator-(BigReal &other);
};

#endif