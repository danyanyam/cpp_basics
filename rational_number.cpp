#include <iostream>
#include <numeric>

using namespace std;

class Rational {
   public:
    Rational(){};
    Rational(int numerator, int denominator) {
        if (denominator < 0 and numerator > 0 or denominator < 0 and numerator < 0) {
            numerator = -1 * numerator;
            denominator = -1 * denominator;
        } else if (numerator == 0) {
            denominator = 1;
        }

        int g = gcd(numerator, denominator);

        p = numerator / g;
        q = denominator / g;
    };

    int numerator() const { return p; }
    int denominator() const { return q; }

   private:
    int p = 0;
    int q = 1;
};

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

Rational operator+(Rational& lhs, Rational& rhs) {
    int new_denominator = lcm(lhs.denominator(), rhs.denominator());
    int new_numerator = new_denominator / lhs.denominator() * lhs.numerator() + new_denominator / rhs.denominator() * rhs.numerator();
    return Rational(new_numerator, new_denominator);
}

Rational operator*(Rational& lhs, Rational& rhs) { return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator()); }
Rational operator*(Rational& lhs, int rhs) { return Rational(lhs.numerator() * rhs, lhs.denominator()); }
Rational operator*(int rhs, Rational& lhs) { return Rational(lhs.numerator() * rhs, lhs.denominator()); }

Rational operator-(Rational& lhs, Rational& rhs) {
    cout << -1 * rhs << endl;
    return lhs + rhs;
}

int main() {
    Rational r1(6, 2);
    Rational r2(1, 2);
    // cout << r1 - r2;
    cout << -1 * r1;
    return 0;
}

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
        if (defaultConstructed.numerator() != 0 || defaultConstructed.denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}