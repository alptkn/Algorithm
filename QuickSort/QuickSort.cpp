#include <iostream>
using namespace std;
void swap(int& num1, int& num2){
	int temp;
	temp = num1;
	num1 = num2;
	num2 = temp;
}

int Partition(int array[],int left,int right){
	int pivot = left;
	int too_big_index = left+1;
	int too_small_index = right;
	int temp;
	
	start: while(array[too_big_index] < array[pivot]){
		too_big_index++;
	}
	while(array[too_small_index] > array[pivot]){
		too_small_index--;
	}
	if(too_big_index < too_small_index){
		temp = array[too_big_index];
		array[too_big_index] = array[too_small_index];
		array[too_small_index] = temp;
	}
	if(too_small_index > too_big_index){
		goto start;
	}
	else{
		temp = array[pivot];
		array[pivot] = array[too_small_index];
		array[too_small_index] = temp;
	}

	return too_small_index;

}
void QuickSort(int array[], int left,int right){
	if(left < right){
		int p = Partition(array,left,right);
		QuickSort(array,left,p-1);
		QuickSort(array,p+1,right);
	}
}



int main(){

	int i,size = 6;
	int array[6] = {14,11,84,54,77,33};
	cout << "Array before sorting" << endl;
	for(i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}

	QuickSort(array,0,5);

	cout << endl <<  "Array after sorting" << endl;

	for(i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
}