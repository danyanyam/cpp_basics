#include <iostream>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& stream, vector<T> vec) {
    cout << '[';

    for (auto&& i : vec) {
        cout << i << ", ";
    }

    cout << ']';
    return stream;
};

int main(int argc, char const* argv[]) {

     cout << v;
    }
