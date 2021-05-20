#include <iostream>
#include <vector>

using namespace std;


int KnapsackRec(vector<int> items, vector<int> weights, int size, int W, vector<vector<int>> dp){
	if(size < 0)
		return 0;

	if(dp[size][W] != -1)
		return dp[size][W];

	if(weights[size] > W){
		dp[size][W] = KnapsackRec(items, weights, size - 1, W, dp);
		return dp[size][W];
	}
	else{
		dp[size][W] = max(items[size] + KnapsackRec(items, weights, size - 1, W - weights[size], dp), KnapsackRec(items, weights, size - 1, W, dp));
		return dp[size][W];
	}
}


int Knapsack(vector<int> items, vector<int> weights, int size, int W){
	vector<vector<int>> dp(size);
	for(int i = 0; i < size; i++)
		dp[i].resize(W + 1);

	for(int i = 0; i < size; i++)
        for(int j = 0; j < W + 1; j++)
            dp[i][j] = -1;

	return KnapsackRec(items, weights, size - 1, W, dp);
}

int main(void){
	vector<int> items = {10, 20, 30};
	vector<int> weights = {1,1,1};
	int W = 2;
	cout << Knapsack(items, weights, items.size(), W);
}