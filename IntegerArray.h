#ifndef INTEGERARRAY_H
#define INTEGERARRAY_H

#include <exception>
#include <string>

// Исключение: выход за границы массива
class bad_range : public std::exception {
private:
    std::string msg;
public:
    bad_range(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

// Исключение: недопустимая длина массива
class bad_length : public std::exception {
private:
    std::string msg;
public:
    bad_length(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class IntegerArray {
private:
    int* m_data;      // указатель на динамический массив
    int m_length;     // текущая длина

public:
    // Конструкторы / деструктор
    IntegerArray();
    explicit IntegerArray(int length);    
    IntegerArray(const IntegerArray& other);
    ~IntegerArray();

    // Операторы
    IntegerArray& operator=(const IntegerArray& other);
    int& operator[](int index);          
    const int& operator[](int index) const; 

    // Основные методы
    int getLength() const;
    void erase();                        
    void resize(int newLength);           
    void reallocate(int newLength);        
    void insertBefore(int value, int index); 
    void remove(int index);                

    // Дополнительные методы (для дополнительного балла)
    void push_back(int value);            
    void push_front(int value);          
    int* find(int value);                  
};

#endif

