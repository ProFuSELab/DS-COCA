//**************************************************************************************************
//
// PROJECT      : Computaion of Conditional in the Dempster-Shafer belief theoretic framework 
// CLASS        : CondMatrix 
// PURPOSE      : To perform computations on a conditional computation matrix 
//
//**************************************************************************************************
// 
// Copyright(C) 2016 ProFuSE Lab, College of Engineering, University of Miami
// All rights reserved. 
// 
// This is unpublished proprietary Source Code of ProFuSE Lab.
//
// This copy of the Source Code is intended for ProFuSE Lab's research use only and is intended for
// view by persons duly authorized by the ProFuSE Lab. No part of this file may reproduced or
// distributed in any form or by any means without the written approval of the ProFuSE Lab. 
//
//**************************************************************************************************
//
// REVISIONS
// 
// Date                 Researcher              Descriptions
// -------------------  -------------------     -------------------
// April 2016          	Lalintha Polpitiya     	Initial experiment 
// August 2016         	Lalintha Polpitiya     	Condtional computation matrix 
// September 2016      	Lalintha Polpitiya     	DS-Alpha scheme	

//
//**************************************************************************************************

//**************************************************************************************************
//
// PROJECT  : DS-Condtional-One and DS-Conditional-All 
// CLASS    : CondMatrix 
// PURPOSE  : Simulate
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
// April 2016             Lalintha Polpitiya      Initial Experiment
// August 2016            Lalintha Polpitiya      Conditional Computation Matrix
// September 2016         Lalintha Polpitiya      DS-Alpha Scheme
// May 2018               Lalintha Polpitiya      DS-CONAC 
//
//**************************************************************************************************

#include "condmatrix.h"

using namespace std;

//**************************************************************************************************
// Default 20 singletons
//**************************************************************************************************
CondMatrix::CondMatrix(void)
{
	vector<float> row;

	no_singletons = 20;
	no_sin_conditioning = 10;
	no_sin_complement = 10;
	no_sin_conditioned = 0;
	normalizing_const = 1.0;
	debug = false;
	row.assign(pow(2, 10), 0.0);
	focal_element.assign(pow(2, 10), row);
	REGAP_index.assign(pow(2, 20), 0);
	int power_of_i = 1;
	for (int i = 0; i < no_singletons; i++)
	{
		power.push_back(power_of_i);
		power_of_i *= 2;
	}
}

//**************************************************************************************************
// Have to pass the number of singletons; conditional singletons and complement singletons  
//**************************************************************************************************
CondMatrix::CondMatrix(int sin_complement, int sin_conditioning)
{
	vector<float> row;

	no_singletons = sin_complement + sin_conditioning;
	no_sin_conditioning = sin_conditioning;
	no_sin_complement = sin_complement;
	no_sin_conditioned = 0;
	normalizing_const = 1.0;
	debug = false;
	row.assign(pow(2, sin_conditioning), 0.0);
	focal_element.assign(pow(2, sin_complement), row);
	REGAP_index.assign(pow(2, no_singletons), 0);
	int power_of_i = 1;
	for (int i = 0; i < no_singletons; i++)
	{
		power.push_back(power_of_i);
		power_of_i *= 2;
	}
}

//**************************************************************************************************
// Clear matrix 
//**************************************************************************************************
void CondMatrix::clearMatrix(void)
{
	vector<float> row;

	no_singletons = 0;
	no_sin_conditioning = 0;
	no_sin_complement = 0;
	conditioned_ele_vec.clear();
	no_sin_conditioned = 0;
	normalizing_const = 1.0;
	debug = false;
	focal_element.clear();
	REGAP_index.clear();
	int power_of_i = 1;
}

//**************************************************************************************************
// Have to pass the number of singletons; conditional singletons and complement singletons  
//**************************************************************************************************
void CondMatrix::newMatrix(int sin_complement, int sin_conditioning)
{
	vector<float> row;

	no_singletons = sin_complement + sin_conditioning;
	no_sin_conditioning = sin_conditioning;
	no_sin_complement = sin_complement;
	no_sin_conditioned = 0;
	normalizing_const = 1.0;
	debug = false;
	row.assign(pow(2, sin_conditioning), 0.0);
	focal_element.assign(pow(2, sin_complement), row);
	REGAP_index.assign(pow(2, no_singletons), 0);
	int power_of_i = 1;
	for (int i = 0; i < no_singletons; i++)
	{
		power.push_back(power_of_i);
		power_of_i *= 2;
	}
}


