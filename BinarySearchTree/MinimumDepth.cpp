/*  This file contains driver code showcasing initialization, node removal, 
 *  printing, and calculation of minimum depth for a binary search tree. The
 *  minimum depth of a binary tree is defined as the number of nodes traversed
 *  in going from the root node to the closest leaf node. E.g., the minimum
 *  depth of this binary tree:
 *                        (root)
 *                      *       *
 *                  (1)          (2)
 *                 *   *        *   *
 *               (3)   (4)    (5)   (6)
 *              *   *  
 *            (7)   (8)     
 * 
 * is 2, and the path is: root->(2)->(5)->leaf.
 *
 * The implementation of the minimum depth algorithm is in the
 * BinarySearchTree.cpp file.
 */

#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
    BinarySearchTree binarySearchTree;

    // Initialize the binary search tree:
    binarySearchTree.insertNode(10);
    binarySearchTree.insertNode(1);
    binarySearchTree.insertNode(99);
    binarySearchTree.insertNode(-5);
    binarySearchTree.insertNode(8);
    binarySearchTree.insertNode(43);
    binarySearchTree.insertNode(10);
    binarySearchTree.insertNode(6);
    binarySearchTree.insertNode(77);
    binarySearchTree.insertNode(1000);

    cout << "Initial binary search tree:" << endl;
    binarySearchTree.printBinarySearchTree();
    cout << "The minium depth of this tree is: " 
         << binarySearchTree.minimumDepth() << endl << endl;

    int removeKey = 1;
    cout << "Removing node with key " << removeKey << ":" << endl;
    binarySearchTree.removeNode(removeKey);
    cout << "The new tree is:" << endl;
    binarySearchTree.printBinarySearchTree();
    cout << "The minimum depth of the new tree is: "
         << binarySearchTree.minimumDepth() << endl << endl;

    removeKey = 6;
    cout << "Removing node with key " << removeKey << ":" << endl;
    binarySearchTree.removeNode(removeKey);
    cout << "The new tree is:" << endl;
    binarySearchTree.printBinarySearchTree();
    cout << "The minimum depth of the new tree is: "
         << binarySearchTree.minimumDepth() << endl << endl;

    binarySearchTree.destroyBinarySearchTree();
}
