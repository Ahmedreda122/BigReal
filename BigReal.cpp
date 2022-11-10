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

BigReal::BigReal(string realNumber) : fullNum(realNumber)
{
  cout << "<---------Default Constructor--------->" << endl;
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
  if (fullNum[0] >= '0' && fullNum[0] <= '9' )//isdigit(fullNum[0]))
  {
    fullNum.insert(0, "+");
  }
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
  string fracStr1 = tmpFullNum.substr(dotIndex1 + 1);
  string fracStr2 = other.fullNum.substr(dotIndex2 + 1);
  long long first = fracStr1.size();
  long long second = fracStr2.size();
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
  result = firstNum + secondNum;

  finalResult = result.getNumber();
  cout << "finalResult: " << finalResult << '\n';
  cout << "SZ1: " << size1 << '\n';
  cout << "SZ2: " << size2 << '\n';

  if (size1 > size2)
  {
    finalResult.insert(--dotIndex1, ".");
  }
  else
  {
    finalResult.insert(--dotIndex2, ".");
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
  string fracStr1 = tmpFullNum.substr(dotIndex1 + 1);
  string fracStr2 = other.fullNum.substr(dotIndex2 + 1);
  long long first = fracStr1.size();
  long long second = fracStr2.size();
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

  cout << target1 << '\n'<< target2 << '\n';
  BigDecimalInt firstNum(target1), secondNum(target2), result;
  string finalResult;
  result = firstNum - secondNum;

  finalResult = result.getNumber();
  cout << "finalResult: " << finalResult << '\n';
  cout << "SZ1: " << size1 << '\n';
  cout << "SZ2: " << size2 << '\n';
  if (size1 > size2)
  {
    finalResult.insert(--dotIndex1, ".");
  }
  else
  {
    finalResult.insert(--dotIndex2, ".");
  }
  
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


BigReal::BigReal(const BigReal &other)
{
  cout << "<---------Copy Constructor--------->" << endl;
  if (this != &other)
  {
    fullNum = other.fullNum;
  }
}

BigReal& BigReal::operator=(BigReal &other)
{
  if (this != &other)
  {
    this->fullNum = other.fullNum;
  }
  return *this;
}

BigReal::BigReal(BigReal &&other)
{
  cout << "<---------Move Constructor--------->" << endl;
  fullNum = move(other.fullNum);
}

BigReal &BigReal::operator=(BigReal &&other)
{
  cout << "<---------Move Constructor--------->" << endl;
  fullNum = move(other.fullNum );
  return *this;
}