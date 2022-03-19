// Основная задача: использовать предопределенное множество
// для выбора действия.
#include <iostream>
#include <set>

using namespace std;

enum class RequestType {
    /**
     * В классе перечисления определены отношения порядка,
     * согласующиеся с порядком определения элементов
     * перечисления.
     */
    ADD,
    REMOVE,
    NEGATE
};

void process_request(set<int>& numbers, RequestType request_type,
                     int request_data) {
    /**
     * Функция обрабатывает переденанный запрос в соотвествии
     * с переданным правилом.
     */

    if (request_type == RequestType::ADD) {
        numbers.insert(request_data);
        cout << "inserted" << endl;
    } else {
        cout << "signal not recorgnised" << endl;
    }
}

void process_request_switch(set<int>& numbers, RequestType request_type,
                            int request_data) {
    switch (request_type) {
        case RequestType::ADD:
            numbers.insert(request_data);
            cout << "inserted" << endl;
            break;
        case RequestType::REMOVE:
            numbers.erase(request_data);
            cout << "erased" << endl;
            break;
        case RequestType::NEGATE:
            numbers.erase(request_data);
            numbers.insert(-request_data);
            cout << "negated" << endl;
            break;

        default:
            break;
    }
}

void print(set<int> v) {
    for (auto&& i : v) {
        cout << i << ' ';
    }
}

int main(int argc, char const* argv[]) {
    set<int> numbers = {1, 2, 3, 4};

    process_request_switch(numbers, RequestType::ADD, 5);
    process_request_switch(numbers, RequestType::REMOVE, 5);
    process_request_switch(numbers, RequestType::NEGATE, 1);
    print(numbers);

    // можно преобразовать enum class в числовые значения:
    cout << endl << endl;
    cout << "ADD code:    " << static_cast<int>(RequestType::ADD) << endl;
    cout << "REMOVE code: " << static_cast<int>(RequestType::REMOVE) << endl;
    cout << "NEGATE code: " << static_cast<int>(RequestType::NEGATE) << endl;
}
