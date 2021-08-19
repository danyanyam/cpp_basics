//
// Lecture from https://www.coursera.org/learn/c-plus-plus-white/lecture/ifJgS/vviedieniie-v-iskliuchieniia
//

#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Date {
    // 2017/08/01
    int year = 1970;
    int month = 1;
    int day = 1;
};

ostream& operator<<(ostream& stream, Date d) {
    // обратить внимание на манипуляции с месяцем и днём
    stream << "Date(" << d.year << '-' << setw(2) << setfill('0') << d.month
           << '-' << setw(2) << setfill('0') << d.day << ')';
    return stream;
}

void ensure_sepchar_skip(stringstream& stream) {
    /**
     * Супер интересно используем stringstream. Сначала засовываем в него строку
     * чтобы воспользоваться конкатенацией, затем преобразуем обратно в строку,
     * чтобы скормить исключению. Еще важный факт: .peek() возвращает код
     * символа а не сам символ.
     */

    if (stream.peek() != '/') {
        stringstream ss;
        ss << "expected / as date separator, but received "
           << char(stream.peek());  // код символа, а не символ
        throw runtime_error(ss.str());
    }
    stream.ignore(1);
}

Date parse_dates(const string& s) {
    stringstream stream(s);
    Date d;
    stream >> d.year;
    ensure_sepchar_skip(stream);
    stream >> d.month;
    ensure_sepchar_skip(stream);
    stream >> d.day;
    return d;
}

using namespace std;
int main() {
    string d = "2021a08b21";
    try {
        Date dd = parse_dates(d);
        cout << dd << endl;
    } catch (exception& ex) {
        cout << "wrong date separator" << ex.what()
             << endl;  // .what() возвращает тело эксепшена
    }
}