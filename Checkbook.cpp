/*
Checkbook balancing program. The program will read in, from the console,
the following for all checks that were not cashed as of the last time you balanced your checkbook:
the number of each check (int), the amount of the check (double), and whether or not it has been cashed (1 or 0, boolean in the array).
Use an array with the class as the type. The class should be a class for a check.

There should be three member variables to record the check number, the check amount, and whether or not the check was cashed.
The class for a check will have a member variable of type Money (as defined on page 662 in the book; Display 11.9)
to record the check amount. So, you will have a class used within a class.

The class for a check should have accessor and mutator functions as well as constructors and functions for both input and output of a check.
In addition to the checks, the program also reads all the deposits (from the console; cin),
the old and the new account balance (read this in from the user at the console; cin).
You may want another array to hold the deposits.
The new account balance should be the old balance plus all deposits, minus all checks that have been cashed.

The program outputs the total of the checks cashed, the total of the deposits,
what the new balance should be, and how much this figure differs from what the bank says the new balance is.
It also outputs two lists of checks: the checks cashed since the last time you balanced your
checkbook and the checks still not cashed. [ edit: if you can, Display both lists of checks in sorted order
from lowest to highest check number.]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int digit_to_int(char c);
class Money {
public:
    friend Money operator +(const Money& amount1, const Money& amount2);
    friend Money operator -(const Money& amount1, const Money& amount2);
    friend Money operator -(const Money& amount);
    friend bool operator ==(const Money& amount1, const Money& amount2);
    friend bool operator <(const Money& amount1, const Money& amount2);

    Money(long dollars, int cents);
    Money(long dollars) : all_cents(dollars * 100) {};
    Money() :all_cents(0) {};

    double get_value()const { return (all_cents * 0.01); };

    friend istream& operator >>(istream& ins, Money& amount);
    friend ostream& operator <<(ostream& outs, Money& amount);

private:
    long all_cents;
};

class Check {
public:
    //constructors
    Check(int number, Money amount, bool cashed);
    Check(int number, Money amount);
    Check() :check_number(0), check_amount(0), is_cashed(false) {};

    //accessors and mutators 
    void set_number(int number) { check_number = number; };
    void set_amount(Money amount) { check_amount = amount; };
    void set_cashed(bool cashed) { is_cashed = cashed; };
    int get_number() const { return check_number; };
    Money get_amount() const { return check_amount; };
    bool get_cashed() { return is_cashed; };

    //operator overload 
    friend istream& operator >>(istream& ins, Check& check);
    friend ostream& operator <<(ostream& outs, Check& check);
    friend bool operator <(const Check& c1, const Check& c2);


private:
    int check_number;
    Money check_amount;
    bool is_cashed;
};

vector<Check>input_check();
vector<Money>input_deposit();
Money cashed_checks_sum(vector<Check>vector);
Money deposits_sum(vector<Money>vector);
void print_vector(vector<Check>vector);

int main()
{
    Money curr_balace, old_balance, new_balance, difference;
    Money total_checks_cashed, total_deposits;
    vector<Check>check_vector;
    vector<Money>deposit_vector;
    vector<Check>cashed_checks;
    vector<Check>uncashed_checks;
    int check_number{};
    Money check_amount;

    cout << "Welcome to the checkbook balancing program!" << endl;
    cout << "Please enter account balances in the format: $##.##" << endl;
    cout << "Old bank account balance: ";
    cin >> old_balance;
    cout << "New bank account balance: ";
    cin >> curr_balace;
    cout << endl;

    check_vector = input_check();
    cout << endl;
    deposit_vector = input_deposit();

    total_checks_cashed = cashed_checks_sum(check_vector);
    total_deposits = deposits_sum(deposit_vector);
    new_balance = old_balance + total_deposits - total_checks_cashed;
    difference = curr_balace - new_balance;

    cout << endl;
    cout << "The total of all cashed checks: " << total_checks_cashed << endl;
    cout << "The total of deposits: " << total_deposits << endl;
    cout << "New balance: " << new_balance << endl;
    cout << "The difference from current bank balance: " << difference << endl;

    //creates two vectors for cashed and uncashed checks 
    for (int i = 0; i < check_vector.size(); i++) {
        if (check_vector[i].get_cashed() == true) {
            cashed_checks.push_back(check_vector[i]);
        }
        else {
            uncashed_checks.push_back(check_vector[i]);
        }
    }

    sort(cashed_checks.begin(), cashed_checks.end());
    sort(uncashed_checks.begin(), uncashed_checks.end());

    cout << endl;
    cout << "The checks that have been cashed:" << endl;
    print_vector(cashed_checks);
    cout << "The checks that have NOT been cashed:" << endl;
    print_vector(uncashed_checks);

    return 0;
}

void print_vector(vector<Check>vector) {
    for (int i = 0; i < vector.size(); i++) {
        cout << vector[i];
        cout << endl;
    }
    cout << endl;
}

//inputs check information from user into vector 
vector<Check>input_check() {

    bool end = false;
    vector <Check> check_vector;
    int check_number;
    Money check_amount;
    char cashed;
    bool is_cashed;

    cout << "Please enter your check information!" << endl;
    cout << "Format: number of the check, amount of the check ($##.##), whether the check has been cashed (y/n), each separated by a space." << endl;
    cout << "For example: 1 $10.00 y" << endl;
    cout << "Enter -1, when finished entering checks." << endl;
    cout << endl;

    //input check info in a vector 
    while (end == false) {
        cin >> check_number;
        if (check_number == -1) {
            end = true;
        }
        else {
            cin >> check_amount >> cashed;
            if ((cashed == 'y') || (cashed == 'Y')) {
                is_cashed = true;
            }
            else {
                is_cashed = false;
            }
            Check input(check_number, check_amount, is_cashed);
            check_vector.push_back(input);
        }
    }
    return check_vector;
}

//inputs deposit information from user into vector 
vector<Money>input_deposit() {

    int n = 0;
    vector <Money> deposit_vector;
    Money amount;

    cout << "How many deposits do you wish to enter?" << endl;
    cin >> n;
    cout << "Please enter your deposits in the format: $##.##" << endl;

    for (int i = 0; i < n; i++) {
        cin >> amount;
        deposit_vector.push_back(amount);
    }
    return deposit_vector;
}

Money cashed_checks_sum(vector<Check>vector) {
    Money sum = 0;
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].get_cashed() == true) {
            sum = sum + vector[i].get_amount();
        }
    }
    return sum;
}

Money deposits_sum(vector<Money>vector) {
    Money sum = 0;
    for (int i = 0; i < vector.size(); i++) {
        sum = sum + vector[i];
    }
    return sum;
}

//Class Check
//constructor
Check::Check(int number, Money amount, bool cashed) {
    check_number = number;
    check_amount = amount;
    is_cashed = cashed;
}
Check::Check(int number, Money amount) {
    check_number = number;
    check_amount = amount;
}

istream& operator >>(istream& ins, Check& check) {
    int number{};
    Money amount;
    bool cashed{};

    check.check_number = number;
    check.check_amount = amount;
    check.is_cashed = cashed;

    return ins;
}

ostream& operator <<(ostream& outs, Check& check) {
    outs << "#" << check.check_number;
    outs << " amount: " << check.check_amount;
    /*if (check.is_cashed) {
        outs << " cashed";
    }
    else {
        outs << " not cashed";
    }
    */
    return outs;
}

