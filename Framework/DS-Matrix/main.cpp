//**************************************************************************************************
//
// PROJECT  : Data Structures for Efficient Computation of the Dempster-Shafer Evidential
//     Calculations and Visualization of Imperfect Data
// CLASS    : Simulate DSMatrix 
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

#include "dsmatrix.h"

using namespace std;

int main()
{
        pair<int, int> index;
        double experiment_time, total_time = 0;
	vector <int> row_param, col_param;
        DSMatrix ds_matrix;
        ds_matrix.debugOff();
        ds_matrix.readSingletons();
        ds_matrix.genIncreasingMassValues();

	for (int fod = 1; fod <= 20; fod++)
	{       
		for (int rounds = 0; rounds < 1000000; rounds++)
		{       
			for (int i = 0; i < fod; i++)
			{       
				if (rand() % 3 == 0)
				{
					if (i % 2 == 1)
						row_param.push_back(i / 2);
					else
						col_param.push_back(i / 2);
				}
			}
			ds_matrix.fillingBeliefVecRandom(row_param, col_param);
			experiment_time = ds_matrix.calBelief();
			row_param.clear();
			col_param.clear();
			total_time += experiment_time;
		}
		cout << "FoD size : " << fod << " Time spent : " << total_time << endl;
		total_time = 0;
	}


        return 0;
}
