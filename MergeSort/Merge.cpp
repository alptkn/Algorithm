#include <iostream>
using namespace std;

void Merge(int a[], int low, int mid,int high){

	int k,i,j,h;
	k = low;
	i = low;
	j = mid+1;
	int b[6];

	while((k <= mid) && (j <= high)){

		if(a[k] < a[j]){
			b[i] = a[k];
			k++;
		}
		else{
			b[i] = a[j];
			j++;
		}
		i++;
	}

	if(k > mid){
		for(h = j; h <= high; h++){
			b[i] = a[h];
			i++;
		}
	}
	else{
		for(h = k; h <= mid; h++){
			b[i] = a[h];
			i++;
		}
	}
	for(h = low; h <= high; h++){
		a[h] = b[h];
	}
}

void MergeSort(int *array, int low, int high){
	if(low < high){
		int mid = (high + low) / 2;
		MergeSort(array,low,mid);
		MergeSort(array,mid+1,high);
		Merge(array,low,mid,high);
	}
}

int main(){


	int array[6] = {42,16,84,12,77,26};
	int i,j,k;
	int temp;
	int size = 6;

	cout << "Array before sorting" << endl;
	for(i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}

	MergeSort(array,0,5);

	cout << endl <<  "Array after sorting" << endl;

	for(i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}

}