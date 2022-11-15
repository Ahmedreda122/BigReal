#include "BigReal.h"

BigReal::BigReal(double realNumber)
{
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
    *this = BigReal(realnSStr.str());
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

  // if there is more than one dot in the input string
  if (count(realNumber.begin(), realNumber.end(), '.') > 1)
  {
    cout << "INVALID INPUT";
    return;
  }
  
  if (realNumber == ".")
  {
    cout << "INVALID INPUT";
    return;
  }

  string sign = "+";

  if (realNumber[0] == '-')
  {
    sign = "-";
    realNumber.erase(0, 1);
  }
  else if (realNumber[0] == '+')
  {
    //Default sign is +
    realNumber.erase(0, 1);
  }
  else if (realNumber[0] == '.')
  {
    realNumber = "0" + realNumber;
  }

  if (realNumber[realNumber.length() - 1] == '.')
  {
    realNumber += "0";
  }

  if (checkValid(realNumber))
  {
    bool streak = true;
    int cursor = 0;
    // Getting dot index in the realNumber, start searching from the first character, returning -1 if not found
    int dotPos = realNumber.find('.');

    //Deleting left zeros from integer part // 000099999.5
    for (int i = 0; i < realNumber.size(); ++i)
    {
      if (realNumber[i] == '0' && streak == true)
      {
        ++cursor;
      }
      else
      {
        streak = false;
        break;
      }
    }

    if (cursor > 0)
    {
      // Erasing zeros from the beginning of the string, "cursor" of times
      realNumber.erase(0, cursor);

      if (realNumber == "")
      {
        realNumber = "0.0";
        dotPos = 1;
      }
      // 0 + .569
      else if (realNumber[0] == '.')
      {
        realNumber = "0" + realNumber;
      }
    }

    streak = true;
    cursor = 0;

    // Deleting right zeros from fraction part 1.5000
    for (int i = realNumber.size() - 1; i >= 0; --i)
    {
      if (realNumber[i] == '0' && streak == true)
      {
        ++cursor;
      }
      else
      {
        streak = false;
        break;
      }
    }

    if (cursor > 0)
    {
      int lastIndex = realNumber.size() - 1;
      // Erasing zeros from lastIndex - cursor + 1, "cursor" of times
      realNumber.erase(((lastIndex + 1) - cursor), cursor);

      if (realNumber[realNumber.size() - 1] == '.')
      {
        realNumber += "0";
      }
    }

    this->fullNum = realNumber;
    // if the dot is not exist in realNumber
    if (dotPos == -1)
    {
      fullNum += ".0";
    }
    // Returning the sign back to fullNum(realNumber)
    fullNum.insert(0, sign);
    
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
  fullNum = move(other.fullNum);
  return *this;
}

BigReal &BigReal::operator=(BigReal &other)
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

  string tmpFullNum = fullNum; // to avoid changing in fullNum (private attribute)
  long long dotIndex1 = tmpFullNum.find(".");
  long long dotIndex2 = other.fullNum.find(".");
  string fracPart1 = tmpFullNum.substr(dotIndex1 + 1);
  string fracPart2 = other.fullNum.substr(dotIndex2 + 1);
  long long tmpDot;
  long long first = fracPart1.size();// to add zeros to fracPart then first++.
  long long second = fracPart2.size();// to add zeros to second fracPart then second++
  long long first1 = fracPart1.size();// to know where dot sign is.
  long long second2 = fracPart2.size();// to know where dot sign is.
  long long bigger = max(first, second);

  if (bigger == first1)// assign tmpDot corosponding to the biggest size in fracPart
  {
    tmpDot = first1;
  }
  else
  {
    tmpDot = second2;
  }

  while (first < bigger)// adding zeros to fracPart
  {
    tmpFullNum += '0';
    first++;
  }
  while (second < bigger)
  {
    other.fullNum += '0';
    second++;
  }

  string target1 = erase_dot(tmpFullNum);
  string target2 = erase_dot(other.fullNum);
  BigDecimalInt firstNum(target1), secondNum(target2), result;
  string finalResult;

  result = firstNum + secondNum; // to use their operator +
  finalResult = result.getNumber(); // note: getNumber() doesnt return the sign
                                    // note: BigDecimalInt result sotres the sign

  if (finalResult == "0")
  {
    finalResult = "0";
    return BigReal(finalResult);
  }
  // adding dot as a reverse order
  reverse(finalResult.begin(), finalResult.end()); // reverse
  finalResult.insert(tmpDot, ".");
  reverse(finalResult.begin(), finalResult.end());// reverse it back;

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

  string tmpFullNum = fullNum; // to avoid changing in fullNum (private attribute)
  long long dotIndex1 = tmpFullNum.find(".");
  long long dotIndex2 = other.fullNum.find(".");
  string fracPart1 = tmpFullNum.substr(dotIndex1 + 1);
  string fracPart2 = other.fullNum.substr(dotIndex2 + 1);
  long long tmpDot;
  long long first = fracPart1.size();// to add zeros to fracPart then first++.
  long long second = fracPart2.size();// to add zeros to second fracPart then second++.
  long long first1 = fracPart1.size();// to know where dot sign is.
  long long second2 = fracPart2.size();// to know where dot sign is.
  long long bigger = max(first, second);

  if (bigger == first1) // assign tmpDot corosponding to the biggest size in fracPart
  {
    tmpDot = first1;
  }
  else
  {
    tmpDot = second2;
  }

  while (first < bigger) // adding zeros to fracPart
  {
    tmpFullNum += '0';
    first++;
  }
  while (second < bigger)
  {
    other.fullNum += '0';
    second++;
  }

  string target1 = erase_dot(tmpFullNum);
  string target2 = erase_dot(other.fullNum);
  BigDecimalInt firstNum(target1), secondNum(target2), result;
  string finalResult;

  result = firstNum - secondNum; // to use their operator - 
  finalResult = result.getNumber(); // note: getNumber() doesnt return the sign
                                    // note: BigDecimalInt result sotres the sign

  if (finalResult == "0")
  {
    finalResult = "0";
    return BigReal(finalResult);
  }

  // adding dot as a reverse order
  reverse(finalResult.begin(), finalResult.end());//reverse
  finalResult.insert(tmpDot, ".");
  reverse(finalResult.begin(), finalResult.end()); // reverse it back;

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
  string dataIn;
  in >> dataIn;
  if (num.checkValid(dataIn))
  {
    num.fullNum = dataIn;
  }
  else
  {
    cout << "Cannot set this value (" << dataIn << ") to BigReal Class" << endl;
  }
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

bool BigReal::operator>(BigReal anotherReal)
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

bool BigReal::checkValid(string realNumber)
{
  regex validStr("[-+]?[0-9]+(.[0-9]+)?");
  return regex_match(realNumber, validStr);
}