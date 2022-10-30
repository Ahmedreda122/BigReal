#ifndef BIGREAL_H_
#define BIGREAL_H_

#include "BigDecimalIntClass.h"
#include <cmath>

class BigReal
{
private:
    BigDecimalInt intPart;
    BigDecimalInt fracPart;
public:
    BigReal (double realNumber = 0.0); // Default constructor
    BigReal (string realNumber);
    BigReal (BigDecimalInt bigInteger);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator=(BigReal& other); // Assignment operator
    BigReal& operator=(BigReal&& other); // Move assignment 
};


#endif 