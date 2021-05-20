#include <iostream>
#include <vector>

using namespace std;

int Knapsak(vector<int> items, vector<int> weights, int size, int W){
	vector<vector<int>> M(size + 1);

	for(int i = 0; i < size + 1; i++)
		M[i].resize(W + 1);

	for(int i = 0; i < W + 1; i++)
		M[0][i] = 0;

	for(int i = 1; i < M.size(); i++){
		for(int w = 0; w < M[i].size(); w++)
		{
			if(weights[i] > W)
				M[i][w] = M[i-1][w];
			else
				M[i][w] = max(items[i] + M[i - 1][W - weights[i]], M[ i- 1][w] );
		}
	}
	return M[size][W];	
}


int main(void){
	vector<int> items = {10, 20, 30};
	vector<int> weights = {1,1,1};
	int W = 2;
	cout << Knapsak(items, weights, items.size(), W);
}