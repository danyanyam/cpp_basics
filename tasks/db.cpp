/**
 * Task from
 * https://www.coursera.org/learn/c-plus-plus-white/programming/sO7Vq/final-naia-zadacha-kursa
 *
 * Create a database, which takes two arguments DATE ACTION, where
 * DATE   - string in format (%Y-%m-%d)
 * ACTION - string of any content
 *
 * database should recorgnise different commands:
 * - ADD  DATE ACTION
 * - DEL  DATE ACTION
 * - DEL  DATE
 * - FIND DATE
 * - ADD  DATE ACTION
 * - PRINT
 *
 */

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define RESET "\033[0m"
#define GREEN "\033[32m" /* Green */

void print_set(set<string> s) {
    for (auto &&i : s) {
        cout << i << ' ';
    }
}

class Date {
   private:
    int day = 1, month = 1, year = 1970;

   public:
    Date(){};
    Date(int &new_day, int &new_month, int &new_year) {
        day = new_day, month = new_month, year = new_year;
    };
    int get_day() { return day; }
    int get_month() { return month; }
    int get_year() { return year; }

    string to_str() {
        stringstream stream;
        stream << setw(4) << setfill(' ') << year << '-' << setw(2)
               << setfill('0') << month << '-' << setw(2) << setfill('0')
               << day;
        return stream.str();
    }

    Date parse_date(string &s) {
        stringstream stream(s);

        char sep = '-';
        int nyear, nmonth, nday;

        stream >> nyear;
        stream.ignore(1);
        stream >> nmonth;
        stream.ignore(1);
        stream >> nday;

        return Date(nday, nmonth, nyear);
    }
};

ostream &operator<<(ostream &stream, Date &d) {
    stream << d.to_str();
    return stream;
}
bool operator<(Date &lhs, Date &rhs) {
    if (lhs.get_year() < rhs.get_year()) {
        return true;
    } else if (lhs.get_year() == rhs.get_year()) {
        if (lhs.get_month() < rhs.get_month()) {
            return true;
        } else if (lhs.get_month() == rhs.get_month()) {
            return lhs.get_day() < rhs.get_day();
        } else {
            return false;
        }
    } else {
        return false;
    }
}
bool operator==(Date &lhs, Date &rhs) {
    return lhs.get_day() == rhs.get_day() and
           lhs.get_month() == rhs.get_month() and
           lhs.get_year() == rhs.get_year();
}

class DataBase {
   private:
    map<string, set<string> > data = {};

    void print(string &date) {
        Date dt;
        dt = dt.parse_date(date);
        string key = dt.to_str();

        cout << endl
             << endl
             << "========== " << GREEN << "FIND DATE " << RESET << key
             << " ==========" << endl
             << endl;

        if (data.count(key) > 0) {
            for (auto &text : data[key]) {
                cout << key << ' ' << text << endl;
            }
        }
        cout << endl
             << "==========" << GREEN << " FIND DATE " << RESET << key
             << " ==========" << endl
             << endl;
    }

   public:
    void print() {
        cout << endl
             << endl
             << "========== " << GREEN << "PRINTING DB" << RESET
             << " ==========" << endl;

        for (auto &&records : data) {
            for (auto &record_string : records.second) {
                cout << records.first << ' ' << record_string << endl;
            }
        }
    }
    void add(string &date, string &text) {
        set<string> existing;
        pair<string, set<string> > new_value;

        Date dt;
        dt = dt.parse_date(date);
        string key = dt.to_str();

        bool dt_exist = data.count(key) > 0;
        new_value.first = key;

        if (dt_exist) {
            existing = data[key];
            if (existing.count(text) > 0) {
                cout << "[LOGS] "
                     << "duplicate: " << text << endl;
                return;
            }
        }
        existing.insert(text);

        new_value.second = existing;
        data[new_value.first] = new_value.second;
        cout << "[LOGS] "
             << "successfully added" << text << endl;
    }
    void find(string &date) { print(date); }
    void del(string &date) {
        Date dt;
        dt = dt.parse_date(date);
        string key = dt.to_str();
        if (data.count(key) > 0) {
            data.erase(key);

            cout << "[LOGS] "
                 << "successfully erased" << key << endl;
        } else {
            cout << "[LOGS] "
                 << "could not erase messages at " << key << endl;
        }
    }
    void del(string &date, string &text) {
        Date dt;
        dt = dt.parse_date(date);
        string key = dt.to_str();

        if (data.count(key) > 0) {
            set<string> s = data[key];
            s.erase(text);
            data[key] = s;
            cout << "[LOGS] "
                 << "successfully deleted message " << text << " at date "
                 << key << endl;
        } else {
            cout << "[LOGS] "
                 << "key not found: " << key << endl;
        }
    }
};

int main() {
    DataBase db;
    string date = "2021-8-9";
    string date1 = "2021-8-10";
    string date2 = "2021-8-11";
    string date3 = "2021-8-12";
    string text = "b";
    string text1 = "asdassadadmalskdlamsd";

    db.add(date1, text);
    db.add(date2, text1);
    db.print();
    db.del(date2);
    db.print();
}