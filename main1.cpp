#include "IntegerArray.h"
#include <iostream>

int main() {
    using std::cout;
    using std::cerr;
    using std::endl;

    // Создание с отрицательной длиной -> bad_length
    try {
        IntegerArray arr(-5);
    }
    catch (const bad_length& e) {
        cerr << "Test 1 - Caught bad_length (expected): " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cerr << "Test 1 - Unexpected exception: " << e.what() << endl;
    }

    // Выход за границы при доступе -> bad_range
    try {
        IntegerArray arr(3);
        arr[0] = 1; arr[1] = 2; arr[2] = 3;
        cout << arr[5] << endl;   // выход за границы
    }
    catch (const bad_range& e) {
        cerr << "Test 2 - Caught bad_range (expected): " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cerr << "Test 2 - Unexpected exception: " << e.what() << endl;
    }

    // Удаление по неверному индексу -> bad_range
    try {
        IntegerArray arr(3);
        arr.remove(5);
    }
    catch (const bad_range& e) {
        cerr << "Test 3 - Caught bad_range (expected): " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cerr << "Test 3 - Unexpected exception: " << e.what() << endl;
    }

    // Вставка по неверному индексу -> bad_range
    try {
        IntegerArray arr(2);
        arr.insertBefore(10, 3);   // допустимые индексы 0,1,2
    }
    catch (const bad_range& e) {
        cerr << "Test 4 - Caught bad_range (expected): " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cerr << "Test 4 - Unexpected exception: " << e.what() << endl;
    }

    // Изменение размера на отрицательный -> bad_length
    try {
        IntegerArray arr(3);
        arr.resize(-1);
    }
    catch (const bad_length& e) {
        cerr << "Test 5 - Caught bad_length (expected): " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cerr << "Test 5 - Unexpected exception: " << e.what() << endl;
    }

    //  Корректная работа и дополнительные функции
    try {
        IntegerArray arr(3);
        arr[0] = 10; arr[1] = 20; arr[2] = 30;
        cout << "\n--- Correct usage ---\n";
        cout << "Original array: ";
        for (int i = 0; i < arr.getLength(); ++i) cout << arr[i] << " ";
        cout << endl;

        // Копирование
        IntegerArray arrCopy = arr;
        cout << "Copied array:   ";
        for (int i = 0; i < arrCopy.getLength(); ++i) cout << arrCopy[i] << " ";
        cout << endl;

        // Вставка в конец и начало
        arr.push_back(40);
        arr.push_front(5);
        cout << "After push_back(40) and push_front(5): ";
        for (int i = 0; i < arr.getLength(); ++i) cout << arr[i] << " ";
        cout << endl;

        // Поиск элемента
        int* found = arr.find(20);
        if (found) {
            // Для демонстрации выведем найденное значение
            cout << "Found value 20 at address " << found << ", value = " << *found << endl;
        }
        else {
            cout << "Value 20 not found." << endl;
        }

        // Удаление элемента
        arr.remove(2);   // удаляем элемент с индексом 2
        cout << "After removing index 2: ";
        for (int i = 0; i < arr.getLength(); ++i) cout << arr[i] << " ";
        cout << endl;

        // Изменение размера
        arr.resize(2);
        cout << "After resize to 2: ";
        for (int i = 0; i < arr.getLength(); ++i) cout << arr[i] << " ";
        cout << endl;

        // Очистка
        arr.erase();
        cout << "After erase, length = " << arr.getLength() << endl;
    }
    catch (const std::exception& e) {
        cerr << "Unexpected exception in test 6: " << e.what() << endl;
    }

    return 0;
}