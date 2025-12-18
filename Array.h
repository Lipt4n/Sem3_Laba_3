#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Array {
    T* arr;
    int size, cap;
    void grow() {
        cap = cap ? cap * 2 : 8;
        T* newarr = new T[cap];
        for (int i = 0; i < size; i++) newarr[i] = arr[i];
        delete[] arr;
        arr = newarr;
    }
public:
    Array() : arr(nullptr), size(0), cap(0) {}
    ~Array() { delete[] arr; }

    void push_back(T x) {
        if (size == cap) grow();
        arr[size++] = x;
    }
    void pop_back() {
        if (size > 0) {
            size--;
            arr[size] = T();
        }
    }
    void insert(int idx, T x) {
        if (idx < 0 || idx > size) throw "Некорректный индекс!";
        if (size == cap) grow();
        for (int i = size; i > idx; i--) arr[i] = arr[i-1];
        arr[idx] = x;
        size++;
    }
    void remove(int idx) {
        if (idx < 0 || idx >= size) throw "Некорректный индекс!";
        for (int i = idx; i < size-1; i++) arr[i] = arr[i+1];
        size--;
    }
    void replace(int idx, T x) {
        if (idx < 0 || idx >= size) throw "Некорректный индекс!";
        arr[idx] = x;
    }
    T& operator[](int i) { return arr[i]; }
    int length() const { return size; }
    void print() const { for (int i = 0; i < size; i++) cout << arr[i] << ' '; cout << endl; }
    
    vector<T> to_vector() const {
        vector<T> result;
        for (int i = 0; i < size; i++) {
            result.push_back(arr[i]);
        }
        return result;
    }

    void from_vector(const vector<T>& data) {
        delete[] arr;
        size = data.size();
        cap = max(size, 8);
        arr = new T[cap];
        
        for (int i = 0; i < size; i++) {
            arr[i] = data[i];
        }
    }

    void save_to_file(const string& filename) const {
        save_to_file_generic(filename, DataType::ARRAY, to_vector());
    }

    void load_from_file(const string& filename) {
        auto [type, data] = load_from_file_generic<T>(filename);
        if (type != DataType::ARRAY) {
            throw runtime_error("Неверный тип данных в файле");
        }
        from_vector(data);
    }
};