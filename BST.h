#pragma once
#include <iostream>

using namespace std;

template<typename T>
struct TreeNode {
    T data;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode(T v) : data(v) {}
};

template<typename T>
class BST {
    TreeNode<T>* root = nullptr;

    TreeNode<T>* insert(TreeNode<T>* node, T val) {
        if (!node) return new TreeNode<T>(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }
    TreeNode<T>* min(TreeNode<T>* node) {
        while (node->left) node = node->left;
        return node;
    }
    TreeNode<T>* remove(TreeNode<T>* node, T val) {
        if (!node) return nullptr;
        if (val < node->data) node->left = remove(node->left, val);
        else if (val > node->data) node->right = remove(node->right, val);
        else {
            if (!node->left) { TreeNode<T>* t = node->right; delete node; return t; }
            if (!node->right) { TreeNode<T>* t = node->left; delete node; return t; }
            TreeNode<T>* t = min(node->right);
            node->data = t->data;
            node->right = remove(node->right, t->data);
        }
        return node;
    }
    void inorder(TreeNode<T>* node) {
        if (node) { inorder(node->left); cout << node->data << " "; inorder(node->right); }
    }
    void clear(TreeNode<T>* node) {
        if (node) { clear(node->left); clear(node->right); delete node; }
    }
    void collect_inorder(TreeNode<T>* node, vector<T>& result) const {
        if (node) {
            collect_inorder(node->left, result);
            result.push_back(node->data);
            collect_inorder(node->right, result);
        }
    }

    void build_from_sorted(const vector<T>& sorted_data, int start, int end) {
        if (start > end) return;
        
        int mid = start + (end - start) / 2;
        insert(sorted_data[mid]);
        build_from_sorted(sorted_data, start, mid - 1);
        build_from_sorted(sorted_data, mid + 1, end);
    }
public:
    void insert(T x) { root = insert(root, x); }
    void remove(T x) { root = remove(root, x); }
    bool find(T x) {
        TreeNode<T>* cur = root;
        while (cur) {
            if (x == cur->data) return true;
            cur = (x < cur->data) ? cur->left : cur->right;
        }
        return false;
    }
    void print() { inorder(root); cout << endl; }
    ~BST() { clear(root); }

    vector<T> to_vector() const {
        vector<T> result;
        collect_inorder(root, result);
        return result;
    }

    void from_vector(const vector<T>& data) {
        clear(root);
        root = nullptr;
        
        vector<T> sorted_data = data;
        sort(sorted_data.begin(), sorted_data.end());
        
        build_from_sorted(sorted_data, 0, sorted_data.size() - 1);
    }

    void save_to_file(const string& filename) const {
        save_to_file_generic(filename, DataType::BST, to_vector());
    }

    void load_from_file(const string& filename) {
        auto [type, data] = load_from_file_generic<T>(filename);
        if (type != DataType::BST) {
            throw runtime_error("Неверный тип данных в файле");
        }
        from_vector(data);
    }
};