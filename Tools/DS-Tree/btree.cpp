//**************************************************************************************************
//
// PROJECT  : Data Structures for Efficient Computation of the Dempster-Shafer Evidential
//     Calculations and Visualization of Imperfect Data
// CLASS    : BTree 
// PURPOSE  : BTree Implementation
//
//**************************************************************************************************
//
// Copyright (c) 2018 ProFuSE Lab - University of Miami
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//
//
// REVISIONS
//
// Date                   Researcher              Descriptions
// --------------------   --------------------    --------------------
// August 2015            Lalintha Polpitiya      Binary Tree Implementation
// March 2016             Lalintha Polpitiya      Experiments 
// May 2018               Lalintha Polpitiya      Cleanup
//
//**************************************************************************************************

#include "btree.h"

using namespace std;

//**************************************************************************************************
// Default 20 Singletons
//**************************************************************************************************
BTree::BTree(void)
{
	root = NULL;
}

//**************************************************************************************************
// Destructor 
//**************************************************************************************************
BTree::~BTree(void)
{

}

//**************************************************************************************************
// Create tree 
//**************************************************************************************************
void BTree::createTree(int singleton)
{
	for (int i = 0; i < singleton; i++)
	{
		addSubTreeSingleton(i);
	}
}

void BTree::addSubTreeSingleton(int i)
{
	int level = 0;
	node *new_node;
	new_node = new node;
	new_node->mass = 0.0;
	new_node->left = root;
	new_node->right = NULL;
	root = new_node;
	level = i - 1;
	if (level >= 0)
	{
		new_node = new node;
		new_node->mass = 0.0;
		new_node->left = NULL;
		new_node->right = NULL;
		root->right = new_node;
		addSubTree(root->right, level - 1);
	}
}

//**************************************************************************************************
// Add sub tree 
//**************************************************************************************************
void BTree::addSubTree(node *leaf, int level)
{
	if (level >= 0)
	{
		node *new_node;
		new_node = new node;
		new_node->mass = 0.0;
		new_node->left = NULL;
		new_node->right = NULL;
		leaf->left = new_node;
		addSubTree(leaf->left, level - 1);

		new_node = new node;
		new_node->mass = 0.0;
		new_node->left = NULL;
		new_node->right = NULL;
		leaf->right = new_node;
		addSubTree(leaf->right, level - 1);
	}
}

//**************************************************************************************************
// Delete sub tree 
//**************************************************************************************************
double BTree::deleteSubTree(node *leaf)
{
	double normalize = 0.0;
	if (leaf->left)
		normalize += deleteSubTree(leaf->left);	
	if (leaf->right)
		normalize += deleteSubTree(leaf->right);	
	normalize += leaf->mass;
	if (leaf)
		delete leaf;
	return normalize;
}

//**************************************************************************************************
// Get root 
//**************************************************************************************************
node *BTree::getRoot()
{
	return root;	
}

//**************************************************************************************************
// Set root 
//**************************************************************************************************
void BTree::setRoot(node *newroot)
{
	root = newroot;
}
