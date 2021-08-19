//
// task without solution was taken from
// https://www.coursera.org/learn/c-plus-plus-white/lecture/ifJgS/vviedieniie-v-iskliuchieniia
//

#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

class Rational {
    /**
     * Класс описывает рациональное число
     * и такие операции над рациональными числами
     * как сравнение, сложение, вычитание, умножение
     * деление. Кроме того, благодаря операторам сравнения
     * возможно использование в коллекциях vector,
     * map, set
     */

   public:
    Rational(){};
    Rational(int numerator, int denominator) {
        setNumber(numerator, denominator);
    };
    int numerator() const { return p; }
    int denominator() const { return q; }
    void setNumber(int& new_p, int& new_q) {
        tuple<int, int> args = validatepq(new_p, new_q);
        p = get<0>(args);
        q = get<1>(args);
    }

   private:
    int p = 0, q = 1;

    tuple<int, int> validatepq(int& new_p, int& new_q) {
        if (new_q < 0 and new_p > 0 or new_q < 0 and new_p < 0) {
            new_p = -1 * new_p;
            new_q = -1 * new_q;
        } else if (new_p == 0) {
            new_q = 1;
        }

        int g = gcd(new_p, new_q);
        new_p = new_p / g;
        new_q = new_q / g;
        return tuple<int, int>{new_p, new_q};
    }
};

istream& operator>>(istream& stream, Rational& r) {
    /**
     * Одно из важнейших мест для понимания. Проинициализировали
     * переменные, выдали им типы, а вывод потока разбил входную
     * строку на токены соответсвующих типов.
     */

    int p = -1, q = -1;
    int default_p = 0, default_q = 1;
    char d = '/';

    // сплит возможен благодаря указанию типов переменных
    // которые обращаются к потоку
    if (stream.good()) {
        stream >> p >> d >> q;
        if (d == '/' && p >= 0 && q >= 0) {
            r.setNumber(p, q);
        } else {
            r.setNumber(default_p, default_q);
        }
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Rational& r) {
    /**
     * Функция перегружает стандартный оператор вывода информации
     * в поток для дальйнешего использования рациональных чисел в
     * следующем формате:
     *
     * Rational r(2, 3);
     * cout << r;   //  '2/3'
     *
     */
    if (r.numerator() == 0) {
        return stream << 0;
    }
    stream << r.numerator() << '/' << r.denominator();
    return stream;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int new_denominator = lcm(lhs.denominator(), rhs.denominator());
    int new_numerator = new_denominator / lhs.denominator() * lhs.numerator() +
                        new_denominator / rhs.denominator() * rhs.numerator();
    return Rational(new_numerator, new_denominator);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.numerator(),
                    lhs.denominator() * rhs.denominator());
}
Rational operator/(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.numerator() * rhs.denominator(),
                    lhs.denominator() * rhs.numerator());
}
Rational operator*(const Rational& lhs, const int& rhs) {
    return Rational(lhs.numerator() * rhs, lhs.denominator());
}
Rational operator/(const Rational& lhs, const int& rhs) {
    return Rational(lhs.numerator(), lhs.denominator() * rhs);
}
Rational operator*(const int& rhs, const Rational& lhs) {
    return Rational(lhs.numerator() * rhs, lhs.denominator());
}
Rational operator/(const int& lhs, const Rational& rhs) {
    return lhs * Rational(rhs.denominator(), rhs.numerator());
}
Rational operator-(const Rational& lhs, const Rational& rhs) {
    /**
     * Вычитание это сложение с обратным знаком
     * поэтому определим его через сложение.
     */
    Rational rhs_ = -1 * rhs;
    return lhs + rhs_;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    int new_denominator = lcm(lhs.denominator(), rhs.denominator());
    return new_denominator / lhs.denominator() * lhs.numerator() ==
           new_denominator / rhs.denominator() * rhs.numerator();
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    /**
     * Для использования класса Rational в коллекциях
     * типа set достаточно определить функцию для сравнения
     * объектов
     */

    int new_denominator = lcm(lhs.denominator(), rhs.denominator());
    if (lhs.numerator() * new_denominator / lhs.denominator() <
        rhs.numerator() * new_denominator / rhs.denominator()) {
        return true;
    } else {
        return false;
    }
}

void print(const set<Rational>& s) {
    for (auto&& i : s) {
        cout << i << ' ';
    }
    cout << endl;
}

void print(const map<Rational, string>& s) {
    for (auto&& i : s) {
        cout << i.first << ':' << i.second << ' ';
    }
    cout << endl;
}

int main() { return 0; }

int unit_tests() {
    {
        const Rational r(3, 10);
        if (r.numerator() != 3 || r.denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.numerator() != 2 || r.denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.numerator() != -2 || r.denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.numerator() != -2 || r.denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.numerator() != 0 || r.denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.numerator() != 0 ||
            defaultConstructed.denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        cout << c << endl;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;

    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2
                 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1
                 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        cout << r1 << ' ' << r2 << ' ' << r3 << endl;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't "
                    "change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;

    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}