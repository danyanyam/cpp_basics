#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;
/**
 * В плюсах перед сравнениями и арифметическими операциями
 *  числа приводятся к общему типу по следующей схеме:
 *
 *  - Все типы меньше int переводятся к int
 *  - Из двух типов выбирается больший по размеру
 *  - Если размер одинаковый выбирается usigned
 *
 * TODO: дописать примеры конверсий
 */

int main() {
    vector<int> count = {1, 2, 3, 4, 9};

    // Первый вариант реализации
    // изначально счетчик переводим к типу size_t
    for (size_t i = 0; i < count.size(); i++) {
        cout << count[i];
    }

    // размер контейнера переопредяем в int
    for (int i = 0; i < static_cast<int>(count.size()); i++) {
        cout << count[i];
    }
}