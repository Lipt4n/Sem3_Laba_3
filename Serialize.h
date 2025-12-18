#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

enum class DataType {
    ARRAY,
    SINGLY_LIST,
    DOUBLY_LIST,
    STACK,
    QUEUE,
    BST,
    HASH_TABLE
};

template<typename T>
void save_to_file_generic(const string& filename, DataType type, const vector<T>& data) {
    ofstream file(filename, ios::binary);
    if (!file) throw runtime_error("Не удалось открыть файл для записи");
    
    int type_int = static_cast<int>(type);
    file.write(reinterpret_cast<const char*>(&type_int), sizeof(int));
    
    size_t count = data.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(size_t));
    
    for (const auto& item : data) {
        file.write(reinterpret_cast<const char*>(&item), sizeof(T));
    }

    file.close();
}

template<typename T>
pair<DataType, vector<T>> load_from_file_generic(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) throw runtime_error("Не удалось открыть файл для чтения");
    
    int type_int;
    file.read(reinterpret_cast<char*>(&type_int), sizeof(int));
    DataType type = static_cast<DataType>(type_int);
    
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(size_t));
    
    vector<T> data(count);
    for (size_t i = 0; i < count; ++i) {
        file.read(reinterpret_cast<char*>(&data[i]), sizeof(T));
    }
    
    file.close();
    return {type, data};
}