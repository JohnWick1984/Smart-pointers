// Smart pointers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<iostream>
using namespace std;


template <typename T>
class MyUniquePtr 
{
private:
    T* ptr;

public:
   
    MyUniquePtr() : ptr(nullptr) {}
    MyUniquePtr(T* p) : ptr(p) {}
    ~MyUniquePtr() 
    {
        if (ptr)
        {
            delete ptr;
        }
    }

   
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }

    // Запрет копирования и присваивания
    MyUniquePtr(const MyUniquePtr&) = delete;
    MyUniquePtr& operator=(const MyUniquePtr&) = delete;

    // Перемещение ресурсов
    MyUniquePtr(MyUniquePtr&& other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }
    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept 
    {
        if (this != &other) 
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
};


template <typename T>
class MySharedPtr 
{
private:
    T* ptr;
    int* refCount;

public:
    MySharedPtr() : ptr(nullptr), refCount(nullptr) {}
    MySharedPtr(T* p) : ptr(p), refCount(new int(1)) {}
    ~MySharedPtr() 
    {
        if (ptr) 
        {
            if (--(*refCount) == 0) 
            {
                delete ptr;
                delete refCount;
            }
        }
    }

    // Копирующий конструктор и оператор присваивания
    MySharedPtr(const MySharedPtr& other) : ptr(other.ptr), refCount(other.refCount) 
    {
        if (refCount) 
        {
            (*refCount)++;
        }
    }
    MySharedPtr& operator=(const MySharedPtr& other) 
    {
        if (this != &other) 
        {
           
            if (ptr && --(*refCount) == 0) 
            {
                delete ptr;
                delete refCount;
            }

            
            ptr = other.ptr;
            refCount = other.refCount;

            
            if (refCount) 
            {
                (*refCount)++;
            }
        }
        return *this;
    }

   
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }
};



int main() 

{
    // Тестирование MyUniquePtr
    MyUniquePtr<int> uniquePtr(new int(42));
    cout << *uniquePtr << endl;

    // MyUniquePtr не поддерживает копирование
    // MyUniquePtr<int> copyUniquePtr = uniquePtr; // Ошибка компиляции

    // Тестирование MySharedPtr
    MySharedPtr<int> sharedPtr1(new int(42));
    MySharedPtr<int> sharedPtr2 = sharedPtr1;
    cout << *sharedPtr1 << " " << *sharedPtr2 << endl;

    return 0;
}
