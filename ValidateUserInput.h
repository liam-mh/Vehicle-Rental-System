#ifndef VALIDATE_H
#define VALIDATE_H
/*
* ValidateUserInput.h - A template for input validation.
* 
* Methods included:
*   void global(T option)
*   bool checkOption(T &input, T total)
*   bool checkOption(T &input, T options[])
*   bool checkOption(T& input, T total, T single)
*   void validateUserInput(T &input)
*   void validateUserInput<string>(string& input)
*   void validateUserInput(T& input, T total)
*   void validateUserInput(T& input, T total, T single)
*   void validateRegistrationInput<string>(string &input)
*   void validateMobileInput<string>(string &input)

* Code idea
* https://gist.github.com/mikeDevInMyDreams/0b693087ae35342c9094
* I was finding the best way to validate user input with try - catch blocks. 
* However using a template would allow easy repetiton of code.
* I have used this repo to help aid some design in this template.
* I have taken elements from it, and implemented them to best fit my systems needs.
*/

#include <iostream>
#include <regex>
#include <string>
using namespace std;

template<typename T>
void global(T option)
{
    string const errorInvalid = "\nInvalid input type, please retry.";
    string const errorNoOption = "\nInput is not an option, please retry.";
    string const errorFormat = "\nInvalid format, please retry in the correct format.\n";
    auto clearStream = []()
    {
        cin.clear();
        cin.ignore(1000, '\n');
    };

    switch (option)
    {
    case 0: clearStream(); break;
    case 1: cout << errorInvalid; break;
    case 2: cout << errorNoOption; break;
    case 3: cout << errorFormat; break;
    }
}

/*
* checkOption() Compares an input parameter against a secondary parameter.
* Inputs: 
*   Output variable - The input value to be checked.
*   Options - The correct comparisons for the first parameter.
*   *Overload* Single - A single correct comparisons for the first parameter outside the scope of Options.
*                       Such as an exit determination number.
* Returns bool.
*/
template <typename T>
bool checkOption(T &input, T total)
{
    // input is between 1 and total
    if (input >= 1 && input <= total)
        return true;
    return false;
}
template <typename T>
bool checkOption(T &input, T options[])
{
    // input is == any item in array
    for (T i = 0; i < sizeof(options); i++)
        if (input == options[i])
            return true;
    return false;
}
template <typename T>
bool checkOption(T& input, T total, T single)
{
    // input is between 1 and total, or == single
    if (input >= 1 && input <= total || input == single)
        return true;
    return false;
}

/*
* validateUserInput() Compares an input parameter against a secondary parameter.
* Inputs: 
*   Output variable - The input value to be checked.
*   *Overloaded* Options - The correct comparisons for the first parameter.
*   *Overload* Single - A single correct comparisons for the first parameter outside the scope of Options.
*                       Such as an exit determination number.
* Returns Output variable as correct datatype.
*/
template <typename T>
void validateUserInput(T &input)
{
    while (1)
    {
        if (cin >> input)
        {
            global(0);
            return;
        }
        else
        {
            global(0);
            global(1);
        }
    }
}

template <>
void validateUserInput<string>(string& input)
{
    while (1)
    {
        if (getline(cin, input))
            return;
        else
        {
            global(0);
            global(1);
        }
    }
}

template <typename T>
void validateUserInput(T& input, T total)
{
    while (1)
    {
        if (cin >> input)
        {
            global(0);
            bool b = checkOption(input, total);
            if (b)
                return;
            global(2);
        }
        else
        {
            global(0);
            global(1);
        }
    }
}

template <typename T>
void validateUserInput(T& input, T total, T single)
{
    while (1)
    {
        if (cin >> input)
        {
            global(0);
            bool b = checkOption(input, total, single);
            if (b)
                return;
            global(2);
        }
        else
        {
            global(0);
            global(1);
        }
    }
}

/*
* validateRegistrationInput() Uses regex to check a correct input format is entered.
* Inputs:
*   Output variable - The input value to be formatted.
* Returns Output variable in correct format.
*/
template <typename T>
void validateRegistrationInput(T &input)
{}

template <>
void validateRegistrationInput<string>(string &input)
{
    /*
    * Code Snippet - Highlighted below
    * https://regexlib.com/REDetails.aspx?regexp_id=1981
    * I have used the regex template from this website and learnt how to use regex expressions on others.
    * I couldn't find a better expression as this one will also accept AA1 AAA, as I just need AA11 AAA format.
    * To combat this I have applied a length filter to only return correct if 8 characters long.
    */

    // ----------------------------------
    regex r("([A-HJ-PR-Y]{2}([0][1-9]|[1-9][0-9])|[A-HJ-PR-Y]{1}([1-9]|[1-2][0-9]|30|31|33|40|44|55|50|60|66|70|77|80|88|90|99|111|121|123|222|321|333|444|555|666|777|888|999|100|200|300|400|500|600|700|800|900))[ ][A-HJ-PR-Z]{3}$");
    // ----------------------------------
    while (1)
    {
        if (getline(cin, input))
        {
            if (regex_match(input, r) && input.size() == 8)
                return;
            else
            {
                global(3);
                cout << "Registration:  ";
            }   
        }
    }
}

/*
* validateMobileInput() Uses regex to check a correct input format is entered.
* Inputs:
*   Output variable - The input value to be formatted.
* Returns Output variable in correct format.
*/
template <typename T>
void validateMobileInput(T& input)
{}

template <>
void validateMobileInput<string>(string& input)
{
    /*
    * Code Snippet - Highlighted below
    * https://www.regextester.com/104299
    * I have used the regex template from this website to format UK mobile numbers.
    */

    // ----------------------------------
    regex r(/*"((\+44(\s\(0\)\s|\s0\s|\s)?)|0)7\d{3}(\s)?\d{6}"*/ "");
    // ----------------------------------
    while (1)
    {
        if (getline(cin, input))
        {
            if (regex_match(input, r))
                return;
            else
            {
                global(3);
                cout << "Customer Number: ";
            }  
        }
    }
}

#endif // !VALIDATE_H