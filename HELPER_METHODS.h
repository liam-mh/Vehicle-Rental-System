#pragma once
#include <iostream>
using namespace std;

class HELPER_METHODS
{

public:
    string pound = "\x9C";
    static void CLEAR_SCREEN();
    static void SPACE();
    static bool YES_NO();

};

inline void HELPER_METHODS::CLEAR_SCREEN()
{
    system("cls");
}

inline void HELPER_METHODS::SPACE()
{
    cout << "" << endl;
}

inline bool HELPER_METHODS::YES_NO()
{
    int option = NULL;
    cout << "1) Yes" << endl;
    cout << "2) No" << endl;
    cin >> option;
    if (option != 1)
        return false;
    return true;
}
