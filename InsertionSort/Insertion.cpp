#include <iostream>

using namespace std;

void insertionsort(int arr[], int n){
	int i,j,key;
	for(i = 1; i < n; i++){

		key = arr[i];
		j = i - 1;

		while((j >= 0) && (arr[j] > key)){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}
}

void printArray(int arr[], int n)  
{  
    int i;  
    for (i = 0; i < n; i++)  
        cout << arr[i] << " ";  
    cout << endl; 
}   
int main(){

	int arr[] = { 12, 11, 13, 5, 6 };  
    int n = sizeof(arr) / sizeof(arr[0]);  
  
    insertionsort(arr, n);  
    printArray(arr, n);  
  
    return 0;  

}