#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    /**
     * argc - argument count (сколько аргументов было)
     * передано в функцию main.
     * argv - массив указателей на переданные аргументы.
     * Всегда первый жлемент - название файла. Можно
     * посомтреть на все аргументы, итерируясь по argv
     * как показано ниже:
     */

    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            cout << argv[i] << endl;
        }
    }
}
