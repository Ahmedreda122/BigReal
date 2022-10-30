/*
description: In this problem we developed a new C++ type (class).
that can hold unlimited decimal integer values and performs arithmetic operations on them.
such as: +, -, <, and >.
 */

#ifndef BIGDECIMALINT_BIGDECIMALINTCLASS_H
#define BIGDECIMALINT_BIGDECIMALINTCLASS_H

#include <iostream>
#include <deque>
#include <regex>
#include <string>

using namespace std;

class BigDecimalInt{
private:
    string number;
    char signNumber;
    bool checkValidInput(string input);

public:
    bool operator < (const BigDecimalInt& anotherDec);
    bool operator > (const BigDecimalInt& anotherDec);
    bool operator == (const BigDecimalInt anotherDec);
    BigDecimalInt& operator = (BigDecimalInt anotherDec);
    BigDecimalInt operator + (BigDecimalInt number2);
    BigDecimalInt operator - (BigDecimalInt anotherDec);
    friend ostream &operator << (ostream &out, BigDecimalInt num);
    int size();
    int sign();
    void setNumber(string num);
    string getNumber(){
        return number;
    }

    BigDecimalInt(){}
    BigDecimalInt(string num)
    {
        setNumber(num);
    }
    

};

#endif //BIGDECIMALINT_BIGDECIMALINTCLASS_H
