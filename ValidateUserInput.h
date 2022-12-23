/*
* ValidateUserInput.h - A template for input validation.
* 
* Methods included:
*   bool checkOption(T &input, T total)
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

class ValidateUserInput
{
private:
    ValidateUserInput() {}
    static ValidateUserInput* singleton;

    string const errorInvalid = "\nInvalid input type, please retry.\n";
    string const errorNoOption = "\nInput is not an option, please retry.\n";
    string const errorFormat = "\nInvalid format, please retry in the correct format.\n";
    void clearStream()
    {
        cin.clear();
        cin.ignore(1000, '\n');
    };

public:

    static ValidateUserInput* getInstance() {
        if (!singleton)
        {
            singleton = new ValidateUserInput();
            return singleton;
        }
        else
            return singleton;
    }
    void deleteInstance() {
        delete singleton;
        singleton = nullptr;
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
    bool checkOption(T& input, T total)
    {
        // input is between 1 and total
        if (input >= 1 && input <= total)
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

    
   /* * validateUserInput() Compares an input parameter against a secondary parameter.
    * Inputs:
    *   Output variable - The input value to be checked.
    *   *Overloaded* Options - The correct comparisons for the first parameter.
    *   *Overload* Single - A single correct comparisons for the first parameter outside the scope of Options.
    *                       Such as an exit determination number.
    * Returns Output variable as correct datatype.*/
    
    template <typename T>
    void validateUserInput(T& input)
    {
        while (1)
        {
            if (cin >> input)
            {
                clearStream();
                return;
            }
            else
            {
                clearStream();
                cout << errorInvalid;
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
                clearStream();
                cout << errorInvalid;
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
                clearStream();
                bool b = checkOption(input, total);
                if (b)
                    return;
                cout << errorNoOption;
            }
            else
            {
                clearStream();
                cout << errorInvalid;
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
                clearStream();
                bool b = checkOption(input, total, single);
                if (b)
                    return;
                cout << errorNoOption;
            }
            else
            {
                clearStream();
                cout << errorInvalid;
            }
        }
    }

    
    /** validateRegistrationInput() Uses regex to check a correct input format is entered.
    * Inputs:
    *   Output variable - The input value to be formatted.
    * Returns Output variable in correct format.
    */
    template <typename T>
    void validateRegistrationInput(T& input)
    {}

    template <>
    void validateRegistrationInput<string>(string& input)
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
                    cout << errorFormat << "Registration:  ";
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
        * https://stackoverflow.com/questions/51621150/uk-mobile-phone-and-uk-landline-regex
        * I have used the regex template from this website to format UK mobile numbers.
        */

        // ----------------------------------
        regex r("^0([1-6][0-9]{8,10}|7[0-9]{9})$");
        // ----------------------------------
        while (1)
        {
            if (getline(cin, input))
            {
                if (regex_match(input, r))
                    return;
                else
                    cout << errorFormat << "Customer Number: ";
            }
        }
    }
};


