#include <iostream>
using namespace std;

int main()
{
	int array[6] = {42,16,84,12,77,26};
	int i,j,k;
	int temp;
	int size = 6;

	cout << "Array before sorting" << endl;
	for(i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}

	for(i = 0; i <= size-2; i++  )
	{
		j = i; 
		for(int k = i + 1; k <= size-1; k++)
		{
			if(array[k] < array[j])
				j = k;
		}

		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}

	cout << endl <<  "Array after sorting" << endl;

	for(i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
}