#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;

bool compare(string s1, string s2) {
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
    return s1 == s2;
}

void getNow(int& day, int& month, int& year) {
    time_t now = time(0);
    tm* t = localtime(&now);
    year = (t->tm_year + 1900);
    month = (t->tm_mon + 1);
    day = t->tm_mday;
}

#endif