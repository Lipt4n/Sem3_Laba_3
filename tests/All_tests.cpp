#include <gtest/gtest.h>
#include "../Array.h"
#include "../SinglyList.h"
#include "../DoublyList.h"
#include "../Stack.h"
#include "../Queue.h"
#include "../BST.h"
#include "../HashTable_Chain.h"

// ===================== ARRAY =====================
TEST(ArrayTest, InitialEmpty) {
    Array<int> a;
    EXPECT_EQ(a.length(), 0);
}

TEST(ArrayTest, PushBackAndAccess) {
    Array<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    EXPECT_EQ(a.length(), 3);
    EXPECT_EQ(a[0], 10);
    EXPECT_EQ(a[1], 20);
    EXPECT_EQ(a[2], 30);
}

TEST(ArrayTest, PopBack) {
    Array<int> a;
    a.push_back(999);
    a.push_back(888);
    a.pop_back();
    EXPECT_EQ(a.length(), 1);
    EXPECT_EQ(a[0], 999);
}

TEST(ArrayTest, InsertAndRemove) {
    Array<int> a;
    a.push_back(1);
    a.push_back(3);
    a.insert(1, 2);  // 1 2 3
    EXPECT_EQ(a.length(), 3);
    EXPECT_EQ(a[1], 2);
    a.remove(0);     // 2 3
    EXPECT_EQ(a.length(), 2);
    EXPECT_EQ(a[0], 2);
    a.remove(1);     // 2
    EXPECT_EQ(a.length(), 1);
}

TEST(ArrayTest, Replace) {
    Array<int> a;
    a.push_back(100);
    a.replace(0, 555);
    EXPECT_EQ(a[0], 555);
}

TEST(ArrayTest, GrowCapacity) {
    Array<int> a;
    for (int i = 0; i < 1000; ++i) {
        a.push_back(i);
    }
    EXPECT_EQ(a.length(), 1000);
    EXPECT_EQ(a[999], 999);
}

// ===================== SINGLY LIST =====================
TEST(SinglyListTest, PushFrontBack) {
    SinglyList<int> s;
    s.push_back(20);
    s.push_front(10);
    s.push_back(30);
    EXPECT_EQ(s.length(), 3);
}

TEST(SinglyListTest, InsertAfterBefore) {
    SinglyList<int> s;
    s.push_back(2);
    Node<int>* n = s.find(2);
    s.insert_after(n, 3);
    s.insert_before(n, 1);
    EXPECT_EQ(s.length(), 3);
}

TEST(SinglyListTest, RemoveOperations) {
    SinglyList<int> s;
    s.push_back(1); s.push_back(2); s.push_back(3);
    s.pop_front();  // 2 3
    s.pop_back();   // 2
    EXPECT_EQ(s.length(), 1);
    s.push_back(3); s.push_back(4);
    Node<int>* n = s.find(3);
    s.remove_after(n);  // удалит 4
    EXPECT_EQ(s.length(), 2);
}

TEST(SinglyListTest, RemoveValue) {
    SinglyList<int> s;
    s.push_back(10); s.push_back(20); s.push_back(10);
    EXPECT_TRUE(s.remove_value(10));
    EXPECT_TRUE(s.remove_value(10));
    EXPECT_FALSE(s.remove_value(999));
    EXPECT_EQ(s.length(), 1);
}

// ===================== DOUBLY LIST =====================
TEST(DoublyListTest, PushFrontBack) {
    DoublyList<int> d;
    d.push_front(10);
    d.push_back(20);
    EXPECT_EQ(d.length(), 2);
}

TEST(DoublyListTest, InsertAfterBefore) {
    DoublyList<int> d;
    d.push_back(2);
    Node<int>* n = d.find(2);
    d.insert_after(n, 3);
    d.insert_before(n, 1);
    EXPECT_EQ(d.length(), 3);
}

TEST(DoublyListTest, PopAndRemove) {
    DoublyList<int> d;
    d.push_back(1); d.push_back(2); d.push_back(3);
    d.pop_front();  // 2 3
    d.pop_back();   // 2
    d.push_back(3); d.push_back(4);
    d.remove_value(3);
    EXPECT_EQ(d.length(), 2);
}

TEST(DoublyListTest, RemoveBeforeAfter) {
    DoublyList<int> d;
    d.push_back(1); d.push_back(2); d.push_back(3); d.push_back(4);
    Node<int>* pos = d.find(3);
    d.remove_before(pos);  // удалит 2
    d.remove_after(pos);   // удалит 4
    EXPECT_EQ(d.length(), 2);
}

// ===================== STACK =====================
TEST(StackTest, PushPop) {
    Stack<int> st;
    st.push(10);
    st.push(20);
    EXPECT_EQ(st.size(), 2);
    EXPECT_EQ(st.pop(), 20);
    EXPECT_EQ(st.pop(), 10);
    EXPECT_TRUE(st.empty());
}

// ===================== QUEUE =====================
TEST(QueueTest, PushPop) {
    Queue<int> q;
    q.push(10);
    q.push(20);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.pop(), 10);
    EXPECT_EQ(q.pop(), 20);
    EXPECT_TRUE(q.empty());
}

// ===================== BST =====================
TEST(BSTTest, InsertAndFind) {
    BST<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    EXPECT_TRUE(tree.find(30));
    EXPECT_TRUE(tree.find(70));
    EXPECT_FALSE(tree.find(999));
}

TEST(BSTTest, RemoveLeaf) {
    BST<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.remove(30);
    EXPECT_FALSE(tree.find(30));
}

TEST(BSTTest, RemoveOneChild) {
    BST<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.remove(30);  // 20 заменит 30
    EXPECT_FALSE(tree.find(30));
    EXPECT_TRUE(tree.find(20));
}

TEST(BSTTest, RemoveTwoChildren) {
    BST<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.remove(50);
    EXPECT_FALSE(tree.find(50));
}

// ===================== HASH TABLE =====================
TEST(HashTableTest, InsertContainsRemove) {
    HashTable<int> ht(8);
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    EXPECT_TRUE(ht.contains(20));
    ht.remove(20);
    EXPECT_FALSE(ht.contains(20));
}

TEST(HashTableTest, NoDuplicates) {
    HashTable<int> ht;
    ht.insert(42);
    ht.insert(42);
}

TEST(HashTableTest, ResizeOnLoadFactor) {
    HashTable<int> ht(4); 
    for (int i = 0; i < 10; ++i) {
        ht.insert(i * 10);
    }
    EXPECT_TRUE(ht.contains(0));
    EXPECT_TRUE(ht.contains(90));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}