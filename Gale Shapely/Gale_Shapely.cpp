#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int findIndex(int val, vector<int> arr)
{
	for(int i = 0; i < arr.size(); i++)
	{
		if(val == arr[i])
			return i;
	}
	return -1;
}
/*

void GaleShapley(vector<vector<int>> pref1, vector<vector<int>> pref2)
{
	int free = pref1.size();
	int n = pref1.size();
	vector<int> match1(free,-1);
	vector<int> match2(free,-1);

	int newH, oldH;
	int resident;

	int i;

	while(free > 0)
	{
		for(i = 0; i < n; i ++)
		{
			if(match1[i] == -1)
				break;
		}

		for(int j = 0; j < n; j++)
		{
			resident = pref1[i][j];
			if(match2[resident] == -1)
			{
				match1[i] = resident;
				match2[resident] = i;
				free--;
				break;
			}
			else
			{

			}
		}



	}




}

*/



void print(vector<vector<int>> p)
{
	for(int i = 0; i < p.size(); i++)
		{
			for(int j = 0; j < p[i].size(); j++)
			{
				cout << p[i][j] << " ";
			}
			cout << endl;
		}
}

int main(void)
{
	ifstream hospitalsFile,residentsFile;
	hospitalsFile.open("hospitals.txt");
	residentsFile.open("residents.txt");

	int n,temp;

	hospitalsFile >> n;
	residentsFile >> n;


	vector<int> h,r;
	vector<vector<int>> hospitals,residents;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			hospitalsFile >> temp;
			h.push_back(temp);
			residentsFile >> temp;
			r.push_back(temp);
		}
		hospitals.push_back(h);
		h.clear();
		residents.push_back(r);
		r.clear();
	}

	print(hospitals);
	cout << endl;
	print(residents);
	return 0;
}