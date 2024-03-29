/*************************************************************************
 * AUTHOR		: Ryan Martinez
 * STUDENT ID	: 389657
 * Assignment	: 4
 * CLASS		: CS1D
 * SECTION		: MW: 3:30 PM
 * DUE DATE		: 9/26/2016
 ************************************************************************/

#ifndef H_binarySearchTree
#define H_binarySearchTree
#include <iostream>
#include "binaryTree.h"
 
using namespace std;

template <class elemType>
class bSearchTreeType: public binaryTreeType<elemType>
{
public:
    bool search(const elemType& searchItem) const;
      //Function to determine if searchItem is in the binary 
      //search tree.
      //Postcondition: Returns true if searchItem is found in 
      //               the binary search tree; otherwise, 
      //               returns false.

    void insert(const elemType& insertItem);
      //Function to insert insertItem in the binary search tree.
      //Postcondition: If there is no node in the binary search
      //               tree that has the same info as 
      //               insertItem, a node with the info 
      //               insertItem is created and inserted in the
      //               binary search tree.

    void deleteNode(const elemType& deleteItem);
      //Function to delete deleteItem from the binary search tree 
      //Postcondition: If a node with the same info as deleteItem
      //               is found, it is deleted from the binary 
      //               search tree.
      //               If the binary tree is empty or deleteItem
      //               is not in the binary tree, an appropriate
      //               message is printed.

private:
    void deleteFromTree(nodeType<elemType>* &p);
      //Function to delete the node to which p points is 
      //deleted from the binary search tree.
      //Postcondition: The node to which p points is deleted
      //               from the binary search tree.
};


template <class elemType>
bool bSearchTreeType<elemType>::search
                    (const elemType& searchItem) const
{
    nodeType<elemType> *current;
    bool found = false;

    if (binaryTreeType<elemType>::root == NULL)
        cout << "Cannot search an empty tree." << endl;
    else
    { 
       current = binaryTreeType<elemType>::root;

       while (current != NULL && !found)
        {
            if (current->info == searchItem)
                found = true;
            else if (current->info > searchItem)
                current = current->left;
            else
                current = current->right;
        }//end while
    }//end else

    return found;
}//end search

template <class elemType>
void bSearchTreeType<elemType>::insert
                 (const elemType& insertItem)
{
    nodeType<elemType> *current; //pointer to traverse the tree
    nodeType<elemType> *trailCurrent; //pointer behind current
    nodeType<elemType> *newNode;  //pointer to create the node

    newNode = new nodeType<elemType>;
    newNode->info = insertItem;
    newNode->left = NULL;
    newNode->right = NULL;

    if (binaryTreeType<elemType>::root == NULL)
    	binaryTreeType<elemType>::root = newNode;
    else
    {
        current = binaryTreeType<elemType>::root;
 
        while (current != NULL)
        {
            trailCurrent = current;

            if (current->info == insertItem)
            {
                cout << "The item to be inserted is already ";
                cout << "in the tree -- duplicates are not "
                     << "allowed." << endl;
                return;
            }
            else if (current->info > insertItem)
                current = current->left;
            else
                current = current->right;
        }//end while

        if (trailCurrent->info > insertItem)
            trailCurrent->left = newNode;
        else
            trailCurrent->right = newNode;
    }
}//end insert

template <class elemType>
void bSearchTreeType<elemType>::deleteNode
                                (const elemType& deleteItem)
{
    nodeType<elemType> *current; //pointer to traverse the tree
    nodeType<elemType> *trailCurrent; //pointer behind current
    bool found = false;

    if (binaryTreeType<elemType>::root == NULL)
        cout << "Cannot delete from an empty tree." 
             << endl;
    else
    {
        current = binaryTreeType<elemType>::root;
        trailCurrent = binaryTreeType<elemType>::root;

        while (current != NULL && !found)
        {
            if (current->info == deleteItem)
                found = true;
            else
            {
                trailCurrent = current;

                if (current->info > deleteItem)
                    current = current->left;
                else
                    current = current->right;
            }
        }//end while

        if (current == NULL)
            cout << "The item to be deleted is not in the tree." 
                 << endl;
        else if (found)
        {
            if (current == binaryTreeType<elemType>::root)
                deleteFromTree(binaryTreeType<elemType>::root);
            else if (trailCurrent->info > deleteItem)
                deleteFromTree(trailCurrent->left);
            else
                deleteFromTree(trailCurrent->right);
        }
        else
            cout << "The item to be deleted is not in the tree."
                 << endl;
    }
} //end deleteNode

template <class elemType>
void bSearchTreeType<elemType>::deleteFromTree
                                 (nodeType<elemType>* &p)
{
    nodeType<elemType> *current; //pointer to traverse the tree
    nodeType<elemType> *trailCurrent;  //pointer behind current
    nodeType<elemType> *temp;      //pointer to delete the node

    if (p == NULL)
        cout << "Error: The node to be deleted does not exist."
             << endl;
    else if (p->left == NULL && p->right == NULL)
    {
        temp = p;
        p = NULL;
        delete temp;
    }
    else if (p->left == NULL)
    {
        temp = p;
        p = temp->right;
        delete temp;
    }
    else if (p->right == NULL)
    {
        temp = p;
        p = temp->left;
        delete temp;
    }
    else
    {
        current = p->left;
        trailCurrent = NULL;

        while (current->right != NULL)
        {
            trailCurrent = current;
            current = current->right;
        }//end while

        p->info = current->info;

        if (trailCurrent == NULL) //current did not move;
                               //current == p->left; adjust p
            p->left = current->left;
        else
            trailCurrent->right = current->left;
 
        delete current;
    }//end else
} //end deleteFromTree

#endif
