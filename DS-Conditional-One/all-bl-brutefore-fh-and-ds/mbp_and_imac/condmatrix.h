#ifndef _condmatrix_h_
#define _condmatrix_h_

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>
#include <utility>

class CondMatrix
{
	public:
		CondMatrix(void);
		CondMatrix(int sin_complement, int sin_conditioning);
		void clearMatrix();
		void newMatrix(int sin_complement, int sin_conditioning);
		void debugOn(void);
		void debugOff(void);
		void readSingletons(void);
		int fillingConditionedVecRandom(std::vector<int> & conditionedVec);
		void genRandomMassValues(void);
		void genIncreasingMassValues(void);
		double getNConst(void);
		double accessFocalElement(int row, int col);
		double accessFocalElementCoVecs(std::vector<int> & rowVec, std::vector<int> & colVec);
		double calBeliefB(void);
		double calBeliefComp(void);
		double calStrad(void);
		void printFocalElements(void);
		void printFocalElementsNormalized(void);
		void printSingletonVector(void);
		void printConditionedVec(void);

	private:
		int no_singletons, no_sin_focalele, no_sin_conditioning, no_sin_complement, no_sin_conditioned;
		std::vector<std::string> row_singleton, col_singleton;
		std::vector<std::string>::iterator it_str;
		std::vector<int> conditioned_ele_vec;
		// std::vector<int> complement_ele_vec;
		// std::vector<int> conditioning_ele_vec;
		std::vector<std::vector<float> > focal_element;
		std::vector<int> REGAP_index;
		std::vector<int> power;
		double normalizing_const;
		bool debug;
		clock_t begin, end;
		double time_spent;
};

#endif //_condmatrix_h_
