/**
 * https://www.coursera.org/learn/c-plus-plus-yellow/programming/7T2kJ/sriedniaia-tiempieratura-2/submission
 *
 * Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней.
 *Найдите номера дней (в нумерации с нуля) со значением температуры выше
 *среднего арифметического за все N дней.
 *
 *Гарантируется, что среднее арифметическое значений температуры является целым
 *числом.
 *
 * Формат ввода
 *
 * Вводится число N, затем N целых чисел — значения температуры в 0-й, 1-й, ...
 * (N−1)-й день. Гарантируется, что N не превышает миллиона (10^6), а значения
 * температуры, измеряющиеся в миллионных долях градусов по Цельсию, лежат в
 * диапазоне от −10^8 до 10^8. Проверять соблюдение этих ограничений не нужно:
 *вы можете ориентироваться на них при выборе наиболее подходящих типов для
 * переменных.
 *
 * - Формат вывода -
 * Первое число K — количество дней, значение температуры в которых выше
 *среднего арифметического. Затем K целых чисел — номера этих дней.
 *
 */

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void avg_temp(vector<int16_t> v) {
    vector<int16_t> res;
    int16_t sum = 0, cnt = 0, j = 0;
    float mean = 0.0;

    // finding sum of temperature vector
    for_each(v.begin(), v.end(), [&](const int16_t& i) { sum += i; });

    mean = sum / static_cast<float>(v.size());
    // deriving the way temprature is filtered
    auto filter = [&](int16_t& i) { return i > mean; };

    // how many days tempretature was above average
    cnt = count_if(begin(v), end(v), filter);
    cout << cnt << endl;

    // indexes of such days
    for (size_t i = 0; i < v.size(); i++) {
        if (filter(v[i])) {
            cout << i << ' ';
        }
    }
}

int main(int argc, char const* argv[]) {
    string n, temp;
    int16_t v;

    getline(cin, n);
    getline(cin, temp);

    stringstream iss(temp);
    size_t N = stoi(n);
    vector<int16_t> temps;

    while (iss.good()) {
        iss >> v;
        temps.push_back(v);
    }

    avg_temp(temps);
}
