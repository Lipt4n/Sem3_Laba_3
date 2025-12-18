#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Queue {
    DoublyList<T> list;
public:
    void push(T x) { list.push_back(x); }
    auto pop() {
        T res;
        if (list.length()) {
            res = list.pop_front();
        }
        return res;
    }
    void print() { return list.print(); }
    bool empty() const { return list.length() == 0; }
    int size() const { return list.length(); }

    vector<T> to_vector() const {
        vector<T> result;
        Queue<T> temp = *this;
        
        while (!temp.empty()) {
            result.push_back(temp.pop());
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
        save_to_file_generic(filename, DataType::QUEUE, to_vector());
    }

    void load_from_file(const string& filename) {
        auto [type, data] = load_from_file_generic<T>(filename);
        if (type != DataType::QUEUE) {
            throw runtime_error("Неверный тип данных в файле");
        }
        from_vector(data);
    }
};
