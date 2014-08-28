//Dat Do
//Assignment 6

#ifndef AVLTree_H
#define AVLTree_H

#include <iostream>
#include <string>
#include "TreeNode.h"
using namespace std;

template <typename KeyType, typename ElementType>

class AVLTree
{
    TreeNode<KeyType, ElementType> * root;

public:
    //constructor assigns 0 to root
    AVLTree() //O(1)
     : root(0) {}

    //destructor calls freetree
    ~AVLTree() //O(N)
    {
        if(root)
        {
            TreeNode<KeyType, ElementType>::freeTree(root);
        }
    }

    //insert calls TreeNode insert on root
    void insert(KeyType key, ElementType info) //O(log N)
    {
        TreeNode<KeyType, ElementType>::insert(key, info, root);
    }

    //finds key and returns info
    ElementType find(KeyType key) //O(log N)
    {
        TreeNode<KeyType, ElementType> * t = TreeNode<KeyType, ElementType>::find(key, root);

        if(!t)
        {
            insert(key, ElementType());
            t = TreeNode<KeyType, ElementType>::find(key, root);
        }
        return TreeNode<KeyType, ElementType>::returnInfo(t);
    }

    //removes specified key from tree
    void remove(KeyType key) //O(log N)
    {
        TreeNode<KeyType, ElementType>::remove(key, root);
    }

    //prints tree starting at root
    void print(ostream & out) //O(N)
    {
        TreeNode<KeyType, ElementType>::print(out, root);
        TreeNode<KeyType, ElementType>::displayCounter();
    }

    //returns reference to info of node with specified key
    ElementType & operator [] (KeyType key) //O(log N)
    {
        TreeNode<KeyType, ElementType> * t = TreeNode<KeyType, ElementType>::find(key, root);
        return TreeNode<KeyType, ElementType>::returnInfo(t);
    }
};

#endif
