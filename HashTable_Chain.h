#pragma once
#include <iostream>
#include "Array.h"  
#include "SinglyList.h"

using namespace std;

template<typename T>
class HashTable {
    Array<SinglyList<T>> table;
    int cap;
    int sz;
    float load_factor_threshold = 0.75f;

    size_t hash(const T& key) const {
        return std::hash<T>{}(key) % cap;
    }

    void resize() {
        int new_cap = cap * 2;
        Array<SinglyList<T>> new_table;
        for (int i = 0; i < new_cap; ++i) {
            new_table.push_back(SinglyList<T>());
        }

        for (int i = 0; i < cap; ++i) {
            Node<T>* cur = table[i].get_head();
            while (cur) {
                size_t new_idx = std::hash<T>{}(cur->data) % new_cap;
                new_table[new_idx].push_back(cur->data);
                cur = cur->next;
            }
        }
        table = std::move(new_table);
        cap = new_cap;
    }

public:
    HashTable(int initial_cap = 16) : cap(initial_cap), sz(0) {
        for (int i = 0; i < cap; ++i) {
            table.push_back(SinglyList<T>());
        }
    }

    void insert(T key) {
        size_t idx = hash(key);
        if (!contains(key)) {
            table[idx].push_back(key);
            ++sz;
            if ((float)sz / cap > load_factor_threshold) {
                resize();
            }
        }
    }

    void remove(T key) {
        size_t idx = hash(key);
        if (table[idx].remove_value(key)) {
            --sz;
        }
    }

    bool contains(T key) {
        size_t idx = hash(key);
        return table[idx].find(key) != nullptr;
    }

    void print() {
        for (int i = 0; i < cap; ++i) {
            cout << "Bucket " << i << ": ";
            table[i].print();
        }
    }

    vector<T> to_vector() const {
        vector<T> result;
        for (int i = 0; i < cap; ++i) {
            Node<T>* cur = table[i].get_head();
            while (cur) {
                result.push_back(cur->data);
                cur = cur->next;
            }
        }
        return result;
    }

    void from_vector(const vector<T>& data) {
        for (int i = 0; i < cap; ++i) {
            table[i] = SinglyList<T>();
        }
        sz = 0;
        
        for (const auto& item : data) {
            insert(item);
        }
    }

    void save_to_file(const string& filename) const {
        save_to_file_generic(filename, DataType::HASH_TABLE, to_vector());
    }

    void load_from_file(const string& filename) {
        auto [type, data] = load_from_file_generic<T>(filename);
        if (type != DataType::HASH_TABLE) {
            throw runtime_error("Неверный тип данных в файле");
        }
        from_vector(data);
    }
};