 #include <vector>
#include <iostream>

using namespace std;

int countSplitInv(vector<int> &vec, int left, int mid, int right){
    vector<int> b(right + 1);
    int count = 0;
    int k, i, j, h;
    k = left;
    i = left;
    j = mid+1;

    while((k <= mid) && (j <= right)){

        if(vec[k] < vec[j]){
            b[i] = vec[k];
            k++;
        }
        else{
            b[i] = vec[j];
            count += mid - k + 1;
            j++;
        }
        i++;
    }
    if(k > mid){
        for(h = j; h <= right; h++){
            b[i] = vec[h];
            i++;
        }
    }
    else{
        for(h = k; h <= mid; h++){
            b[i] = vec[h];
            i++;
        }
    }
    for(h = left; h <= right; h++){
        vec[h] = b[h];
    }
    return count;
}



int sort_and_count(vector<int> &vec, int left,int right ){
    int count = 0;
    if(left < right){
        int mid = (left + right ) / 2;
        count += sort_and_count(vec, left, mid);
        count += sort_and_count(vec, mid + 1, right);
        count += countSplitInv(vec, left, mid, right);
    }
    return count;
}



int main(void){

    vector<int> vec = {1,5,4,8,10,2,6,9,12,11,3,7};
    cout << "Number of inversions " << sort_and_count(vec, 0, vec.size() - 1) << endl;
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i] << " " ;
}