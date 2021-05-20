#include <iostream> 
#include <algorithm> 
#include <vector> 
using namespace std; 

void bucketSort(float *array, int size) {
   vector<float> bucket[size];
   for(int i = 0; i<size; i++)  {          //put elements into different buckets
      bucket[int(size*array[i])].push_back(array[i]);
   }
   for(int i = 0; i<size; i++) {
      sort(bucket[i].begin(), bucket[i].end());       //sort individual vectors
   }
   int index = 0;
   for(int i = 0; i<size; i++) {
      while(!bucket[i].empty()) {
         array[index++] = *(bucket[i].begin());
         bucket[i].erase(bucket[i].begin());
      }
   }
}
int main(){

	int i,size = 6;
	float array[6] = {42,16,84,12,77,26};
	cout << "Array before sorting" << endl;
	for(i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
	int n = 6;
	bucketSort(array,n);

	cout << endl <<  "Array after sorting" << endl;

	for(i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
}