//**************************************************************************************************
//
// PROJECT  : Data Structures for Efficient Computation of the Dempster-Shafer Evidential
//     Calculations and Visualization of Imperfect Data
// CLASS    : Simulate 
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
// May 2018               Lalintha Polpitiya      Simulate 
//
//**************************************************************************************************

#include "DS-Vector/dsvector.h"
#include "DS-Matrix/dsmatrix.h"

using namespace std;

int main()
{
        int index;
        double element;
        DSVector ds_vector;
        DSMatrix ds_matrix;
        ds_vector.debugOff();
        ds_vector.readSingletons();
        index = ds_vector.calFocalIndexAscending();
        element = ds_vector.accessFocalElement(index);
        ds_vector.genIncreasingMassValues();
        ds_vector.fillingBeliefVecAscending();
        ds_vector.calBelief();
        ds_vector.fillingBeliefInvVecAscending();
        ds_vector.calPlausibility();
        ds_vector.printSingletonVector();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.removeFocalEleSingleton();
        ds_vector.printSingletonVector();
        ds_vector.printFocalElements();
        ds_vector.removeFocalEleSingleton();
        ds_vector.addFocalEleSingleton();
        ds_vector.printSingletonVector();
        ds_vector.printFocalElements();
            
        return 0;
}
