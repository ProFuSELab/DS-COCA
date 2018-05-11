#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

vector<vector<bool> > spe_matrix;
vector<vector<bool> > A_vals;
vector<double> focal_element;
vector<double> conditioned_element;
double Nlz = 0.0;
int cur_fod = 0, arr[20];

void A_props(int start, int tot, int k)
{
	//  cout << start << " " << tot << " " << k << endl;
	vector <bool> a;
	if (k == 0)
	{   
		//cnt++;
		for (int i = 0; i < tot; i++)
		{   
			a.push_back(arr[i]);
			//cout << arr[i] << " ";
		}   
		//cout << endl;
		A_vals.push_back(a);
		return;
	}   
	for (int i = start; i <= (tot - k); i++)
	{   
		arr[i] = 1;
		A_props(i + 1, tot, k - 1); 
		arr[i] = 0;
	}   
}

void init_mat(int i)
{
	Nlz = 0.0;
	cur_fod = i;
	vector<bool> row;
	spe_matrix.clear();
	row.assign(pow(2, i), 0);
	spe_matrix.assign(pow(2, i), row);
	//cout << endl;
	//cout << spe_matrix.size() << endl;
}

void create_A_props()
{
	A_vals.clear();
	for (int t = 1; t <= cur_fod; t++)
		A_props(0, cur_fod, t);
}

void print_A_props()
{
	cout << endl;
	for (int i = 0; i < A_vals.size(); i++)
	{
		for (int j = 0; j < A_vals[i].size(); j++)
			cout << A_vals[i][j] << " ";
		cout << endl;
	}
}

void rand_focals()
{
	focal_element.clear();
	focal_element.assign(pow(2, cur_fod), 0.0);
	conditioned_element.clear();
	conditioned_element.assign(pow(2, cur_fod), 0.0);
	for (int i = 1; i < pow(2, cur_fod); i++)
	{
		focal_element[i] = (i) / 10000.0;
		Nlz += focal_element[i];
	}
}

void print_focals()
{
	cout << endl;
	for (int i = 0; i < pow(2, cur_fod); i++)
		cout << focal_element[i] << " ";
	cout << endl;
}

void print_conditioned_values()
{
	cout << endl;
	for (int i = 0; i < pow(2, cur_fod); i++)
		cout << conditioned_element[i] << " ";
	cout << endl;
}

void print_mat()
{
	cout << endl;
	for (int i = 0; i < pow(2, cur_fod); i++)
	{
		for (int j = 0; j < pow(2, cur_fod); j++)
		{
			cout << spe_matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void print_nlz()
{
	cout << endl;
	cout << "Nlz : " << Nlz << endl;
}

void prep_spe(int a)
{
	for (int i = 0; i < pow(2, cur_fod); i++)
		for (int j = i; j < pow(2, cur_fod); j++)
			if (i == (j & a))
				spe_matrix[i][j] = 1;
}

void spe_multi()
{
	for (int i = 0; i < pow(2, cur_fod); i++)
		for (int j = i; j < pow(2, cur_fod); j++)
			if (spe_matrix[i][j])
				conditioned_element[i] += focal_element[j];
}

void normalized()
{
	if (conditioned_element[0] > 0)
	{
		for (int i = 1; i < conditioned_element.size(); i++)
			conditioned_element[i] /= (Nlz - conditioned_element[0]);	
		conditioned_element[0] = 0.0;
	}
}

int prop_int_val(int rand_prop)
{
	int ret = 0;
	for (int i = 0; i < A_vals[rand_prop].size(); i++)
		if (A_vals[rand_prop][i])
			ret += pow(2, i);
	//cout << ret << endl;
	return ret;	
}

int main()
{
	double total_time = 0.0;
	clock_t cond_begin, cond_end;
	int roundct = 0;
	int rand_prop = 0;
	srand(time(NULL));
	
	for (int fod = 2; fod <= 8; fod = fod + 2)
	{
		total_time = 0.0;
		roundct = 0;
		for (int rounds = 1; rounds <= 10000; rounds++)
		{
			roundct++;
			init_mat(fod);	
			//print_mat();
			rand_focals();
			create_A_props();
			rand_prop = rand() % A_vals.size();
			cond_begin = clock();
			prep_spe(prop_int_val(rand_prop));
			//print_mat();
			//print_focals();
			//print_nlz();
			//print_A_props();
			spe_multi();
			//print_conditioned_values();
			normalized();
			//print_conditioned_values();
			cond_end = clock();
			total_time += (double)(cond_end - cond_begin) / CLOCKS_PER_SEC;
		}
		cout << "Fod size: " << fod << "\tRounds: " << roundct << "\t\tAverage Time spent: " << (total_time / roundct) * 1000000 << endl;
	}
	
	return 0;
}
