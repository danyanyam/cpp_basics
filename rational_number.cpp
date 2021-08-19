#include <iostream>
using namespace std;

class Rational {
   public:
    Rational(){};
    Rational(int numerator, int denominator) {
        p = numerator;
        q = denominator;
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

int main() {
    Rational r(1, 3);
    cout << r << endl;
    return 0;
}