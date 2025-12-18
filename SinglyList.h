#pragma once
#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template<typename T>
class SinglyList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int len = 0;

    void del(Node<T>* n) { delete n; }
public:
    ~SinglyList() { while(head) pop_front(); }

    void push_front(T x) {
        Node<T>* n = new Node<T>(x);
        n->next = head;
        head = n;
        if (!tail) tail = n;
        len++;
    }
    void push_back(T x) {
        Node<T>* n = new Node<T>(x);
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = tail;
        len++;
    }
    void insert_after(Node<T>* pos, T x) {
        if (!pos) return;
        Node<T>* n = new Node<T>(x);
        n->next = pos->next;
        pos->next = n;
        if (tail == pos) tail = n;
        len++;
    }
    void insert_before(Node<T>* pos, T x) {
        if (!pos) return;
        if (pos == head) return push_front(x);
        Node<T>* cur = head;
        while (cur && cur->next != pos) cur = cur->next;
        if (cur) insert_after(cur, x);
    }

    void pop_front() {
        if (!head) return;
        Node<T>* t = head;
        head = head->next;
        del(t);
        if (!head) tail = nullptr;
        len--;
    }
    void pop_back() {
        if (!head) return;
        if (head == tail) { pop_front(); return; }
        Node<T>* cur = head;
        while (cur->next != tail) cur = cur->next;
        del(tail);
        tail = cur;
        tail->next = nullptr;
        len--;
    }
    void remove_before(Node<T>* pos) {
        if (!pos || !head || pos == head) return;
        if (pos == head->next) return pop_front();
        Node<T>* cur = head;
        while(cur && cur->next != pos) cur = cur->next;
        if (cur && cur->next && cur->next->next == pos) {
            Node<T>* to_delete = cur->next;
            cur->next = to_delete->next;
            delete to_delete;
            len--;
            if (to_delete == tail) {
                tail = cur;
            }
        }
    }
    void remove_after(Node<T>* pos) {
        if (!pos || !pos->next) return;
        Node<T>* to_delete = pos->next;
        pos->next = to_delete->next;
        if (to_delete == tail) {
            tail = pos;
        }
        delete to_delete;
        len--;
    }

    Node<T>* find(T x) {
        Node<T>* cur = head;
        while (cur && cur->data != x) cur = cur->next;
        return cur;
    }
    bool remove_value(T x) {
        if (!head) return false;
        if (head->data == x) { pop_front(); return true; }
        Node<T>* cur = head;
        while (cur->next && cur->next->data != x) cur = cur->next;
        if (cur->next) {
            Node<T>* t = cur->next;
            cur->next = t->next;
            if (t == tail) tail = cur;
            del(t);
            len--;
            return true;
        }
        return false;
    }
    void print() const {
        for (Node<T>* p = head; p; p = p->next) cout << p->data << " -> ";
        cout << "null" << endl;
    }
    int length() const { return len; }
    Node<T>* get_head() const { return head; }

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
        while(head) pop_front();
        
        for (const auto& item : data) {
            push_back(item);
        }
    }

    void save_to_file(const string& filename) const {
        save_to_file_generic(filename, DataType::SINGLY_LIST, to_vector());
    }

    void load_from_file(const string& filename) {
        auto [type, data] = load_from_file_generic<T>(filename);
        if (type != DataType::SINGLY_LIST) {
            throw runtime_error("Неверный тип данных в файле");
        }
        from_vector(data);
    }
};