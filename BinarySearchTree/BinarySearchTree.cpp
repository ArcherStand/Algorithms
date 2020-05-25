/*  File: BinarySearchTree.cpp
 *  This file contains the implementation of the BinarySearchTree class.
 */

#include <cstddef>
#include <iostream>
#include <queue>
#include "BinarySearchTree.h"

using namespace std;

////
//// Public Functions:
////

BinarySearchTree::BinarySearchTree()
{
    m_root = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
    destroyBinarySearchTree();
}

// Public Function: insertNode
// Input: key - Integer key to be added to the tree.
// Output: None.
void BinarySearchTree::insertNode(int key)
{
    m_root = insertNode(key, m_root);
}

// Public Function: removeNode
// Input: key - Integer indicating which node to remove.
// Output: None.
void BinarySearchTree::removeNode(int key)
{
    m_root = removeNode(key, m_root);
}

// Public Function: constainsNode
// Input: key - The integer to search for in the tree.
// Output: Returns true if the tree contains a node whose key matches the input
//          key, otherwise returns false.
bool BinarySearchTree::containsNode(int key)
{
    Node *node = findNode(key, m_root);

    if (node != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Public Function: minimumDepth
// Input: None.
// Output: The number of nodes encountered on the shortest path to a leaf node.
int BinarySearchTree::minimumDepth()
{
    return minimumDepth(m_root);
}

// Public Function: printBinarySearchTree
// Input: None.
// Output: Non-graphical printing of the nodes of the tree in a breadth-first
//          order.
void BinarySearchTree::printBinarySearchTree()
{
    cout << "Breadth-first traversal of binary search tree:" << endl;
    printBinarySearchTree(m_root);
    cout << endl;
}

// Public Function: destroyBinarySearchTree
// Input: none
// Output: none
// This function destroys the entire binary tree.
void BinarySearchTree::destroyBinarySearchTree()
{
    destroyBinarySearchTree(m_root);
    m_root = NULL;
}


////
//// Private functions:
////

// Private Function: insertNode
// Input: key - Integer key to be added to the tree.
//        node - The current node we are checking.
// Output: Returns a pointer to the new root of the subtree after the tree has
// been altered by inserting the node.
Node *BinarySearchTree::insertNode(int key, Node *node)
{
    if (node != NULL)
    {
        // Smaller values go to the left child:
        if (key < node->key)
        {
            node->left = insertNode(key, node->left);
        }
        // Larger values go to the right child:
        else if (key > node-> key)
        {
            node->right = insertNode(key, node->right);
        }
        // Otherwise this node already contains the key:
        else
        {
            // Nothing to do
        }

        return node;
    }
    // If we reach here then no node in the tree contains the key and the
    // current node is a leaf node so we may insert the key:
    else
    {
        node = new Node;
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        
        return node;
    }
}

// Private Function: removeNode
// Input: key - Integer key to be removed from the tree.
//        node - The current node we are checking.
// Output: Returns a pointer to the new root of the subtree after the tree has
// been altered by removing the node.
Node *BinarySearchTree::removeNode(int key, Node *node)
{
    if (node != NULL)
    {
        // Smaller values are in the left child:
        if (key < node->key)
        {
            node->left = removeNode(key, node->left);
        }
        // Larger values are in the right child:
        else if (key > node-> key)
        {
            node->right = removeNode(key, node->right);
        }
        // Otherwise this node contains the key to be removed:
        else
        {
            // First try to replace the node with it's right successor:
            if (node->right != NULL)
            {
                Node *successor = findSmallestNode(node->right);
                node->key = successor->key;
                node->right = removeNode(successor->key, node->right);
            }
            // If no right subtree, try to replace the node with it's left
            // predecessor:
            else if (node->left != NULL)
            {
                Node *predecessor = findLargestNode(node->left);
                node->key = predecessor->key;
                node->left = removeNode(predecessor->key, node->left);
            }
            // If no left or right subtree then this node is the one to remove:
            else
            {
                delete node;
                node = NULL;
            }
        }
    }

    // Return the root of the updated subtree:
    return node;
}

// Private Function: findSmallestNode
// Input: node - The root of the subtree to search for the node with the
//                smallest key.
// Output: Returns a pointer to the node with the smallest key within the
//          subtree whose rood is the input node.
// Since this is a binary search tree, the smallest node is always the
//  left-most child node in the subtree.
Node *BinarySearchTree::findSmallestNode(Node *node)
{
    Node *currentNode = node;

    if (currentNode != NULL)
    {
        while (currentNode->left != NULL)
        {
            currentNode = currentNode->left;
        }
    }

    return currentNode;
}

// Private Function: findLargestNode
// Input: node - The root of the subtree to search for the node with the
//                largest key.
// Output: Returns a pointer to the node with the largest key within the
//          subtree whose rood is the input node.
// Since this is a binary search tree, the largest node is always the
//  right-most child node in the subtree.
Node *BinarySearchTree::findLargestNode(Node *node)
{
    Node *currentNode = node;

    if (currentNode != NULL)
    {
        while(currentNode->right != NULL)
        {
            currentNode = currentNode->right;
        }
    }

    return currentNode;
}

// Private Function: findNode
// Input: key - Integer indicating the node to search for.
//        node - the root of the current subtree we are searching.
// Output: If the tree contains a node whose key matches the input key then
//          this will return a pointer to that node. Otherwise it returns NULL.
Node *BinarySearchTree::findNode(int key, Node *node)
{
    if (node != NULL)
    {
        if (key = node->key)
        {
            return node;
        }
        else if (key < node->key)
        {
            return findNode(key, node->left);
        }
        else
        {
            return findNode(key, node->right);
        }
    }
    else
    {
        return NULL;
    }
}

// Private Function: minimumDepth
// Input: root - The root node of the tree.
// Output: Returns the number of nodes traversed along the shortest path to a
// leaf node.
int BinarySearchTree::minimumDepth(Node *root)
{
    queue<Node *> nodeQueue;
    queue<int> depthQueue; // Kept in sync with nodeQueue for tracking depth.
    int currentDepth = 0;

    nodeQueue.push(root);
    depthQueue.push(currentDepth);

    while (!nodeQueue.empty())
    {
        // The first time we find a leaf node, return the current depth:
        if (nodeQueue.front() == NULL)
        {
            return depthQueue.front();
        }
        else
        {
            Node *currentNode = nodeQueue.front();
            int currentDepth = depthQueue.front();

            nodeQueue.pop();
            depthQueue.pop();

            nodeQueue.push(currentNode->left);
            depthQueue.push(currentDepth+1);
            nodeQueue.push(currentNode->right);
            depthQueue.push(currentDepth+1);
        }
    }
}

// Private Function: printBinarySearchTree
// Input: root - the root node of the binary search tree to print.
// Output: Non-graphical printing of the nodes of the tree in a breadth-first
//          order.
// A queue of nodes is utilized to print all children nodes before
// grand-children.
void BinarySearchTree::printBinarySearchTree(Node *root)
{
    queue<Node *> nodeQueue;

    nodeQueue.push(root);

    while (!nodeQueue.empty())
    {
        if (nodeQueue.front() != NULL)
        {
            Node *currentNode = nodeQueue.front();

            cout << currentNode->key << " ";
            nodeQueue.push(currentNode->left);
            nodeQueue.push(currentNode->right);
        }

        nodeQueue.pop();
    }
}

void BinarySearchTree::destroyBinarySearchTree(Node *node)
{
    if (node != NULL)
    {
        destroyBinarySearchTree(node->left);
        destroyBinarySearchTree(node->right);
        delete node;
    }
}
