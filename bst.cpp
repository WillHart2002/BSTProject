/*
 * bst.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: William Hart
 */

//add includes
#include "bst.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

bst::bst() // empty constructor
{
	root = NULL;
}

bst::bst(string f, string l, int n, string j) // constructor that forms the root
{
	root = new bstNode(f, l, n, j);
}

void bst::clearTree() //clears out an old tree, this calls the recursive clearTree with the root node
{
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	} else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void bst::clearTree(bstNode *tmp) {
	if (tmp == NULL) {
		return;
	} else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete (tmp);
	}
}

void bst::printTreeIO() // Just the start – you must write the recursive version
{
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		cout << endl << "Printing In Order:" << endl;
		printTreeIO(root);
	}
}

void bst::printTreePre() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		cout << endl << "Printing PreOrder:" << endl;
		printTreePre(root);
	}
}

void bst::printTreePost() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	} else {
		cout << endl << "Printing PostOrder:" << endl;
		printTreePost(root);
	}
}

bool bst::insert(string f, string l, int n, string j) //insert a student into the tree with the following parameters, using bstNode constructor
{
	bstNode *s = new bstNode(f,l,n,j);
	    if (root == NULL){
	            root = s;
	            return true;
	    }
	    bstNode *temp = root;
	    while (temp){

	        if (l < temp->student->last){
	            if (temp->left == NULL){
	                temp -> left = s;
	                temp -> left -> parent = temp;
	                setHeight(temp);
	                return true;
	            }
	            else {
	                temp = temp->left;
	            }
	        }
	        else if (l > temp->student->last){
	            if (temp->right == NULL){
	                temp -> right = s;
	                temp -> right -> parent = temp;
	                setHeight(temp);
	                return true;
	            }
	            else{
	                temp = temp->right;
	            }
	        }
	        else return false; //equal
	    }
	    return false;
}

bstNode* bst::find(string l, string f) //finds a student within the tree using their first and last name
{
	bstNode *temp = root;
	    while (temp){
	        string l_temp = temp->student->last;
	        string f_temp = temp->student->first;
	        if (l_temp == l && f_temp == f)
	        {
	            return temp;
	        } else if(l < l_temp) { //less than, goes left
	            temp = temp->left;
	        } else { //greater than, goes right
	            temp = temp->right;
	        }
	    }
	    return NULL;
}

void bst::printTreeIO(bstNode *n) //recursive function that prints out the data in the tree in order
{
	 bstNode *temp = n;
	 if (temp)
	 {
	 	if (temp->left == NULL); 
	 	else 
	 	{
	        printTreeIO(temp->left);
	    }
	    n->printNode();
	    if (temp->right == NULL); 
		else 
		{
	        printTreeIO(temp->right);
	    }
	 } 
}

void bst::printTreePre(bstNode *n) //a recursive function that prints out the datain the tree in pre-order
{
	bstNode *temp = n;
	if (temp)
	{
		n->printNode();
	    if (temp->left == NULL); 
	    else 
	    {
	        printTreePre(temp->left);
	    }
	    if (temp->right == NULL); 
	    else 
	    {
	        printTreePre(temp->right);
	    }
	} 
}

void bst::printTreePost(bstNode *n) //a recursive function that prints out the data in the tree in post-order
{
	bstNode *temp = n;
	if (temp)
	{
		if (temp->left == NULL);
		else 
		{
	        printTreePost(temp->left);
	    }
	    if (temp->right == NULL); 
	    else 
	    {
	        printTreePost(temp->right);
	    }
	    n->printNode();
	} 
}

bstNode* bst::remove(string l, string f) //removes node from tree and returns that node
{
	 bstNode *temp = find(l, f);
	 bstNode *furthest_right;
	 if (temp == NULL) { return NULL; }
	 if (temp -> left == NULL && temp -> right == NULL) //no kids
	 { 
	 	removeNoKids(temp);
	 }
	 else if (temp -> left && temp -> right == NULL) //left is not NULL, right is NULL
	 { 
	 	removeOneKid(temp, true);
	 }
	 else if (temp -> left == NULL && temp -> right) //left is  NULL, right is not NULL
	 { 
	 	removeOneKid(temp, false);
	 }  else { //there are two children
	        bstNode *right_temp = temp->right;
	        bstNode *n = temp->left;
	        bstNode *temp_parent = temp->parent;
	        while (n) //finds furthest right
	        {
	            furthest_right = n;
	            n = n->right;
	        }
	        if (temp_parent->right == temp) //makes temps parent point to furthest right
	        {
	            temp_parent->right = furthest_right;
	        } else {
	            temp_parent->left = furthest_right;
	        }
	        if (temp->left != furthest_right) 
	        {
	        	 temp->left->parent = furthest_right; //makes temps left kid point to furthest right, if it exists
	        	 furthest_right->left = temp->left; //makes furthest right point to temps left kid, if it exists
	        	 furthest_right->parent->right = NULL; //makes furthest rights old parent point to null for their right kid
	        } else {
	        	furthest_right->left = NULL;
	        }
	        if (temp->right != NULL) temp->right->parent = furthest_right; //makes temps right kid point to furthest right, if it exits
	        furthest_right->right = right_temp;
	        furthest_right->parent = temp->parent;
	    }
	 	setHeight(temp);
	    return temp;
}

bstNode* bst::removeNoKids(bstNode *tmp) //for removing a node with no children
{
	bstNode *temp = tmp;
	if (temp->parent->left == temp) 
	{
		temp->parent->left = NULL;
	} else {
		temp->parent->right = NULL;
	}
	return temp;
}

bstNode* bst::removeOneKid(bstNode *tmp, bool leftFlag) //for removing a node with one child, leftflag being used to determine if the child is on the left or right
{
	bstNode *temp = tmp;
	if (leftFlag) 
	{
		if (temp->parent->left == temp) 
		{
			temp->parent->left = temp->left;
			temp->left->parent = temp->parent;
		} else {
			temp->parent->right = temp->left;
			temp->left->parent = temp->parent;
		}
	} else {
		if (temp->parent->left == temp) 
		{
			temp->parent->left = temp->right;
			temp->right->parent = temp->parent;
		} else {
			temp->parent->right = temp->right;
			temp->right->parent = temp->parent;
		}
	}
	return temp;
}

void bst::setHeight(bstNode *n) //This method sets the heights of the nodes in a tree
{
	
	bstNode *temp = n;
	int h = 0;
	while (temp != NULL) //changing there nodes ansestors heights 
	{
		if (temp->left != NULL) h = temp->left->height;
		if (temp->right != NULL)  //setting the height to the highest height between the two kids
		{
			if(h < temp->right->height) h = temp->right->height;
		}
		h++; 
		temp->height = h;
		if (temp->parent == NULL) break;
		if (temp->parent->height >= (temp->height + 1)) break;
		temp = temp->parent;
	}
}
 