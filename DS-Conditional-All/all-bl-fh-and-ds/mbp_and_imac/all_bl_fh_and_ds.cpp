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
// May 2018               Lalintha Polpitiya      All belief computations FH and DS 
//
//**************************************************************************************************

#include "../../condmatrix.h"

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

  for (int fod = 2; fod <= 12; fod += 2)
  {       
    round_count = 0;
    total_time = 0.0;
    for (int a = 1; a <= fod; a++)
    {
      cond_matrix.clearMatrix();
      cond_matrix.newMatrix(fod - a, a);
      cond_matrix.genIncreasingMassValues();
      // cout << "Fod size: " << fod << " |A|: " << a << endl;
      // cond_matrix.printFocalElements();
      // cond_matrix.printFocalElementsNormalized();

      for (int brounds = 0; brounds <= 10000 / fod; brounds++)
      {       
        cond_begin = clock();
        cond_matrix.computeGammaVals();
        cond_matrix.FMTGammatoPi();
        cond_matrix.FMTMasstoBl();
        cond_matrix.AllCondBlDSAll();
        cond_end = clock();
        round_count++;
        //cout << round_count << endl;
        total_time += (double)(cond_end - cond_begin) / CLOCKS_PER_SEC; 
        //cout << endl;
      }

      //cout << "Fod size: " << fod <<  "\t|A|: " << a << "\t\tTime spent: " << total_time * 1000 / (a - 1) << endl; // to get values in micro sec multiplied by 1000000 and divided by 1000
    }

    cout << "Fod size: " << fod << "\tRounds: " << round_count << "\tAverage time spent: " << (total_time / round_count) * 1000000 << " microseconds" << endl; // to get values in microseconds multiplied by 1000000

  }
  return 0;
}
