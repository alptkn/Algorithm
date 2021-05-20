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

int findMaxProfit(vector<Job> Jobs, int n){
	sort(Jobs.begin(), Jobs.end(), jobComparator);
	vector<int> table(n);
	table[0] = Jobs[0].profit;

	for(int i = 1; i < n; i++){
		int inclprof = Jobs[i].profit;
		int l = latestNonConflict(Jobs, i);
		if(l != -1)
			inclprof += table[l];

		table[i] = max(inclprof, table[i-1]);
	}
	int result = table[n-1];
	return result;
}


int main(void){
	vector<Job> Jobs = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
	cout << "The optimal profit is : " << findMaxProfit(Jobs, Jobs.size());
}