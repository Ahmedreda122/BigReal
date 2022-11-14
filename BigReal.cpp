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
BigReal::BigReal(BigDecimalInt bigInteger) // sign ????
{
  if (bigInteger.sign())
  {
    fullNum = "+" + bigInteger.getNumber();  
  }
  else
  {
    fullNum = "-" + bigInteger.getNumber();
  }
  fullNum += ".0";
}

BigReal::BigReal(string realNumber)
{
  cout << "<---------Default Constructor--------->" << endl;
  // if there is more than one dot in the input string
  if (count(realNumber.begin(), realNumber.end(), '.') > 1)
  {
    cout << "INVALID INPUT";
    return;
  }
  regex validStr("[-+]?[0-9]+(.[0-9]+)?");
  if (regex_match(realNumber, validStr))
  {
    // Getting dot index in the realNumber, start searching from the first character, returning -1 if not found
    int dotPos = realNumber.find('.');

    this->fullNum = realNumber;
    // if the dot is not exist in realNumber
    if (dotPos == -1)
    {
      fullNum += ".0";
    }

    if (fullNum[0] >= '0' && fullNum[0] <= '9' )//isdigit(fullNum[0]))
    {
      fullNum.insert(0, "+");
    }
  }
  else
  {
    cout << "INVALID INPUT";
    return;
  }
}

BigReal::BigReal(const BigReal &other)
{
  cout << "<---------Copy Constructor--------->" << endl;
  if (this != &other)
  {
    fullNum = other.fullNum;
  }
}

BigReal::BigReal(BigReal &&other)
{
  cout << "<---------Move Constructor--------->" << endl;
  fullNum = move(other.fullNum);
}

BigReal &BigReal::operator=(BigReal &&other)
{
  cout << "<---------Move Assigment--------->" << endl;
  fullNum = move(other.fullNum );
  return *this;
}

BigReal& BigReal::operator=(BigReal &other)
{
  if (this != &other)
  {
    this->fullNum = other.fullNum;
  }
  return *this;
}

string erase_dot(string &target)
{
  target.erase(remove(target.begin(), target.end(), '.'), target.end());
  return target;
}

BigReal BigReal::operator+(BigReal other)
{
  string tmpFullNum = fullNum;
  long long dotIndex1 = tmpFullNum.find(".");
  long long dotIndex2 = other.fullNum.find(".");
  string fracPart1 = tmpFullNum.substr(dotIndex1 + 1);
  string fracPart2 = other.fullNum.substr(dotIndex2 + 1);
  long long first = fracPart1.size();
  long long second = fracPart2.size();
  long long bigger = max(first, second);
  while (first < bigger)
  {
    tmpFullNum += '0';
    first++;
  }
  while (second < bigger)
  {
    other.fullNum += '0';
    second++;
  }

  cout << "1 " << dotIndex1 << '\n';
  cout << "2 " << dotIndex2 << '\n';
  string target1 = erase_dot(tmpFullNum);
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
  
  if (!result.sign())
  {
    finalResult.insert(0, "-");
  }
  else
  {
    finalResult.insert(0, "+");
  }
  
  return BigReal(finalResult);
}
BigReal BigReal ::operator-(BigReal other)
{
  string tmpFullNum = fullNum;
  long long dotIndex1 = tmpFullNum.find(".");
  long long dotIndex2 = other.fullNum.find(".");
  string fracPart1 = tmpFullNum.substr(dotIndex1 + 1);
  string fracPart2 = other.fullNum.substr(dotIndex2 + 1);
  long long first = fracPart1.size();
  long long second = fracPart2.size();
  long long bigger = max(first, second);

  while (first < bigger)
  {
    tmpFullNum += '0';
    first++;
  }

  while (second < bigger)
  {
    other.fullNum += '0';
    second++;
  }

  cout << "1 " << dotIndex1 << '\n';
  cout << "2 " << dotIndex2 << '\n';

  string target1 = erase_dot(tmpFullNum);
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


  if (result.sign())
  {
    finalResult.insert(0, "+");
  }
  else
  { 
    finalResult.insert(0, "-");
  }
  
  return BigReal(finalResult);
}

ostream &operator<<(ostream &out, BigReal num)
{

  out << num.fullNum;

  return out;
}

