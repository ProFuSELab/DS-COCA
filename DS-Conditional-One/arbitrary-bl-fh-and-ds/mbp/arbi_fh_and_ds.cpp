//**************************************************************************************************
//
// PROJECT  : DS-Condtional-One 
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
// May 2018               Lalintha Polpitiya      Arbitrary belief computations FH and DS
//
//**************************************************************************************************
#include "condmatrix.h"

using namespace std;

int main()
{
        pair<int, int> index;
        double experiment_time = 0.0, total_time = 0.0, blB = 0.0, compA = 0.0, strad = 0.0, condBelief = 0.0, nlz = 0.0;
	clock_t cond_begin, cond_end;
	vector <int> b_param;
	int rem_ele, round_count = 0;
        CondMatrix cond_matrix;
        cond_matrix.debugOff();

	// for (int fod = 5; fod <= 20; fod += 5)
	for (int fod = 2; fod <= 20; fod += 2)
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
			for (int arounds = 0; arounds < 1; arounds++)
			{       
				for (int b = 1; b <= a; b = b + 1)
				{       
					for (int brounds = 0; brounds < 20400 / ((fod - 1) * (fod - 1)); brounds++)
					{       
            if (a != b)
            {
              b_param.clear();
              for (int fill = 0; fill < a; fill++)
                b_param.push_back(fill);
              for (int rem = 1; rem <= a - b; rem++)
              {
                rem_ele = rand() % (a + 1 - rem);
                b_param.erase (b_param.begin() + rem_ele);
              }
            }
						
						cond_begin = clock();
            if (a == b)
              condBelief = 1;
            else
            {
              cond_matrix.fillingConditionedVecRandom(b_param);
              blB = cond_matrix.calBeliefB();
              compA = cond_matrix.calBeliefComp();
              strad = cond_matrix.calStrad();
              nlz = cond_matrix.getNConst();
              condBelief = blB / (nlz - compA - strad);
            }
						cond_end = clock();
            if (a == b)
              cout << "Fod size: " << fod <<  "\t|A|: " << a << "\t|B|: " << b << "\tFH Cond Belief: " << condBelief << endl;
            else
              cout << "Fod size: " << fod <<  "\t|A|: " << a << "\t|B|: " << b << "\tBl (B):" << blB / nlz << "\t Nlz: " << nlz << "\t Bl ({A}): " << compA / nlz << "\tS({A};B): " << strad / nlz << "\tFH Cond Belief: " << condBelief << endl;

						round_count++;
						//cout << round_count << endl;
						total_time += (double)(cond_end - cond_begin) / CLOCKS_PER_SEC; 
					}
					//cout << "Fod size: " << fod <<  "\t|A|: " << a << "\t|B|: " << b << "\t\tTime spent: " << total_time * 1000000 << endl; // to get values in micro sec multiplied by 1000000 and divided by 1000
				}
				//cout << "Fod size: " << fod <<  "\t|A|: " << a << "\t\tTime spent: " << total_time * 1000 / (a - 1) << endl; // to get values in micro sec multiplied by 1000000 and divided by 1000
			}
		}
		cout << "Fod size: " << fod << "\tRounds: " << round_count << "\tAverage Time spent: " << (total_time / round_count) * 1000000 << " microseconds" << endl; // to get values in microseconds multiplied by 1000000
	}
        return 0;
}