//**************************************************************************************************
// Debug On 
//**************************************************************************************************
void CondMatrix::debugOn(void)
{
	debug = true;
}

//**************************************************************************************************
// Debug Off 
//**************************************************************************************************
void CondMatrix::debugOff(void)
{
	debug = false;
}

//**************************************************************************************************
// Reading singleton names 
//**************************************************************************************************
void CondMatrix::readSingletons(void)
{
	string st;
	for (int i = 0; i < no_sin_conditioning; i++)
	{
		cin >> st;
		row_singleton.push_back(st);
	}

	for (int i = 0; i < no_sin_complement; i++)
	{
		cin >> st;
		col_singleton.push_back(st);
	}
}

//**************************************************************************************************
// Filling conditioned vector random, for experiments 
//**************************************************************************************************
int CondMatrix::fillingConditionedVecRandom(vector<int> & conditionedVec)
{
	conditioned_ele_vec.clear();
	no_sin_conditioned = conditionedVec.size();

	for (vector<int>::iterator it = conditionedVec.begin(); it != conditionedVec.end(); ++it)
	{
		conditioned_ele_vec.push_back(power[*it]);	
	}

	if (debug)
		cout << "Belief ele vec size : " << conditioned_ele_vec.size() << endl;

	return conditioned_ele_vec.size();
}

//**************************************************************************************************
// Generate random mass values 
//**************************************************************************************************
void CondMatrix::genRandomMassValues(void)
{
	srand(time(NULL)); 						// initialize random seed
	normalizing_const = 0.0;

	for (int row = 0; row < pow(2, no_sin_complement); row++)
		for (int col = 0; col < pow(2, no_sin_conditioning); col++)
		{
			if (row == 0 && col == 0)
				focal_element[0][0] = 0.0;		// 0.0 to null element
			else
				focal_element[row][col] = rand() % 10000; // 0 to 9999
			normalizing_const += focal_element[row][col];	// normalizing constant

		}
	// no need to normalize everytime, we can normalize only when we use

	if (debug)
		for (int row = 0; row < pow(2, no_sin_complement); row++)
		{
			for (int col = 0; col < pow(2, no_sin_conditioning); col++)
				cout << "mass( " << row << " : " << col << " ) \t: " 
					<< focal_element[row][col] / normalizing_const << " " << endl;
			cout << endl;
		}
}

//**************************************************************************************************
// Generate increasing mass values, specially for testing 
//**************************************************************************************************
void CondMatrix::genIncreasingMassValues(void)
{
	srand(time(NULL)); 						// initialize random seed
	normalizing_const = 0.0;

	for (int row = 0; row < pow(2, no_sin_complement); row++)
		for (int col = 0; col < pow(2, no_sin_conditioning); col++)
		{
			if (row == 0 && col == 0) 
				focal_element[0][0] = 0.0;		// 0.0 to null element
			focal_element[row][col] = col + row * pow(2, no_sin_conditioning);
			normalizing_const += focal_element[row][col];	// normalizing constant
		}
	// no need to normalize everytime, we can normalize only when we use

	if (debug)
		for (int row = 0; row < pow(2, no_sin_complement); row++)
		{
			for (int col = 0; col < pow(2, no_sin_conditioning); col++)
				cout << "mass( " << row << " : " << col << " ) \t: " 
					<< focal_element[row][col] / normalizing_const << " " <<endl;
			cout << endl;
		}
}

//**************************************************************************************************
// Get normalizing const 
//**************************************************************************************************
double CondMatrix::getNConst(void)
{
	return normalizing_const;
}

//**************************************************************************************************
// Access a focal element 
//**************************************************************************************************
double CondMatrix::accessFocalElement(int row, int col)
{
	double element;

	begin = clock();
	element = focal_element[row][col];
	end = clock();
	time_spent = 1000000 * (double)(end - begin) / CLOCKS_PER_SEC;

	if (debug)
		cout << "Focal element (" << row << ", " << col << ")\t: " << element << endl;

	cout << "Time spent on accessing a focal element\t: " << time_spent << endl;
	return element;
}

