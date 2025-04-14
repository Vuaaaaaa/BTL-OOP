#ifndef OTHERSTRUCT_H
#define OTHERSTRUCT_H
#include "validate.h"
#include "func.h"
#include <iostream>
using namespace std;

class Date {
    private:
        int day;
        int month;
        int year;
    public:
        Date(): Date(1,1,2025) {}
        Date(int d, int m, int y) {
            if (checkDate(d, m, y)) {
                day = d;
                month = m;
                year = y;
            } else {
                cout << "Constructor date loi\n";
            }
        }
        Date& operator=(Date other) {
            if(*this != other) {
                day = other.day;
                month = other.month;
                year = other.year;
            }
            return *this;
        }
        bool operator!=(Date& other) {
            return day != other.day || month != other.month || year != other.year;
        }
        bool operator==(Date& other) {
            return day == other.day && month == other.month && year == other.year;
        }
        friend ostream& operator<< (ostream& out, const Date& date) {
            out << (date.day<10?"0":"") << date.day << "/"
                << (date.month<10?"0":"") << date.month << "/" << date.year << "\n";
            return out;
        }
        friend istream& operator>> (istream& in, Date& date) {
            do {
                cout << "nhap ngay: ";
                in >> date.day;
                cout << "nhap thang: ";
                cin >> date.month;
                cout << "nhap nam: ";
                cin >> date.year;
                if (!checkDate(date.day, date.month, date.year)) {
                    cout << "Date khong hop le\n";
                }
            } while (!checkDate(date.day, date.month, date.year));
            return in;
        }
        void setDay(int d) {
            if (checkDate(d, month, year))
                day = d;
            else 
                cout << "set day loi\n";
        }
        void setMonth(int m) {
            if (checkDate(day, m, year)) 
                month = m;
            else 
                cout << "set month loi\n";
        }
        void parseString(string_view s) {
            day = (s[0] - '0') * 10 + (s[1] - '0');
            month = (s[3] - '0') * 10 + (s[4] - '0');
            year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 
                    + (s[8] - '0') * 10 + (s[9] - '0');
        }
        void setYear(int y) {
            if (checkDate(day, month, y))
                year = y;
            else 
                cout << "set year loi\n";
        }
        bool operator>=(const Date& other) const {
            if (year != other.year) return year >= other.year;
            if (month != other.month) return month >= other.month;
            return day >= other.day;
        }
        bool operator>(const Date& other) const {
            if (year != other.year) return year > other.year;
            if (month != other.month) return month > other.month;
            return day > other.day;
        }
        bool lNow() {
            int x, y, z;
            getNow(x, y, z);
            Date now(x, y, z);
            return (now > *this); 
        }
        bool leNow() {
            int x, y, z;
            getNow(x, y, z);
            Date now(x, y, z);
            return (now >= *this); 
        }
        bool gNow() {
            int x, y, z;
            getNow(x, y, z);
            Date now(x, y, z);
            return (*this > now);
        }
        bool geNow() {
            int x, y, z;
            getNow(x, y, z);
            Date now(x, y, z);
            return (*this >= now);
        }
        int getDay() {return day;}
        int getMonth() {return month;}
        int getYear() {return year;}
};

#endif