#pragma once
#include <iostream>
#include <string>
using namespace std;

string const errorInvalid = "Invalid input type, please retry.\n";
string const errorNoOption = "Input is not an option, please retry.\n";

void clearStream()
{
    cin.clear();
    cin.ignore(1000, '\n');
}


template <typename T>
bool checkOption(T& input, T total)
{
    if (input >= 1 && input <= total)
        return true;
    return false;
}
template <typename T>
bool checkOption(T &input, T options[])
{
    for (int i = 0; i < sizeof(options); i++)
        if (input == options[i])
            return true;
    return false;
}
template <typename T, typename U>
bool checkOption(T &input, U options[])
{
    for (int i = 0; i < sizeof(options); i++)
        if (input == options[i])
            return true;
    return false;
}


template <typename T>
void validateUserInput(T &input)
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
            cout << errorInvalid << endl;
        }
    }
}

template <typename T, typename U>
void validateUserInput(T &input, U options[])
{
    while (1)
    {
        if (cin >> input)
        {
            clearStream();
            bool b = checkOption(input, options);
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

template <>
void validateUserInput<string>(string &input)
{
    while (1)
    {
        if (getline(std::cin, input))
            return;
        else
        {
            clearStream();
            cout << errorInvalid;
        }
    }
}
