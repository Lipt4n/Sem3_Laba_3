#pragma once
#include <iostream>

using namespace std;

template<typename T>
class DoublyList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int len = 0;
public:
    ~DoublyList() { while(head) { Node<T>* t = head; head = head->next; delete t; } }

    void push_front(T x) {
        Node<T>* n = new Node<T>(x);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
        len++;
    }
    void push_back(T x) {
        Node<T>* n = new Node<T>(x);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = n;
        len++;
    }
    void insert_after(Node<T>* p, T x) {
        if (!p) return;
        Node<T>* n = new Node<T>(x);
        n->next = p->next; n->prev = p;
        if (p->next) p->next->prev = n;
        p->next = n;
        if (p == tail) tail = n;
        len++;
    }
    void insert_before(Node<T>* p, T x) {
        if (!p) return;
        if (p == head) return push_front(x);
        insert_after(p->prev, x);
    }
    void remove(Node<T>* p) {
        if (!p) return;
        if (p->prev) p->prev->next = p->next;
        if (p->next) p->next->prev = p->prev;
        if (head == p) head = p->next;
        if (tail == p) tail = p->prev;
        delete p;
        len--;
    }
    bool remove_value(T x) {
        for (Node<T>* p = head; p; p = p->next)
            if (p->data == x) { remove(p); return true; }
        return false;
    }
    auto pop_front() {
        if (!head) return T();
        Node<T>* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        T res = temp->data;
        delete temp;
        len--;
        return res;
    }
    void pop_back() {
        if (!tail) return;
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        len--;
    }       
    void remove_before(Node<T>* pos) {
        if (!pos || !pos->prev) return;
        Node<T>* to_delete = pos->prev;
        if (to_delete->prev) {
            to_delete->prev->next = pos;
        }
        pos->prev = to_delete->prev;
        if (to_delete == head) {
            head = pos;
        }
        delete to_delete;
        len--;
    }
    void remove_after(Node<T>* pos) {
        if (!pos || !pos->next) return;
        Node<T>* to_delete = pos->next;
        pos->next = to_delete->next;
        if (to_delete->next) {
            to_delete->next->prev = pos;
        }
        if (to_delete == tail) {
            tail = pos;
        }
        delete to_delete;
        len--;
    }
    Node<T>* find(T x) {
        for (Node<T>* p = head; p; p = p->next)
            if (p->data == x) return p;
        return nullptr;
    }
    void print() const {
        for (Node<T>* p = head; p; p = p->next) cout << p->data << " <-> ";
        cout << "null\n";
    }
    int length() const { return len; }

    vector<T> to_vector() const {
        vector<T> result;
        Node<T>* cur = head;
        while (cur) {
            result.push_back(cur->data);
            cur = cur->next;
        }
        return result;
    }

    void from_vector(const vector<T>& data) {
        while(head) { Node<T>* t = head; head = head->next; delete t; }
        head = tail = nullptr;
        len = 0;
        
        for (const auto& item : data) {
            push_back(item);
        }
    }

    void save_to_file(const string& filename) const {
        save_to_file_generic(filename, DataType::DOUBLY_LIST, to_vector());
    }

    void load_from_file(const string& filename) {
        auto [type, data] = load_from_file_generic<T>(filename);
        if (type != DataType::DOUBLY_LIST) {
            throw runtime_error("Неверный тип данных в файле");
        }
        from_vector(data);
    }
};