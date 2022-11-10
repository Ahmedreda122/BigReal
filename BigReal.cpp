#include "BigReal.h"

BigReal::BigReal(double realNumber)
{
  cout << "<---------Default Constructor--------->" << endl;
  if (realNumber == 0.0)
  {
    BigReal("0.0");
    return;
  }
  else
  {
    /*
    Creating string stream realnSStr:
      Objects of this class use a **string buffer** that contains a sequence of characters.
      This sequence of characters can be accessed directly as a string object, using member str.
      Characters can be inserted and/or extracted from the stream using any operation allowed on output streams like <<, >>.
    */
    stringstream realnSStr;
    // Sending the whole double num (without rounding up or off) to the stream to convert it into string buffer
    realnSStr << setprecision(15) << realNumber;
    // Gets its standard string object (from string stream) and sending it to the string constructor to deal with it
    BigReal(realnSStr.str());
  }

  // ___________________________________________________________________
  // Getting the int part of the realnumber by converting(casting) it to an integer
  // int integerPart{(int) realNumber};

  // intPart = move(BigDecimalInt(to_string(integerPart)));
  // // Getting the fraction part of the realnumber by substracting intpart from the realnumber
  // double fraction {realNumber - integerPart};

  // string fractionStr {to_string(fraction)}; // 0.566 -> 0.566000
  // fractionStr.erase(remove(fractionStr.begin(), fractionStr.end(), '0'), fractionStr.end());
  // int size = fractionStr.size();

  // int  fractionalPart = fraction * pow(10, (size-1));
  // fracPart = move(BigDecimalInt(to_string(fractionalPart)));
}
BigReal::BigReal(BigDecimalInt bigInteger) // sign ????
{
  fullNum = bigInteger.getNumber();
  fullNum += ".0";
}
BigReal::BigReal(string realNumber) : fullNum(realNumber)
{
  // if there is more than one dot in the input string
  if (count(fullNum.begin(), fullNum.end(), '.') > 1)
  {
    cout << "INVALID INPUT";
    // return;
    exit(0);
  }

  // if (other.fullNum[0] >= '0' && other.fullNum[0] <= '9')
  // {
  //   other.fullNum.insert(0, "+");
  // }
  // Getting dot index in the realNumber, start searching from the first character, returning -1 if not found
  int dotPos = realNumber.find('.');

  // if the dot is not exist in realNumber
  if (dotPos == -1)
  {
    fullNum += ".0";
  }
  if (fullNum[0] >= '0' && fullNum[0] <= '9')
  {
    fullNum.insert(0, "+");
  }
  // Make the whole realNumber in Integer part and give the fractional part 0 as a value
  // fullNum = realNumber;
  // }
  // else
  // {
  // // Getting the interger part of the number by substracting it from the beginning(index 0) until the dot (before dotPos index)
  // intPart = BigDecimalInt(realNumber.substr(0, dotPos));
  // intSign = intPart.sign();
  // // Getting the fractional part of the number by substracting it from the the dotPos + 1 (the index after the dot) till the end of the number
  // fracPart = BigDecimalInt(realNumber.substr(dotPos + 1));
  // if (!intSign)
  // {
  //   intPart.setNumber("-" + intPart.getNumber());
  // }
  // else
  //   intPart.setNumber("+" + intPart.getNumber());
  // fullNum = realNumber
}

string erase_dot(string &target)
{
  target.erase(remove(target.begin(), target.end(), '.'), target.end());
  return target;
}

