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
}

BigReal::BigReal(string realNumber)
{
  // if there is more than one dot in the input string
  if (count(realNumber.begin(), realNumber.end(), '.') > 1)
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
  }
}

BigReal::BigReal(BigDecimalInt bigInteger)
{
  intPart = bigInteger;
  fracPart = move(BigDecimalInt("0"));
}

BigReal::BigReal(const BigReal &other)
{
  cout << "<---------Copy Constructor--------->" << endl;
  if (this != &other)
  {
    this->intPart = other.intPart;
    this->fracPart = other.fracPart;
  }
}

BigReal& BigReal::operator=(BigReal &other)
{
  if (this != &other)
  {
    this->intPart = other.intPart;
    this->fracPart = other.fracPart;
  }
  return *this;
}

BigReal::BigReal(BigReal&& other)
{
  cout << "<---------Move Constructor--------->" << endl;
  intPart = move(other.intPart);
  fracPart = move(other.fracPart);
}

BigReal& BigReal::operator=(BigReal&& other)
{
  cout << "<---------Move Constructor--------->" << endl;
  intPart = move(other.intPart);
  fracPart = move(other.fracPart);

  return *this;
}

BigDecimalInt faddition(string num1, string num2)
{
  auto it1 = num1.rbegin();
  auto it2 = num2.rbegin();
  string res;
  int carry = 0;
  while (it1 != num1.rend())
  {
    int twoDigitsSum;
    carry = 0;
    twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
    if (twoDigitsSum >= 10)
    {
      if (it1 == (num1.rend() - 1))
      {
        cary = 1;
      }
      else
      {
        carry = 1;
      }
    }
    res = char((twoDigitsSum % 10) + '0') + res;
    if (it1 == num1.rend() - 1)
    {
      break;
    }
    *(it1 + 1) = char((*(it1 + 1) + carry));
    it1++;
    it2++;
  }

  return res;
}

BigReal BigReal ::operator+(BigReal &other)
{
  BigReal result;
  BigDecimalInt fnum1 = fracPart, fnum2 = other.fracPart;
  BigDecimalInt intnum1 = intPart, intnum2 = other.intPart;
  BigDecimalInt part1, part2;

  part2 = faddition(fnum1.getNumber(), fnum2.getNumber());

  if (cary)
  {
    BigDecimalInt carry("1");
    BigDecimalInt finalNum1 = intnum1 + carry;
    intnum1.setNumber(finalNum1.getNumber());
  }
  part1 = intnum1 + intnum2;

  cout << part1 << '.' << part2;

  result.fracPart = part2;
  result.intPart = part1;

  return result;
}
BigDecimalInt fsubtraction(string num1, string num2)
{
  deque<long long> d;
  string res;
  for (long long i = num1.length() - 1; i >= 0; i--)
  {
    if (num1[i] < num2[i])
    {
      // 0.3 - 0.7
      //(-)0.4
      num1[i] = char(num1[i] + 10);
      if (i == 0)
      {
        caryminus = 1;
      }
      else
      {
        num1[i - 1] = char(num1[i - 1] - 1);
      }
    }
    
    d.push_front((num1[i] - '0') - (num2[i] - '0'));
  }
  // 2.3 - 1.7
  // 0.6
  for (auto i : d)
  {
    res += to_string(i);
  }
  return res;
}

BigReal BigReal ::operator-(BigReal &other)
{
  BigReal result;
  BigDecimalInt fnum1 = fracPart, fnum2 = other.fracPart;
  BigDecimalInt intnum1 = intPart, intnum2 = other.intPart;
  BigDecimalInt part1, part2;
  part1 = fsubtraction(fnum1.getNumber(), fnum2.getNumber());
  cout << part2 << '.' << part1;
  cout << '\n';
  
  if (caryminus)
  {
    BigDecimalInt carry("1");
    BigDecimalInt finalNum1 = intnum1 - carry;
    intnum1.setNumber(finalNum1.getNumber());
  }
  part2 = intnum1 - intnum2;
  result.fracPart = part2;
  result.intPart = part1;
  cout << part2 << '.' << part1;
  return result;
}
