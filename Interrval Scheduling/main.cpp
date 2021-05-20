#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void SelectActivities(vector<int>s,vector<int>f){
	vector<pair<int,int>> answer;
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>p;
	for(int i = 0; i < s.size(); i++)
		p.push(make_pair(f[i], s[i]));

	auto it = p.top();
	int start = it.second;
	int end = it.first;
	p.pop();
	answer.push_back(make_pair(start, end));

	while(!p.empty()){
		auto itr = p.top();
		p.pop();
		if(itr.second >= end){
			start = itr.second;
			end = itr.first;
			answer.push_back(make_pair(start, end));
		}
	}
	cout << "Following Activities should be selected. " << endl << endl; 
  
    for(auto itr=answer.begin();itr!=answer.end();itr++){ 
        cout << "Activity started at: " << (*itr).first << " and ends at  " << (*itr).second << endl; 
    } 

}	
int main(void){

	vector<int>s = {1, 3, 0, 5, 8, 5}; 
    vector<int>f = {2, 4, 6, 7, 9, 9}; 
    SelectActivities(s,f); 
  
    return 0; 
}