istream &operator>>(istream &in, BigReal &num)
{
  in >> num.fullNum;

  return in;
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

bool BigReal::operator==(BigReal anotherReal)
{
  if (fullNum == anotherReal.fullNum)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool BigReal::operator<(BigReal anotherReal)
{
  int dotPos1 = fullNum.find('.', 0);

  // Getting the interger part of the number by substracting it from the beginning(index 0) until the dot (before dotPos index)  
  BigDecimalInt intPart1 = move(BigDecimalInt(fullNum.substr(0, dotPos1)));

  // Getting the fractional part of the number by substracting it from the the dotPos + 1 (the index after the dot) till the end of the number
  BigDecimalInt fracPart1 = move(BigDecimalInt(fullNum.substr(dotPos1 + 1)));

  int dotPos2 = anotherReal.fullNum.find('.', 0);

  // Getting the interger part of the number by substracting it from the beginning(index 0) until the dot (before dotPos index)  
  BigDecimalInt intPart2 = move(BigDecimalInt(anotherReal.fullNum.substr(0, dotPos2)));

  // Getting the fractional part of the number by substracting it from the the dotPos + 1 (the index after the dot) till the end of the number
  BigDecimalInt fracPart2 = move(BigDecimalInt(anotherReal.fullNum.substr(dotPos2 + 1)));

  // me < another 
  if (intPart1 < intPart2)
  {
    return true;
  }
  // 500.6565 > 300.99999999
  else if (intPart1 > intPart2)
  {
    return false;
  }
  // -500.4 < -500.9
  else if (intPart1 == intPart2 && intPart1.sign() == 0 && intPart2.sign() == 0)
  {
    if (fracPart1 < fracPart2)
    {
      return false;
    }
    else if (fracPart1 > fracPart2)
    {
      return true;
    }
    else // if fracPart1 == fracPart2
    {
      return false;
    }
  }
  // 500.5 < 500.6 
  else if (intPart1 == intPart2 && intPart1.sign() == 1 && intPart2.sign() == 1)
  {
    if (fracPart1 < fracPart2)
    {
      return true;
    }
    else if (fracPart1 > fracPart2)
    {
      return false;
    }
    else // if fracPart1 == fracPart2
    {
      return false;
    }
  }

  return false;
}

bool BigReal::operator> (BigReal anotherReal)
{
  int dotPos1 = fullNum.find('.', 0);

  // Getting the interger part of the number by substracting it from the beginning(index 0) until the dot (before dotPos index)  
  BigDecimalInt intPart1 = move(BigDecimalInt(fullNum.substr(0, dotPos1)));

  // Getting the fractional part of the number by substracting it from the the dotPos + 1 (the index after the dot) till the end of the number
  BigDecimalInt fracPart1 = move(BigDecimalInt(fullNum.substr(dotPos1 + 1)));

  int dotPos2 = anotherReal.fullNum.find('.', 0);

  // Getting the interger part of the number by substracting it from the beginning(index 0) until the dot (before dotPos index)  
  BigDecimalInt intPart2 = move(BigDecimalInt(anotherReal.fullNum.substr(0, dotPos2)));

  // Getting the fractional part of the number by substracting it from the the dotPos + 1 (the index after the dot) till the end of the number
  BigDecimalInt fracPart2 = move(BigDecimalInt(anotherReal.fullNum.substr(dotPos2 + 1)));

  // me > another 
  if (intPart1 < intPart2)
  {
    return false;
  }
  // 500.6565 > 300.99999999
  else if (intPart1 > intPart2)
  {
    return true;
  }
  // -500.9 > -500.4
  else if (intPart1 == intPart2 && intPart1.sign() == 0 && intPart2.sign() == 0)
  {
    if (fracPart1 < fracPart2)
    {
      return true;
    }
    else if (fracPart1 > fracPart2)
    {
      return false;
    }
    else // if fracPart1 == fracPart2
    {
      return false;
    }
  }
  // 500.5 > 500.6 
  else if (intPart1 == intPart2 && intPart1.sign() == 1 && intPart2.sign() == 1)
  {
    if (fracPart1 < fracPart2)
    {
      return false;
    }
    else if (fracPart1 > fracPart2)
    {
      return true;
    }
    else // if fracPart1 == fracPart2
    {
      return false;
    }
  }

  return false;
}







  // // -1.0 < 5 
  // if (fullNum[0] == '-' && anotherReal.fullNum[0] == '+')
  // {
  //   return true;
  // }
  // // 1.0 < -5 
  // else if (fullNum[0] == '+' && anotherReal.fullNum[0] == '-')
  // {
  //   return false;
  // }
  // else if (fullNum[0] == '-' && anotherReal.fullNum[0] == '-')
  // {
  //   if (size() == anotherReal.size())
  //   {
  //     return (fullNum < anotherReal.fullNum);
  //   }
  //   // 1.55555 < 50.0
  //   else if (size() > anotherReal.size())
  //   {
  //     long dotIndex1 =  fullNum.find(".");
  //     long dotIndex2 =  anotherReal.fullNum.find(".");
  //     string intStr1 = fullNum.substr(0 , dotIndex1);
  //     string fracPart1 = fullNum.substr(dotIndex1 + 1);
  //     string intStr2 = anotherReal.fullNum.substr(0, dotIndex2);
  //     string fracPart2 = anotherReal.fullNum.substr(dotIndex2 + 1);
  //   }
  // }
