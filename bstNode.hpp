/*
 * bstNode.hpp
 *
 *  Created on: Oct 19, 2021
 *      Author: William Hart
 */

#ifndef BSTNODE_HPP_
#define BSTNODE_HPP_

#include <iostream>
#include <stdlib.h>
#include "Student.hpp"
using namespace std;

class bstNode 
{
	friend class Student;
	friend class bst;
	
	bstNode *left;
	bstNode *right;
	bstNode *parent;
	int height;
	Student *student;
	
	public:
	bstNode();
	bstNode(string f, string l, int n, string j);
	~bstNode();
	void printNode();
};


#endif /* BSTNODE_HPP_ */