//overload < operator to sort checks by number
bool operator <(const Check& c1, const Check& c2) {
    return c1.check_number < c2.check_number;
}


//Class Money
//overloading operators 
Money operator +(const Money& amount1, const Money& amount2) {
    Money temp;
    temp.all_cents = amount1.all_cents + amount2.all_cents;
    return temp;
}

Money operator -(const Money& amount1, const Money& amount2) {
    Money temp;
    temp.all_cents = amount1.all_cents - amount2.all_cents;
    return temp;
}

Money operator -(const Money& amount) {
    Money temp;
    temp.all_cents = -amount.all_cents;
    return temp;
}

bool operator ==(const Money& amount1, const Money& amount2) {
    return (amount1.all_cents == amount1.all_cents);
}

bool operator <(const Money& amount1, const Money& amount2) {
    return (amount1.all_cents < amount1.all_cents);
}

istream& operator >>(istream& ins, Money& amount) {
    char one_char, decimal_point, digit1, digit2;
    long dollars;
    int cents;
    bool negative;

    ins >> one_char;
    if (one_char == '-') {
        negative = true;
        ins >> one_char;
    }
    else {
        negative = false;
    }
    ins >> dollars >> decimal_point >> digit1 >> digit2;
    if (one_char != '$' || decimal_point != '.' || !isdigit(digit1) || !isdigit(digit2)) {
        cout << "Error illeagal form for money input" << endl;
        exit(1);
    }

    cents = digit_to_int(digit1) * 10 + digit_to_int(digit2);

    amount.all_cents = dollars * 100 + cents;
    if (negative) {
        amount.all_cents = -amount.all_cents;
    }
    return ins;
}

ostream& operator <<(ostream& outs, Money& amount) {
    long positive_cents, dollars, cents;
    positive_cents = labs(amount.all_cents);
    dollars = positive_cents / 100;
    cents = positive_cents % 100;

    if (amount.all_cents < 0) {
        outs << "- $" << dollars << '.';
    }
    else {
        outs << "$" << dollars << '.';
    }
    if (cents < 10) {
        outs << '0';
    }
    outs << cents;
    return outs;
}

//converts char to int
int digit_to_int(char c) {
    return (static_cast<int>(c) - static_cast<int>('0'));
}

//constructor
Money::Money(long dollars, int cents) {
    if (dollars * cents < 0) {
        cout << "Illeagal values for dollars and cents" << endl;
        exit(1);
    }
    all_cents = dollars * 100 + cents;
}
