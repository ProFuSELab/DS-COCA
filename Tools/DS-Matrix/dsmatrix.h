//**************************************************************************************************
//
// PROJECT  : Data Structures for Efficient Computation of the Dempster-Shafer Evidential
//     Calculations and Visualization of Imperfect Data
// CLASS    : DSMatrix 
// PURPOSE  : Matrix Implementation
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
// August 2015            Lalintha Polpitiya      Matrix Implementation
// May 2018               Lalintha Polpitiya      Cleanup
//
//**************************************************************************************************

#ifndef _dsmatrix_h_
#define _dsmatrix_h_

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>
#include <utility>

class DSMatrix
{
	public:
		DSMatrix(void);
		DSMatrix(int singletons);
		void debugOn(void);
		void debugOff(void);
		void readSingletons(void);
		std::pair<int, int> calFocalIndexAnyOrder(void);
		std::pair<int, int> calFocalIndexAscending(void);
		void fillingBeliefVecAnyOrder(void);
		void fillingBeliefVecAscending(void);
		int fillingBeliefVecRandom(std::vector<int> & rowVec, std::vector<int> & colVec);
		void fillingPlausibilityVecAnyOrder(void);
		void fillingPlausibilityVecAscending(void);
		std::vector<std::string> oddEvenToAll(void);
		void fillingBeliefInvVecAnyOrder(void);
		void fillingBeliefInvVecAscending(void);
		void genRandomMassValues(void);
		void genIncreasingMassValues(void);
		double accessFocalElement(int row, int col);
		double accessFocalElementCoVecs(std::vector<int> & rowVec, std::vector<int> & colVec);
		double calBelief(void);
		double calPlausibility(void);
		void removeFocalEleSingleton(void);
		void addFocalEleSingleton(void);
		void printFocalElements(void);
		void printFocalElementsNormalized(void);
		void printSingletonVector(void);
		void printBeliefInvVec(void);

	private:
		int no_singletons, no_sin_focalele, no_sin_belief, no_sin_plausibility;
		std::vector<std::string> odd_singleton, even_singleton, all_singleton;
		std::vector<std::string>::iterator it_str;
		std::vector<std::pair<int, int> > belief_ele_vec;
		std::vector<std::pair<int, int> > plausibility_ele_vec;
		std::vector<std::pair<int, int> > belief_inv_ele_vec;
		std::vector<std::vector<float> > focal_element;
		std::vector<std::pair<int, int> > focal_index;
		std::vector<int> power;
		double normalizing_const;
		bool debug;
		clock_t begin, end;
		double time_spent;
};

#endif //_dsmatrix_h_
