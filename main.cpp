// FCAI – OOP – 2022 - Assignment 2
// Program: BigReal Class
// Author: Abdallah Hussein Ibrahim Hussein - Ahmad Reda Bayoumi
// IDs: 20210235 - 20210019
// Date: November 2022
// ...........................................................................................

#include "BigDecimalIntClass.cpp"
#include "BigReal.cpp"

int main()
{
    BigReal num1("999.6600");
    BigReal num2("+9999.77");
    BigReal num3(BigReal("400"));

    BigReal input;

    cout << "Enter a BigReal Numer to Test istream:" << '\n';
    cin >> input;
    cout << "Test 1 Accepted\n";

    cout << "Testing ostream: " << input << '\n';
    cout << "Test 2 Accepted\n";

    if (num1.sign())
    {
        cout << "Test 3 Accepted\n";
    }
    if (num2.size() == 8)
    {
        cout << "Test 4 Accepted\n";
    }
    if ((num2.sign()) && (num2.getNum() == "+9999.77"))
    {
        cout << "Test 5 Accepted\n";
    }
    if (BigReal("555.5555") > BigReal("555"))
    {
        cout << "Test 6 Accepted\n";
    }
    if (BigReal("555") < BigReal("555.5555"))
    {
        cout << "Test 7 Accepted\n";
    }
    if (BigReal("500.51") + BigReal("500.51") == BigReal("1001.02"))
    {
        cout << "Test 8 Accepted\n";
    }
    if (BigReal("-500.5") + BigReal("500.5") == BigReal("0.0"))
    {
        cout << "Test 9 Accepted\n";
    }
    if (BigReal("1000.5") - BigReal("1000.5") == BigReal("0"))
    {
        cout << "Test 10 Accepted\n";
    }
    if (BigReal("550.5") - BigReal("500.5") == BigReal("50"))
    {
        cout << "Test 11 Accepted\n";
    }
    if (BigReal("550.5") - BigReal(500.5) == BigReal("50"))
    {
        cout << "Test 12 Accepted\n";
    }

    BigReal("5.5.0.5");
    cout << ", Test 13 Accepted\n";

    if (BigReal("0000999.4") == BigReal("999.4"))
    {
        cout << "Test 14 Accepted\n";
    }

    if (BigReal("00000.0") == BigReal("0"))
    {
        cout << "Test 15 Accepted\n";
    }
    if (BigReal("-500.999") - BigReal("0000550.999") == BigReal("-1051.998"))
    {
        cout << "Test .. Accepted\n";
    }
    if (BigReal("500.9990000") + BigReal("550.999") == BigReal("+1051.9980000"))
    {
        cout << "Test ... Accepted\n";
    } 
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
