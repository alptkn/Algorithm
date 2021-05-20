#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job{
	int start, finish, profit;
};

bool jobComparator(Job s1, Job s2){
	return (s1.finish < s2.finish);
}

int latestNonConflict(vector<Job> Jobs, int i){
	for(int j = i - 1; j >= 0; j--){
		if(Jobs[j].finish <= Jobs[i].start)
			return j;
	}
	return -1;
}

int M_Compute_Opt(int j, vector<int> M, vector<Job> Jobs, vector<int> p){
	M[j] = max(M_Compute_Opt(j-1), Jobs[j].profit + M_Compute_Opt(p[j]));
	return M[j];
}

int findMaxProfit(vector<Job> Jobs, int n){
	sort(Jobs.begin(), Jobs.end(), jobComparator);
	vector<int> p(Jobs.size(),0);
	for(int i = 0; i < p.size(); i++)
		p.push_back(latestNonConflict(Jobs,i));
	vector M<int> (Jobs.size(),0);

	return M_Compute_Opt(j, M, Jobs, p);
}


int main(void){
	vector<Job> Jobs = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
	cout << "The optimal profit is : " << findMaxProfit(Jobs, Jobs.size());
}