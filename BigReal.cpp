#include "BigReal.h"

BigReal::BigReal(double realNumber)
{
  int integerPart{realNumber};
  intPart = move(BigDecimalInt(to_string(integerPart)));

  double fraction{realNumber - integerPart};
  string fractionStr = to_string(fraction); // 0.566 -> 0.566000
  fractionStr.erase(remove(fractionStr.begin(), fractionStr.end(), '0'), fractionStr.end());
  int size = fractionStr.size();

  int  fractionalPart = fraction * pow(10, (size-1));
  //cout << fractionalPart << endl;
  fracPart = move(BigDecimalInt(to_string(fractionalPart)));
  //BigReal(to_string(realNumber));
}

BigReal::BigReal (string realNumber)
{

}