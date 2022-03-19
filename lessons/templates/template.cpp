#include <iostream>
#include <utility>

using namespace std;



template <typename first, typename second>
pair<first, second> operator*(const pair<first, second>& lhs,
                              const pair<first, second>& rhs) {
    return make_pair(lhs.first * rhs.first, lhs.second * rhs.second);
}

template <typename T>
T sqr(T& x) {
    return x * x;
}

int main(int argc, char const* argv[]) {
    auto x = make_pair(1, 2);
    cout << sqr(x).second << endl;
    }

void tests() {
    double x = 2.5;
    cout << x << ' ' << sqr(x) << endl;

    int y = 2;
    cout << y << ' ' << sqr(y) << endl;

    float z = 2.3333;
    cout << z << ' ' << sqr(z) << endl;
}