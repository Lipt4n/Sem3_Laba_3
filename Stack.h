#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Stack {
    Array<T> a;
public:
    void push(T x) { a.push_back(x); }
    auto pop() {
        T res;
        if (a.length()) {
            res = a[a.length()-1];
            a.remove(a.length()-1);
        }
        return res;
    }
    void print() { a.print(); }
    bool empty() const { return a.length() == 0; }
    int size() const { return a.length(); }

    vector<T> to_vector() const {
        vector<T> result;
        for (int i = 0; i < a.length(); i++) {
            result.push_back(a[i]);
        }
        return result;
    }

    void from_vector(const vector<T>& data) {
        while (!empty()) pop();
        
        for (const auto& item : data) {
            push(item);
        }
    }

    void save_to_file(const string& filename) const {
        save_to_file_generic(filename, DataType::STACK, to_vector());
    }

    void load_from_file(const string& filename) {
        auto [type, data] = load_from_file_generic<T>(filename);
        if (type != DataType::STACK) {
            throw runtime_error("Неверный тип данных в файле");
        }
        from_vector(data);
    }
};