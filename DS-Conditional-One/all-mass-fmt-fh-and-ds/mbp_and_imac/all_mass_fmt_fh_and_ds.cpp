//**************************************************************************************************
//
// PROJECT  : DS-Conditional-One 
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
// May 2018               Lalintha Polpitiya      All mass (FMT on Bl) computations FH and DS
//
//**************************************************************************************************


#include "../../condmatrix.h"

using namespace std;
int arr[20];
vector <vector<bool> > all_bs;
double beliefs[1048576], masses[1048576];

void new_arr(int start, int tot, int k)
{
	//  cout << start << " " << tot << " " << k << endl;
	vector <bool> a;
	if (k == 0)
	{   
		//cnt++;
		for (int i = 0; i < tot; i++)
		{   
			a.push_back(arr[i]);
//			cout << arr[i] << " ";
		}   
//		cout << endl;
		all_bs.push_back(a);
		return;
	}   
	for (int i = start; i <= (tot - k); i++)
	{   
		arr[i] = 1;
		new_arr(i + 1, tot, k - 1); 
		arr[i] = 0;
	}   
}

int main()
{
	pair<int, int> index;
	double experiment_time = 0.0, total_time = 0.0, blB = 0.0, compA = 0.0, strad = 0.0, condBelief = 0.0, nlz = 0.0;
	clock_t cond_begin, cond_end;
	vector <int> b_param;
	int rem_ele, round_count = 0, belief_index = 0;
	CondMatrix cond_matrix;
	cond_matrix.debugOff();

	// for (int fod = 5; fod <= 20; fod += 5)
	for (int fod = 2; fod <= 12; fod += 2)
	{       
		round_count = 0;
		total_time = 0.0;
		for (int a = 1; a <= fod; a++)
		// for (int a = 1; a <= fod; a++)
		{
			cond_matrix.clearMatrix();
			cond_matrix.newMatrix(fod - a, a);
			cond_matrix.genIncreasingMassValues();
		//	cond_matrix.printFocalElements();
			all_bs.clear();
			for (int t = 1; t <= a; t++)
				new_arr(0, a, t); 
			for (int arounds = 0; arounds < 10019 / fod; arounds++)
			{       
				//for (int b = 1; b < a; b = b + 1)
				//{       
				round_count++;
				for (int brounds = 0; brounds < all_bs.size(); brounds++)
				//for (int brounds = 0; brounds < 2000 / ((fod - 1) * (fod - 1)); brounds++)
				{       
					//cout << "A : " << a << "B : " << b << endl;
					b_param.clear();
					for (int fill = 0; fill < all_bs[brounds].size(); fill++)
						if (all_bs[brounds][fill] == 1)
							b_param.push_back(fill);

					/*
					for (int fill = 0; fill < a; fill++)
						b_param.push_back(fill);
					for (int rem = 1; rem <= a - b; rem++)
					{
						rem_ele = rand() % (a + 1 - rem);
						b_param.erase (b_param.begin() + rem_ele);
					}
					*/
					
					
					cond_begin = clock();
					belief_index = cond_matrix.fillingConditionedVecRetBlIndex(b_param);
					blB = cond_matrix.calBeliefB();
					compA = cond_matrix.calBeliefComp();
					strad = cond_matrix.calStrad();
					nlz = cond_matrix.getNConst();
					condBelief = blB / (nlz - compA - strad);
					beliefs[belief_index] = condBelief;
					cond_end = clock();
				//	cout << "Fod size : " << fod <<  "\t|A| : " << a << "\t|B| : " << b << "\tBl (B) :" << blB << "\t Nlz : " << nlz << "\t Bl ({A}) : " << compA << "\tS({A};B) : " << strad << "\tCond Belief : " << condBelief << endl;
					//cout << round_count << endl;
					total_time += (double)(cond_end - cond_begin) / CLOCKS_PER_SEC; 
					//cout << "Index : " << belief_index << "\t Cond Belief : " << condBelief << endl;
				}
			//	cout << all_bs.size() << "\t" << total_time << "\t" << endl;
				/*
				for (int m = 0; m <= all_bs.size(); m++)
					cout << m << " : " << beliefs[m] << endl;
				*/
				//cout << "Fod size: " << fod <<  "\t|A|: " << a << "\t|B|: " << b << "\t\tTime spent: " << total_time * 1000000 << endl; // to get values in micro sec multiplied by 1000000 and divided by 1000
				//}
				//cout << "Fod size: " << fod <<  "\t|A|: " << a << "\t\tTime spent: " << total_time * 1000 / (a - 1) << endl; // to get values in micro sec multiplied by 1000000 and divided by 1000
				cond_begin = clock();
				for (int i = a - 1; i >= 0; i--)
				{
					for (int j = 0; j * pow(2, i) < pow(2, a); j += 2) 
						for (int k = 0; k < pow(2, i); k++)
							beliefs[j * (int)pow(2, i) + k + (int)pow(2, i)] -= beliefs[j * (int)pow(2, i) + k];
					/*
					double test_tot = 0;
					for (int m = 0; m < pow(2, a); m++)
					{
						test_tot+= beliefs[m];
						cout << beliefs[m] << " ";
					}
					cout << endl;
					cout << test_tot << "..." << endl;
					*/
				}
				cond_end = clock();
				total_time += (double)(cond_end - cond_begin) / CLOCKS_PER_SEC; 

			}
		}
		cout << "Fod size: " << fod << "\tRounds: " << round_count << "\t\tAverage Time spent: " << (total_time / round_count) * 1000000 << endl; // to get values in micro sec multiplied by 1000000 and divided by 1000
	}
        return 0;
}