BigReal BigReal ::operator+(BigReal &other)
{

  long long dotIndex1 = fullNum.find(".");
  long long dotIndex2 = other.fullNum.find(".");
  string fracStr1 = fullNum.substr(dotIndex1 + 1);
  string fracStr2 = other.fullNum.substr(dotIndex2 + 1);
  long long first = fracStr1.size();
  long long second = fracStr2.size();
  long long bigger = max(first, second);
  while (first < bigger)
  {
    fullNum += '0';
    first++;
  }
  while (second < bigger)
  {
    other.fullNum += '0';
    second++;
  }

  cout << "1 " << dotIndex1 << '\n';
  cout << "2 " << dotIndex2 << '\n';
  string target1 = erase_dot(fullNum);
  string target2 = erase_dot(other.fullNum);
  cout << target1 << '\n'<< target2 << '\n';
  BigDecimalInt firstNum(target1), secondNum(target2), result;
  string finalResult;
  result = firstNum + secondNum;
  long long size1 = firstNum.size();
  long long size2 = secondNum.size();
  long long maximum = max(size1, size2);
  long long dot;
  if (maximum == size1)
  {
    dot = dotIndex1;
  }
  else
  {
    dot = dotIndex2;
  }
  finalResult = result.getNumber();
  cout << "finalResult: " << finalResult << '\n';
  cout << "SZ1: " << size1 << '\n';
  cout << "SZ2: " << size2 << '\n';
  cout << "(result.size()): " << (result.size()) << '\n';
  if ((result.size()) > maximum) // +1 to count the sign
  {
    finalResult.insert(dot, ".");
  }
  else
  {
    finalResult.insert(--dot, ".");
  }
  fullNum = finalResult;
  if (!result.sign())
  {
    fullNum.insert(0, "-");
  }
  else
  {
    fullNum.insert(0, "+");
  }

  return *this;
}
BigReal BigReal ::operator-(BigReal &other)
{
  long long dotIndex1 = fullNum.find(".");
  long long dotIndex2 = other.fullNum.find(".");
  string fracStr1 = fullNum.substr(dotIndex1 + 1);
  string fracStr2 = other.fullNum.substr(dotIndex2 + 1);
  long long first = fracStr1.size();
  long long second = fracStr2.size();
  long long bigger = max(first, second);
  while (first < bigger)
  {
    fullNum += '0';
    first++;
  }
  while (second < bigger)
  {
    other.fullNum += '0';
    second++;
  }

  cout << "1 " << dotIndex1 << '\n';
  cout << "2 " << dotIndex2 << '\n';

  string target1 = erase_dot(fullNum);
  string target2 = erase_dot(other.fullNum);
  long long size1 = target1.size();
  long long size2 = target2.size();

  cout << target1 << '\n'
       << target2 << '\n';
  BigDecimalInt firstNum(target1), secondNum(target2), result;
  string finalResult;
  result = firstNum - secondNum;

  finalResult = result.getNumber();
  cout << "finalResult: " << finalResult << '\n';
  cout << "SZ1: " << size1 << '\n';
  cout << "SZ2: " << size2 << '\n';

  finalResult.insert(--dotIndex2, ".");

  fullNum = finalResult;
  if (!result.sign())
  {
    fullNum.insert(0, "-");
  }
  else
  {
    fullNum.insert(0, "+");
  }

  return *this;
}
ostream &operator<<(ostream &out, BigReal num)
{

  out << num.fullNum;

  return out;
}
istream &operator>>(istream &out, BigReal &num)
{
  out >> num.fullNum;

  return out;
}
int BigReal::sign()
{
  if (fullNum[0] == '-')
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
int BigReal::size()
{
  return fullNum.size();
}

// BigReal BigReal ::operator-(BigReal &other)
// {
//   BigReal result;
//   BigDecimalInt fnum1 = fracPart, fnum2 = other.fracPart;
//   // string min, res;
//   BigDecimalInt intnum1 = intPart, intnum2 = other.intPart;
//   BigDecimalInt part1, part2;
//   // part1 = fsubtraction(fnum1.getNumber(), fnum2.getNumber());
//   //
//   while (fnum1.size() < fnum2.size())
//   {
//     fnum1.setNumber(fnum1.getNumber() + '0');
//   }
//   while (fnum2.size() < fnum1.size())
//   {
//     fnum2.setNumber(fnum2.getNumber() + '0');
//   }
//   if (intnum1.sign() == intnum2.sign())
//   {
//     part2.setNumber(fsubtraction(fnum1.getNumber(), fnum2.getNumber()));
//     if (caryminus)
//     {
//       BigDecimalInt carry("1");
//       BigDecimalInt finalNum1 = intnum1 - carry;
//       intnum1.setNumber(finalNum1.getNumber());
//     }
//   }
//___________________________________________________________________________
// BigReal::BigReal(BigDecimalInt bigInteger)
// {
//   intPart = bigInteger;
//   fracPart = move(BigDecimalInt("0"));
// }

// BigReal::BigReal(const BigReal &other)
// {
//   cout << "<---------Copy Constructor--------->" << endl;
//   if (this != &other)
//   {
//     this->intPart = other.intPart;
//     this->fracPart = other.fracPart;
//   }
// }

// BigReal &BigReal::operator=(BigReal &other)
// {
//   if (this != &other)
//   {
//     this->intPart = other.intPart;
//     this->fracPart = other.fracPart;
//   }
//   return *this;
// }

// BigReal::BigReal(BigReal &&other)
// {
//   cout << "<---------Move Constructor--------->" << endl;
//   intPart = move(other.intPart);
//   fracPart = move(other.fracPart);
// }

// BigReal &BigReal::operator=(BigReal &&other)
// {
//   cout << "<---------Move Constructor--------->" << endl;
//   intPart = move(other.intPart);
//   fracPart = move(other.fracPart);

//   return *this;
// }

//   part1 = intnum1 - intnum2;

//   cout << part1 << '.' << part2;
//   result.fracPart = part2;
//   result.intPart = part1;
//   return result;
// }
// int BigReal::sign()
// {
//   if (intPart.sign())
//     return 1;
//   else
//     return 0;
// }

// int sign1 = result.sign();

// if (fnum1.size() > fnum2.size())
// {
//   for (long long i = 0; i < fnum1.size() - fnum2.size(); i++)
//   {
//     min += '0';
//   }
//   min += fnum2.getNumber();
//   fnum2 = min;
// }
// else if (fnum1.size() < fnum2.size())
// {
//   for (long long i = 0; i < fnum2.size() - fnum1.size(); i++)
//   {
//     min += '0';
//   }
//   min += fnum1.getNumber();
//   fnum1 = min;
// }

// bool ok = false, is_determined = false;
// if (fnum1 < fnum2)
// {
//   int temp;
//   swap(fnum1, fnum2);
//   // temp = intnum2.size();

//   // intnum1.size() = temp;

//   // swap(intnum1.size(), intnum2.size());
//   ok = true;
// }

// if (intnum1.sign() == intnum2.sign())
// {
//   part1 = fsubtraction(fnum1.getNumber(), fnum2.getNumber());
//   cout << part2 << '.' << part1;
//   cout << '\n';
//   if (!fnum1.size())
//     ok = !ok;
// }
// else
// {
//   part2 = faddition(fnum1.getNumber(), fnum2.getNumber());
//   if (!fnum1.size())
//   {
//     sign1 = 0;
//     is_determined = true;
//   }
//   else
//   {
//     sign1 = 1;
//     is_determined = true;
//   }
// }

// bool right = false;
// for (long long i = 0; i < res.length(); i++)
// {
//   if (res[i] != '-' && res[i] != '0')
//   {
//     right = true;
//   }
//   if (!right && res[i] == '0')
//   {
//     res.erase(i, 1);
//     i--;
//   }
// }

// if (res.empty())
//   res = "0";
// if (!is_determined && (ok))
// {
//   sign1 = 0;
// }
// else if (!is_determined)
// {
//   sign1 = 1;
// }

// result.fracPart.getNumber() = res;

// string faddition(string num1, string num2)
// {
//   auto it1 = num1.rbegin();
//   auto it2 = num2.rbegin();
//   string res;
//   int carry = 0;
//   while (it1 != num1.rend())
//   {
//     int twoDigitsSum;
//     carry = 0;
//     twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
//     if (twoDigitsSum >= 10)
//     {
//       if (it1 == (num1.rend() - 1))
//       {
//         cary = 1;
//       }
//       else
//       {
//         carry = 1;
//       }
//     }
//     res = char((twoDigitsSum % 10) + '0') + res;
//     if (it1 == num1.rend() - 1)
//     {
//       break;
//     }
//     *(it1 + 1) = char((*(it1 + 1) + carry));
//     it1++;
//     it2++;
//   }

//   return res;
// }
// string fsubtraction(string num1, string num2)
// {
//   deque<long long> d;
//   string res;
//   for (long long i = num1.length() - 1; i >= 0; i--)
//   {
//     // "0762.9751"
//     // "5762.9730"
//     // -5000.0021
//     if (num1[i] < num2[i])
//     {
//       // 0.3 - 0.7
//       // (-)0.4
//       if (i == 0)
//       {
//         caryminus = 1;
//       }
//       else
//       {
//         num1[i - 1] = char(num1[i - 1] - 1);
//       }
//       num1[i] = char(num1[i] + 10);
//     }

//     d.push_front((num1[i] - '0') - (num2[i] - '0'));
//   }
//   // 2.3 - 1.7
//   // 0.6
//   for (auto i : d)
//   {
//     res += to_string(i);
//   }
//   return res;
// }
//++
// BigReal result;
//   BigDecimalInt fnum1 = fracPart, fnum2 = other.fracPart;
//   BigDecimalInt intnum1 = intPart, intnum2 = other.intPart;
//   BigDecimalInt part1, part2;

//   while (fnum1.size() < fnum2.size())
//   {
//     fnum1.setNumber(fnum1.getNumber() + '0');
//   }
//   while (fnum2.size() < fnum1.size())
//   {
//     fnum2.setNumber(fnum2.getNumber() + '0');
//   }

//   if (intnum1.sign() == intnum2.sign())
//   {
//     part2 = faddition(fnum1.getNumber(), fnum2.getNumber());
//     if (cary)
//     {
//       BigDecimalInt carry("1");
//       BigDecimalInt finalNum1 = intnum1 + carry;
//       intnum1.setNumber(finalNum1.getNumber());
//     }
//   }
//   else
//   {
//     if (!intnum1.sign())
//     {
//       part2.setNumber(fsubtraction(fnum2.getNumber(), fnum1.getNumber()));
//       if (caryminus)
//       {
//         BigDecimalInt carry("1");
//         BigDecimalInt finalNum1 = intnum1 - carry;
//         intnum1.setNumber(finalNum1.getNumber());
//       }
//     }
//     else
//       part2.setNumber(fsubtraction(fnum1.getNumber(), fnum2.getNumber()));
//     if (caryminus)
//     {
//       BigDecimalInt carry("1");
//       BigDecimalInt finalNum1 = intnum1 - carry;
//       intnum1.setNumber(finalNum1.getNumber());
//     }
//   }

//   part1 = intnum1 + intnum2;

//   cout << part1 << '.' << part2;

//   result.fracPart = part2;
//   result.intPart = part1;

//   return result;