#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int findIndex(int val, vector <includent> arr){
    for (int i = 0; i < arr.size(); i++){
        if (val == arr[i]){
            return i;
        } 
    }
    return -1;
}


void GaleShapley(vector<vector <int> > pref1, vector<vector <int> > pref2){
    int free = pref1.size();
    int n = pref1.size();
    vector<int> match1(free,-1);
    vector<int> match2(free,-1);

    int newH, oldH;
    int resident;

    int i;

    while(free > 0){
        //Find the first available one
        for(i=0; i<n;i++){
            if(match1[i] == -1){
                break;
            }
        }
        
        for(int j=0;j<n;j++){
            //Find the first valid one to match
            resident = pref1[i][j];
            //If available, then match
            if(match2[resident] == -1){
                match1[i] = resident;
                match2[resident] = i;
                free--;
                break;
            }
            //If not, compare
            else{
                newH = findIndex(i, pref2[resident]);
                oldH = findIndex(match2[resident], pref2[resident]);
                
                //Compare the preferences
                if(newH < oldH){
                    match1[i] = resident;
                    match1[match2[resident]] = -1;
                    match2[resident] = i;
                    break;
                }
            }
        }
        
    }
    cout << "STABLE MATCHING" << endl;
    for(int i = 0; i<n; i++){
        cout << "Hospital: " << i << ", Resident: " << match1[i] << endl;
    }
};

void print(vector<vector <int> > p){
    for(int i=0; i<p.size();i++){
        for(int j=0; j<p[i].size();j++){
            cout << p[i][j] << " ";
        }
        cout << endl;
    }
};

int main(){
    ifstream hospitalsFile, residentsFile;
    hospitalsFile.open("hospitals.txt");
    residentsFile.open("residents.txt");
    
    int n;
    int temp;
    
    hospitalsFile >> n;
    residentsFile >> n;


    vector<int> h, r;
    vector<vector <int> > hospitals, residents;
    
    for(int i=0; i<n;i++){
        for(int j=0;j<n;j++){
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

    GaleShapley(hospitals, residents);
        
    return 0;
}