//**************************************************************************************************
// Access a focal element with even and odd singleton vectors, for experiments, returns time 
//**************************************************************************************************
double CondMatrix::accessFocalElementCoVecs(vector<int> & rowVec, vector<int> & colVec)
{
	double element;
	int row = 0, col = 0;

	begin = clock();
	for (vector<int>::iterator it = rowVec.begin(); it != rowVec.end(); ++it)
	{
		row += power[*it];	
	}
	for (vector<int>::iterator it = colVec.begin(); it != colVec.end(); ++it)
	{
		col += power[*it];	
	}
	element = focal_element[row][col];
	end = clock();
	time_spent = 1000000 * (double)(end - begin) / CLOCKS_PER_SEC;

	if (debug)
		cout << "Focal element (" << row << ", " << col << ")\t: " << element << endl;

	cout << "Time spent on accessing a focal element\t: " << time_spent << endl;
	return time_spent;
}

//**************************************************************************************************
// Calculating belief B 
//**************************************************************************************************
double CondMatrix::calBeliefB(void)
{
	double belief = 0.0;
	if (debug)
	{
		cout << "Conditioned ele vec" << endl;
		for (int i = 0; i < conditioned_ele_vec.size(); i++)
			cout << "i : " << i << "\t element \t" << conditioned_ele_vec[i] << endl;
	}

	int count = 0, temp = 0, subsets = 0;
	for (int i = 0; i < no_sin_conditioned; i++)
	{
		temp = count;	
		REGAP_index[count] = conditioned_ele_vec[i];
		count++;
		
		for (int j = 0; j < temp; j++)
		{
			REGAP_index[count] = REGAP_index[j] + conditioned_ele_vec[i];
			count++;
		}
	}
	
	subsets = pow(2, no_sin_conditioned);

	if (debug)
	{
		for (int i = 0; i < subsets - 1; i++)
			cout << "REGAP index "<< i << " : " <<  REGAP_index[i] << endl;

		cout << endl << "Row count : " << focal_element.size() << "\tCol count : " << focal_element[0].size() << endl;
	}
	
	for (int i = 0; i < subsets - 1; i++)
	{
		belief += focal_element[0][REGAP_index[i]];
	}
	
	return belief;			// returns belief
}

//**************************************************************************************************
// Calculating belief comp A
//**************************************************************************************************
double CondMatrix::calBeliefComp(void)
{
	double belief = 0.0;

	for (int i = 0; i < pow(2, no_sin_complement); i++)
	{
		belief += focal_element[i][0];
	}
	return belief;			// returns belief
}

//**************************************************************************************************
// Calculating straddling component 
//**************************************************************************************************
double CondMatrix::calStrad(void)
{
	double strad = 0.0;
	int subsets_row = 0, subsets_col = 0, REGAP_col = 0;

	subsets_col = pow(2, no_sin_conditioned);
	subsets_row = pow(2, no_sin_complement);

	for (int i = 0; i < subsets_col - 1; i++)
	{
		REGAP_col = REGAP_index[i];
		for (int j = 1; j < subsets_row; j++)
		{
			strad += focal_element[j][REGAP_col];
		}
	}

	return strad;			// returns strad 
}

//**************************************************************************************************
// Print focal elements, without normalizing
//**************************************************************************************************
void CondMatrix::printFocalElements(void)
{
	for (int row = 0; row < pow(2, no_sin_complement); row++)
	{
		for (int col = 0; col < pow(2, no_sin_conditioning); col++)
			cout << "mass( " << row << " : " << col << " ) \t: " 
				<< focal_element[row][col] << " " << endl;
		cout << endl;
	}
}

//**************************************************************************************************
// Print focal elements normalized
//**************************************************************************************************
void CondMatrix::printFocalElementsNormalized(void)
{
	for (int row = 0; row < pow(2, no_sin_complement); row++)
	{
		for (int col = 0; col < pow(2, no_sin_conditioning); col++)
			cout << "mass( " << row << " : " << col << " ) \t: " 
				<< focal_element[row][col] / normalizing_const << " " << endl;
		cout << endl;
	}
}

//**************************************************************************************************
// Print focal elements normalized
//**************************************************************************************************
void CondMatrix::printSingletonVector(void)
{
}

//**************************************************************************************************
// Print belief complement vector
//**************************************************************************************************
void CondMatrix::printConditionedVec(void)
{
	cout << "Conditioned vector \t: " << endl;
	for (int i = 0; i < conditioned_ele_vec.size(); i++)
	{
		cout << conditioned_ele_vec[i] << " " << endl;
	}
}
