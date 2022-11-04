/*
description: In this problem we developed a new C++ type (class).
that can hold unlimited decimal integer values and performs arithmetic operations on them.
such as: +, -, <, and >.
 */
#include "BigDecimalIntClass.cpp"
#include "BigReal.cpp"

int main() 
{
    double num = 250.5556656;
    BigReal a1(num);
    BigDecimalInt aa("1");
    BigDecimalInt bb("2");
    BigDecimalInt cc = aa - bb;
    cout << cc <<'\n';
    BigReal x("0.3");
    BigReal y("1.7");
    BigReal pls = x + y;
    cout << '\n';
    BigReal min = x - y;
    

//   stringstream realnStr, sstr; 

//   cout << "1.5544519" << endl;
  
//   // Method 1 (the Best)
//   sstr << setprecision(15) << 1.5544519;
//   cout << sstr.str() << endl;
//   /*
//     Method 2:
//     NOTE: to_string function write the fractional part in 6 bits (filling it with zeros if neccessary)
//     250.566 -> 250.566000
//   */
//   cout << to_string(1.5544519) << endl; // Round Up

//   // Method 3: (the best)
//   char str[17];
//   sprintf(str, "%.15f", 1.5544519);
//   cout << str << endl;

//   // Method 4 
//   realnStr << 1.5544519;
//   cout << realnStr.str() << endl; // Round off

//   // Boost method -> thirdparty library
//   // boost::lexical_cast<string>(1.5544519)

// //Output:
// // 1.5544519 // original

// // 1.5544519
// // 1.554452
// // 1.554451900000000
// // 1.55445
// written by me hehe

}



