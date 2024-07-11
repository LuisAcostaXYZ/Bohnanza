#include <iostream>
using namespace std;
#pragma once

class IllegalTypeException : public std::exception {
public:
    IllegalTypeException(const char msg[]) { cout << msg << '\n'; }
};

class IllegalState : public std::exception {
public:
    IllegalState(const char msg[]) { cout << msg << '\n'; }
};

class  NotEnoughCoins : public std::exception {
public:
    NotEnoughCoins(const char msg[]) { cout << msg << '\n'; }
};