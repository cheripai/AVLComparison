//Dat Do
//Assignment 6

#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//for keeping track of new & delete
static int nodesCreated = 0;

template <typename KeyType, typename ElementType>

class TreeNode
{
    KeyType key;
    ElementType info;
    TreeNode * left, * right;
    int height;

    //returns the left subtree's right most child
    static TreeNode * findPred(KeyType key, TreeNode * t) //O(N)
    {
    TreeNode * curr = t;

    if(curr != 0 && curr->key == key)
    {
        if(curr->left != 0)
            curr = curr->left;

        while(curr->right != 0)
            curr = curr->right;
    }

    else if(curr && curr->key != key) //if predecessor is above key
    {
        while(curr)
        {
            if(curr->right)
                if(curr->right->key == key)
                    return curr;

            if(curr->left)
                if(curr->left->key == key)
                    return curr;

            if(key < curr->key)
                curr = curr->left;
            else if(key > curr->key)
                curr = curr->right;
        }
        return 0;
    }

    return curr;
    }

    //swaps key and info of the given tree nodes
    static void swapKeyAndInfo(TreeNode * a, TreeNode * b) //O(1)
    {
        TreeNode * temp = new TreeNode(a->key, a->info, 0, 0);

        a->key = b->key;
        a->info = b->info;

        b->key = temp->key;
        b->info = temp->info;

        delete temp;
    }
    
    static int getBalance(TreeNode * t) //O(1)
    {
		if(t == 0)
			return 0;
		return returnHeight(t->left) - returnHeight(t->right);
	}

    //rotates binary tree node with left child
    static TreeNode * rotateWithLeftChild(TreeNode * &t) //O(1)
    {
        TreeNode * t1 = t->left;
        t->left = t1->right;
        t1->right = t;
        t->height = max(returnHeight(t->left), returnHeight(t->right)) + 1;
        t1->height = max(returnHeight(t1->left), returnHeight(t1->right)) + 1;
        t = t1;
        return t;
    }

    //rotates binary tree node with right child
    static TreeNode * rotateWithRightChild(TreeNode * &t) //O(1)
    {
        TreeNode * t1 = t->right;
        t->right = t1->left;
        t1->left = t;
        t->height = max(returnHeight(t->left), returnHeight(t->right)) + 1;
        t1->height = max(returnHeight(t1->left), returnHeight(t1->right)) + 1;
        t = t1;
        return t;
    }

    //double rotates binary tree node: first left child with its right child
    //then t with the new left child
    static void doubleWithLeftChild(TreeNode * &t) //O(1)
    {
        rotateWithRightChild(t->left);
        rotateWithLeftChild(t);
    }

    //double rotates binary tree node: first right child with its left child
    //then t with the new right child
    static void doubleWithRightChild(TreeNode * &t) //O(1)
    {
        rotateWithLeftChild(t->right);
        rotateWithRightChild(t);
    }

public:
    //constructor intializes values for TreeNode
    TreeNode(KeyType newKey, ElementType newInfo, TreeNode *l, TreeNode *r) //O(1)
    : key(newKey), info(newInfo), left(l), right(r), height(0) {}

    //creates a new tree node using the constructor
    static TreeNode * make(KeyType k, ElementType e, TreeNode * l, TreeNode * r) //O(1)
    {
        ++nodesCreated;
        return new TreeNode(k, e, l, r);
    }

    //inserts a new TreeNode at a given location
    static TreeNode * insert(KeyType key, ElementType info, TreeNode * &t) //O(log N)
    {
        if(t == 0) //creates a new node if t is empty
        {
            t = make(key, info, 0, 0);
            return t;
        }

        else if(key < t->key)
        {
            insert(key, info, t->left);

            if(returnHeight(t->left) - returnHeight(t->right) == 2) //if unbalanced
                if(key < t->left->key) //outer case
                    rotateWithLeftChild(t);
                else //inner case
                    doubleWithLeftChild(t);
        }
        else if(key > t->key)
        {
            insert(key, info, t->right);

            if(returnHeight(t->right) - returnHeight(t->left) == 2) //if unbalanced
                if(key > t->right->key) //outer case
                    rotateWithRightChild(t);
                else //inner case
                    doubleWithRightChild(t);
        }
        else //duplicate case
            return t;

        t->height = max(returnHeight(t->left), returnHeight(t->right)) + 1;
    }

