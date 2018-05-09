//**************************************************************************************************
//
// PROJECT  : Data Structures for Efficient Computation of the Dempster-Shafer Evidential
//     Calculations and Visualization of Imperfect Data
// CLASS    : Simulate DSTree 
// PURPOSE  : Tree Implementation
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
// August 2015            Lalintha Polpitiya      Tree Implementation
// May 2018               Lalintha Polpitiya      Cleanup
//
//**************************************************************************************************

#include "dstree.h"

using namespace std;

int main()
{
        int index;
        double experiment_time, total_time = 0;
        DSTree ds_tree;
        ds_tree.debugOff();
	
	vector <int> param;
	srand(time(NULL));
	for (int fod = 1; fod <= 20; fod++)
	{
		ds_tree.addSingleton();
		ds_tree.genIncreasingMassValues();
		for (int rounds = 0; rounds < 10000; rounds++)
		{
			for (int i = 0; i < fod; i++)
			{
				if (rand() % 3 != 0)
				param.push_back(i);
			}
			experiment_time = ds_tree.accessFocalElementIndexVec(param);
			param.clear();
			total_time += experiment_time;
		}
		cout << "FoD size : " << fod << " Time spent : " << total_time << endl;
		total_time = 0;
	}

        return 0;
}
