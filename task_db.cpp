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
#include <vector>

using namespace std;

string parse_date(const string &s) {
    stringstream stream(s);
    stringstream result;

    char sep = '-';
    int year, month, day;

    stream >> year;
    stream.ignore(1);
    stream >> month;
    stream.ignore(1);
    stream >> day;

    result << setw(4) << setfill(' ') << year << '-' << setw(2) << setfill('0')
           << month << '-' << setw(2) << setfill('0') << day;

    return result.str();
}

void print_set(set<string> s) {
    for (auto &&i : s) {
        cout << i << ' ';
    }
}

class DataBase {
   private:
    map<string, set<string> > data = {};

    void print(const string &date) {
        string dt = parse_date(date);
        cout << endl
             << endl
             << "========== FIND DATE " << dt << "==========" << endl
             << endl;

        if (data.count(dt) > 0) {
            for (const string &text : data[dt]) {
                cout << dt << ' ' << text << endl;
            }
        }
        cout << endl
             << endl
             << "========== FIND DATE " << dt << "==========" << endl
             << endl;
    }

   public:
    void print() {
        cout << endl
             << endl
             << "========== PRINTING DB ==========" << endl
             << endl;

        for (auto &&records : data) {
            for (const string &record_string : records.second) {
                cout << records.first << ' ' << record_string << endl;
            }
        }
        cout << endl << "========== PRINTING DB ==========" << endl;
    }
    void add(const string &date, const string &text) {
        set<string> existing;
        pair<string, set<string> > new_value;

        string dt = parse_date(date);
        bool dt_exist = data.count(dt) > 0;

        new_value.first = dt;

        if (dt_exist) {
            existing = data[dt];
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

    void find(const string &date) { print(date); }
};

int main() {
    DataBase db;
    string date = "2021-8-9";
    string date1 = "2021-8-10";
    string date2 = "2021-8-11";
    string text = "b";
    string text1 = "asdassadadmalskdlamsd";

    db.add(date1, text);
    db.add(date, text1);
    db.add(date, text);
    db.add(date2, text);
    db.add(date2, text1);
    db.add(date, text1);
    db.print();
    db.find(date);
}