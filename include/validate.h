#ifndef VALIDATE_H
#define VALIDATE_H
#include <iostream>
using namespace std;

bool checkDate(int day = 1, int month = 1, int year = 2025) {
    if (day > 0 && year >= 1000) {
        switch(month) {
            case 1:
            case 3:
            case 5: 
            case 7:
            case 8:
            case 10:
            case 12:
                return day <= 31;
            case 2:
                if (((year % 4 == 0) && (year % 100 != 0)) || (year%400 == 0)) {
                    return day <= 29;
                } else return day <= 28;
            case 4:
            case 6:
            case 9:
            case 11:
                return day <= 30;
            default:
                return 0;
        };
    } else return 0;
}

bool inRange(int x, int a, int b) {
    return x >= a && x <= b;
}

bool checkMa(string_view ma, int size) {
    if (ma.size() != size) return 0;
    return 1;
}

#endif