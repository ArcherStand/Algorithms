/*  File BinaryTree.h
 *  This file contains the declaration of the Node structure and
 *  BinarySearchTree class.
 *  A binary search tree is a collection of nodes. Each node contains a key
 *  value and pointers to two child nodes called 'left' and 'right'. The tree
 *  has no duplicate keys, and every nodes left child contains keys smaller
 *  than the node, and right child contains keys larger than the node.
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

using namespace std;

// Data Structure: Node
struct Node
{
    int key;
    Node *left;
    Node *right;
};

// Data Structure: Binary Tree
class BinarySearchTree
{
    public:
        BinarySearchTree();
        ~BinarySearchTree();

        void insertNode(int key);
        void removeNode(int key); 
        bool containsNode(int key);
        int minimumDepth();
        void printBinarySearchTree();
        void destroyBinarySearchTree();

    private:
        Node *insertNode(int key, Node *node);
        Node *removeNode(int key, Node *node);
        Node *findSmallestNode(Node *node);
        Node *findLargestNode(Node *node);
        Node *findNode(int key, Node *node);
        int minimumDepth(Node *node);
        void printBinarySearchTree(Node *node);
        void destroyBinarySearchTree(Node* node);

        Node *m_root;
};

#endif // BINARY_SEARCH_TREE_H
