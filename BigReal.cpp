#include "BigReal.h"

BigReal::BigReal(double realNumber)
{  
  /*
    NOTE: to_string function write the fractional part in 6 bits (filling it with zeros if neccessary)
    250.566 -> 250.566000
  */
  if (realNumber == 0.0)
  {
    BigReal("0.0");
    return;
  } 
  // else
  // {
  //   /*
  //   Creating string stream realnStr:
  //     Objects of this class use a **string buffer** that contains a sequence of characters.
  //     This sequence of characters can be accessed directly as a string object, using member str.
  //     Characters can be inserted and/or extracted from the stream using any operation allowed on output streams like <<, >>.
  //   */
  //   stringstream realnStr; 
  //   // Sending the double num to the stream to convert it into string
  //   realnStr << realNumber;
  //   // Gets its standard string object (from string stream) and sending it to the overloaded constructor to deal with it 
  //   BigReal(realnStr.str());
  // }

// ___________________________________________________________________
  int integerPart{(int) realNumber};
  intPart = move(BigDecimalInt(to_string(integerPart)));

  double fraction {realNumber - integerPart};
  string fractionStr {to_string(fraction)}; // 0.566 -> 0.566000
  fractionStr.erase(remove(fractionStr.begin(), fractionStr.end(), '0'), fractionStr.end());
  int size = fractionStr.size();
  

  int  fractionalPart = fraction * pow(10, (size-1));
  fracPart = move(BigDecimalInt(to_string(fractionalPart)));
 
}

BigReal::BigReal (string realNumber)
{
  // if there is more than one dot in the input string
  if (count (realNumber.begin(), realNumber.end(), '.') > 1)
  {
    cout << "INVALID INPUT";
    return;
  }

  // Getting dot index in the realNumber, start searching from the first character, returning -1 if not found
  int dotPos = realNumber.find('.', 0);

  // if the dot is not exist in realNumber
  if (dotPos == -1)
  {
    // Make the whole realNumber in Integer part and give the fractional part 0 as a value
    intPart = move(BigDecimalInt(realNumber));
    fracPart = move(BigDecimalInt("0"));
  }
  else
  {
    // Getting the interger part of the number by substracting it from the beginning(index 0) until the dot (before dotPos index)  
    intPart = move(BigDecimalInt(realNumber.substr(0, dotPos)));

    // Getting the fractional part of the number by substracting it from the the dotPos + 1 (the index after the dot) till the end of the number
    fracPart = move(BigDecimalInt(realNumber.substr(dotPos + 1)));

    cout << fracPart;
  }                     
}