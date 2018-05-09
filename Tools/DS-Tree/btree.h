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

#ifndef _btree_h_
#define _btree_h_

#include <iostream>
#include <cmath>

struct node
{
	float mass;
	node *left;
	node *right;
};

class BTree
{
	public:
		BTree(void);
		~BTree(void);
	
		node *getRoot();
		void setRoot(node *newroot);
		void createTree(int singleton);
		void addSubTreeSingleton(int i);
		void addSubTree(node *leaf, int level);
		double deleteSubTree(node *leaf);
	
	private:
		node *root;

};

#endif //_btree_h_
