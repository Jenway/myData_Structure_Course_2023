#include "Currency.h"

using namespace std;
// below are implenmentation of the funcs added as the homework

void currency::input()
{
    char signChar;
    string str;
    cin >> signChar >> str;
    this->sign = (signChar == '-') ? signType::minus : signType::plus;
    int dotPos = str.find('.');
    this->dollars = stoul(str.substr(0, dotPos));
    this->cents = stoul(str.substr(dotPos + 1));
}

currency& currency::subtract(const currency& x)
{

    long a1 = this->dollars * 100 + this->cents;
    a1 = (this->sign == signType::minus) ? -a1 : a1;
    long a2 = x.getDollars() * 100 + x.getCents();
    a2 = (x.getSign() == signType::minus) ? -a2 : a2;
    long a3 = a1 - a2;
    this->sign = (a3 < 0) ? signType::minus : signType::plus;
    a3 = abs(a3);
    this->dollars = a3 / 100;
    this->cents = a3 % 100;
    return *this;
}

currency currency::percent(double x)
{
    long value = (this->dollars * 100 + this->cents) * (x / 100);
    return currency(this->sign, value / 100, value % 100);
}
currency currency::multiply(double x)
{
    long value = (this->dollars * 100 + this->cents) * x;
    return currency(this->sign, value / 100, value % 100);
}
currency currency::divide(double x)
{
    long value = (this->dollars * 100 + this->cents) / x;
    return currency(this->sign, value / 100, value % 100);
}

// << ==================== the end ==================== >>

// below are implenmentation of the funcs from the textbook's official website's source code

currency::currency(signType theSign, unsigned long theDollars,
    unsigned int theCents)
{ // Create a currency object.
    setValue(theSign, theDollars, theCents);
}

void currency::setValue(signType theSign, unsigned long theDollars,
    unsigned int theCents)
{ // Set currency value.
    if (theCents > 99)
        // too many cents
        throw "Cents should be < 100";

    sign = theSign;
    dollars = theDollars;
    cents = theCents;
}

void currency::setValue(double theAmount)
{ // Set currency value.
    if (theAmount < 0) {
        sign = signType::minus;
        theAmount = -theAmount;
    } else
        sign = signType::plus;

    dollars = (unsigned long)theAmount;
    // extract integer part
    cents = (unsigned int)((theAmount + 0.001 - dollars) * 100);
    // get two decimal digits
}

currency currency::add(const currency& x) const
{ // Add x and *this.
    long a1, a2, a3;
    currency result;
    // convert invoking object to signed integers
    a1 = dollars * 100 + cents;
    if (sign == signType::minus)
        a1 = -a1;

    // convert x to signed integer
    a2 = x.dollars * 100 + x.cents;
    if (x.sign == signType::minus)
        a2 = -a2;

    a3 = a1 + a2;

    // convert to currency representation
    if (a3 < 0) {
        result.sign = signType::minus;
        a3 = -a3;
    } else
        result.sign = signType::plus;
    result.dollars = a3 / 100;
    result.cents = a3 - result.dollars * 100;

    return result;
}

currency& currency::increment(const currency& x)
{ // Increment by x.
    *this = add(x);
    return *this;
}

void currency::output() const
{ // Output currency value.
    if (sign == signType::minus)
        cout << '-';
    cout << '$' << dollars << '.';
    if (cents < 10)
        cout << '0';
    cout << cents;
}
