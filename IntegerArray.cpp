#include "IntegerArray.h"
#include <algorithm> 
#include <cstddef>   

IntegerArray::IntegerArray() : m_data(nullptr), m_length(0) {}

IntegerArray::IntegerArray(int length) : m_length(length) {
    if (length < 0) {
        throw bad_length("Array length cannot be negative. Requested length: " + std::to_string(length));
    }
    if (length > 0) {
        m_data = new int[static_cast<std::size_t>(length)] {}; 
    }
    else {
        m_data = nullptr;
    }
}

// Конструктор копирования (делегирует конструктору с длиной)
IntegerArray::IntegerArray(const IntegerArray& other) : IntegerArray(other.m_length) {
    if (m_length > 0) {
        std::copy_n(other.m_data, m_length, m_data);
    }
}

// Деструктор
IntegerArray::~IntegerArray() {
    delete[] m_data;
}

// Оператор присваивания
IntegerArray& IntegerArray::operator=(const IntegerArray& other) {
    if (this == &other) return *this; 

    reallocate(other.m_length);       
    if (m_length > 0) {
        std::copy_n(other.m_data, m_length, m_data);
    }
    return *this;
}

// Оператор доступа по индексу (неконстантный)
int& IntegerArray::operator[](int index) {
    if (index < 0 || index >= m_length) {
        throw bad_range("Index " + std::to_string(index) + " out of bounds. Array length is " + std::to_string(m_length));
    }
    return m_data[index];
}

// Оператор доступа по индексу (константный)
const int& IntegerArray::operator[](int index) const {
    if (index < 0 || index >= m_length) {
        throw bad_range("Index " + std::to_string(index) + " out of bounds. Array length is " + std::to_string(m_length));
    }
    return m_data[index];
}

// Возвращает длину
int IntegerArray::getLength() const {
    return m_length;
}

// Полная очистка массива
void IntegerArray::erase() {
    delete[] m_data;
    m_data = nullptr;
    m_length = 0;
}

// Быстрое изменение размера (старые данные теряются)
void IntegerArray::reallocate(int newLength) {
    if (newLength < 0) {
        throw bad_length("newLength cannot be negative in reallocate: " + std::to_string(newLength));
    }
    erase(); 
    if (newLength > 0) {
        m_data = new int[static_cast<std::size_t>(newLength)] {};
        m_length = newLength;
    }
}

// Изменение размера с сохранением существующих элементов
void IntegerArray::resize(int newLength) {
    if (newLength < 0) {
        throw bad_length("newLength cannot be negative in resize: " + std::to_string(newLength));
    }
    if (newLength == m_length) return;

    if (newLength == 0) {
        erase();
        return;
    }

    // Выделяем новый массив
    int* newData = new int[static_cast<std::size_t>(newLength)] {};

    // Копируем минимум из старого и нового размера
    int elementsToCopy = (newLength < m_length) ? newLength : m_length;
    if (elementsToCopy > 0) {
        std::copy_n(m_data, elementsToCopy, newData);
    }

    // Заменяем старый массив
    delete[] m_data;
    m_data = newData;
    m_length = newLength;
}

// Вставка элемента перед указанным индексом
void IntegerArray::insertBefore(int value, int index) {
    if (index < 0 || index > m_length) {
        throw bad_range("Invalid index for insertBefore: " + std::to_string(index) +
            ". Allowed range: 0.." + std::to_string(m_length));
    }

    // Создаём новый массив на один элемент больше
    int* newData = new int[static_cast<std::size_t>(m_length + 1)];

    // Копируем элементы до index
    if (index > 0) {
        std::copy_n(m_data, index, newData);
    }

    // Вставляем новый элемент
    newData[index] = value;

    // Копируем оставшиеся элементы после index
    if (m_length > index) {
        std::copy_n(m_data + index, m_length - index, newData + index + 1);
    }

    // Заменяем старый массив
    delete[] m_data;
    m_data = newData;
    ++m_length;
}

// Удаление элемента по индексу
void IntegerArray::remove(int index) {
    if (index < 0 || index >= m_length) {
        throw bad_range("Invalid index for remove: " + std::to_string(index) +
            ". Allowed range: 0.." + std::to_string(m_length - 1));
    }

    // Если удаляем последний элемент, просто очищаем массив
    if (m_length == 1) {
        erase();
        return;
    }

    // Создаём новый массив на один элемент меньше
    int* newData = new int[static_cast<std::size_t>(m_length - 1)];

    // Копируем элементы до index
    if (index > 0) {
        std::copy_n(m_data, index, newData);
    }

    // Копируем элементы после index
    if (m_length > index + 1) {
        std::copy_n(m_data + index + 1, m_length - index - 1, newData + index);
    }

    // Заменяем
    delete[] m_data;
    m_data = newData;
    --m_length;
}

// Вставка в конец
void IntegerArray::push_back(int value) {
    insertBefore(value, m_length);
}

// Вставка в начало
void IntegerArray::push_front(int value) {
    insertBefore(value, 0);
}

// Линейный поиск первого вхождения значения
int* IntegerArray::find(int value) {
    for (int i = 0; i < m_length; ++i) {
        if (m_data[i] == value) {
            return &m_data[i];
        }
    }
    return nullptr;
}