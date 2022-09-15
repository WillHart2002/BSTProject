/*
 * bstNode.cpp
 *
 *  Created on: Oct 19, 2021
 *      Author: William Hart
 */

#include "bstNode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

/*
 *bstNode left;
 	*bstNode right;
 	*bstNode parent;
 	int height;
 	*Student student;
*/

bstNode::bstNode() 
{
	left = NULL;
	right = NULL;
	parent = NULL;
	height = 0;
	student = NULL;
}

bstNode::bstNode(string f, string l, int n, string j) 
{
	student = new Student(f, l, n, j);
	left = NULL;
	right = NULL;
	parent = NULL;
	height = 1;
}

bstNode::~bstNode()
{
	delete student;
}

void bstNode::printNode() 
{
	cout << "node height: " << height << endl;
	cout << "Student " << student->first << " " << student->last << " favorite number is "<< student->fav_num << endl;
	cout << "Joke: " << student->joke <<endl;
}