    //goes through tree starting at t to find correct key, then returns the node
    static TreeNode * find(KeyType key , TreeNode * t) //O(log N)
    {
        while(t != 0)
        {
            if(key < t->key)
                t = t->left;
            else if(key > t->key)
                t = t->right;
            else
                return t;
        }

        cout << key << " not found!" << endl;
        return 0;
    }

    //uses find, then removes node using a technique dependent on the situation
    static TreeNode * remove(KeyType key , TreeNode * &t) //O(log N)
    {
		if(t == NULL)
			return t;
		
		if(key < t->key) //go to the left
			remove(key, t->left);
			
		else if(key > t->key) //go to the right
			remove(key, t->right);
			
		else //tree node has been found
		{
			if((t->left == 0) || (t->right == 0)) //case for one or no children
			{
				TreeNode * temp = t->left ? t->left : t->right;
				TreeNode * tempPred = findPred(key, t);
				if(tempPred->left == temp)
					tempPred->left = 0;
				else if(tempPred->right == temp)
					tempPred->right = 0;
				
				if(temp == 0) //case for no children
				{
					temp = t;
					temp->left = 0;
					temp->right = 0;
					t = 0;
				}
				else //case for one child
				{
					*t = *temp; //copy child contents into t
				
					if(t->left == temp)
						t->left = 0;
					if(t->right == temp)
						t->right = 0;
				}
					
				freeNode(temp);
			}
			else
			{
				TreeNode * temp = findPred(t->key, t);
				swapKeyAndInfo(t, temp);
				return remove(temp->key, t->left);
			}
		}
		if(t == 0) //case for last node deleted
			return t;
			
		t->height = max(returnHeight(t->left), returnHeight(t->right)) +1;
		int balance = getBalance(t);
		
		//left left case
		if(balance > 1 && getBalance(t->left) >= 0)
		{
			return rotateWithLeftChild(t);
		}
		//left right case
		if(balance > 1 && getBalance(t->left) < 0)
		{
			t->left = rotateWithRightChild(t->left);
			return rotateWithLeftChild(t);
		}
		//right right case
		if(balance < -1 && getBalance(t->right) <= 0)
		{
			return rotateWithRightChild(t);
		}
		if(balance < -1 && getBalance(t->right) > 0)
		{
			t->right = rotateWithLeftChild(t->right);
			return rotateWithRightChild(t);
		}
		return t;
    }

    //recursively traverses tree in order and prints
    static void print(ostream & out , TreeNode * t) //O(N)
	{
        if(t)
        {
            out << "[";
            print(out, t->left);
            out << " (" << t->key << "," << t->info << ") ";
            print(out, t->right);
            out << "]";
        }
        else
        {
            out << "NULL";
		}
    }

    //deletes passed in node
    static void freeNode(TreeNode * t) //O(1)
    {
        --nodesCreated;
        delete t;
    }

    //deletes all nodes below and including t
    static void freeTree(TreeNode * &t) //O(N)
    {
        if(t)
        {
            freeTree(t->left);
            freeTree(t->right);
            freeNode(t);
        }
        t = 0;
    }

    //returns the info of specified treenode
    static ElementType & returnInfo(TreeNode * t) //O(1)
    {
        return t->info;
    }

    //returns height of node t or -1 if null
    static int returnHeight(TreeNode * t) //O(1)
    {
        return t == 0 ? -1 : t->height;
    }

    //displays the counter
    static void displayCounter() //O(1)
    {
        cout << endl << "Nodes created: " << nodesCreated << endl << endl;
    }
};

#endif
