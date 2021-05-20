#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

int max_num = 0;

class Event{
	string event_name;
	char type;
	int strat_event;
	int end_event;
	public:
		string get_name();
		int get_start_event();
		int get_end_event();
		char get_type();
		void set_name(string name);
		void set_start_time(int time);
		void set_end_time(int time);
		void set_type(char type);
};
string Event::get_name(){
	return event_name;
}

int Event::get_start_event(){
	return strat_event;
}
int Event::get_end_event(){
	return end_event;
}
char Event::get_type(){
	return type;
}
void Event::set_name(string name){
	event_name = name;
}
void Event::set_start_time(int time){
	strat_event = time;
}
void Event::set_end_time(int time){
	end_event = time;
}
void Event::set_type(char a){
	type = a;
}


int determine_size(string filename){
	fstream file;
	string word;
	int count = 0;
	file.open(filename.c_str());
	while(file >> word)
		count++;
	
	file.close();

	return count/3;	


}
void fill_array(int *array, Event *event,char *type,int size){
	int i = 0;
	int j = 0;
	string str;
	while(i < size){
		array[i] = event[j].get_start_event();
		type[i] = event[j].get_type();
		i++;
		array[i] = event[j].get_end_event();
		type[i] = event[j].get_type();
		i++;
		j++; 
	}
			
}

void read_event(Event *event,string filename){
	fstream file;
	string word;
	stringstream stream;
	int temp,i = 0;
	file.open(filename.c_str());
	while(file >> word){
		event[i].set_type(word[6]);
		event[i].set_name(word);
		file >> word;
		stream.str(word);
		stream >> temp;
		max_num = (temp > max_num) ? temp:max_num;
		stream.clear();
		event[i].set_start_time(temp);
		file >> word;
		stream.str(word);
		stream >> temp;
		max_num = (temp > max_num) ? temp:max_num;
		stream.clear();
		event[i].set_end_time(temp);
		i++;	
	}

	file.close();
}


void heapify(int arr[], int n, int i,char *type) 
{ 
    int smallest = i; // Initialize smalles as root 
    int l = 2 * i + 1; // left = 2*i + 1 
    int r = 2 * i + 2; // right = 2*i + 2 
  
    if (l < n && arr[l] < arr[smallest])    // If left child is smaller than root
        smallest = l; 
  
    if (r < n && arr[r] < arr[smallest])    // If right child is smaller than smallest so far 
        smallest = r; 
  
    if (smallest != i) {                   // If smallest is not root 
        swap(arr[i], arr[smallest]); 
        swap(type[i],type[smallest]);
        
        heapify(arr, n, smallest,type); //Recursively heapify the affected sub-tree/
    } 
} 


void find_operation(Event *event, char type,int value, char *response,int size){
	string temp;
	for(int i = 0; i < size; i++){
		if(event[i].get_type() == type){
			if(value == event[i].get_start_event())
				cout <<"Time "  << value << " "<< event[i].get_name() << " is start!" << endl;
			if(event[i].get_end_event() == value){
				cout <<"Time "  << value << " "<< event[i].get_name() << " is end!" << endl;
			}	
		}
	}
}

void heapSort(int *arr, int n,char *type) 
{ 
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i,type);
  
    // One by one extract an element from heap 
    for (int i = n - 1; i >= 0; i--) { 
        // Move current root to end 
        swap(arr[0], arr[i]); 
        swap(type[0],type[i]);
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0,type); 
    } 
} 

void deletion(int arr[],int& n,char *type){
    int lastelement = arr[0];
    char lascharacter = type[0];
    arr[n-1] = lastelement;
    type[n-1] = lascharacter;

    n = n-1;

    heapify(arr,n,n-1,type);
}  

int main(int argv, char **argc){
	string filename = argc[1];
	int size = determine_size(filename);
	int n = size*2;
	Event *event = new Event[size];
	char *event_type = new char[n];
	int *array = new int[n];
	
	int clock = 0;
	read_event(event,filename);
	char *response = new char(30);
	
	fill_array(array,event,event_type,n);
	heapSort(array,n,event_type);
	


	for(int i = 0; i <= max_num; i++){

		if(array[n-1] == clock){
			while(array[n-1] == clock){
				find_operation(event,event_type[n-1],array[n-1],response,size);
				deletion(array,n,event_type);
			}
		}
		else
			cout << "Time" << " " << clock << ":"<<" No event!" <<endl;	
		

		if(n == 0){

			cout << "Time" << " " << clock << ":"<<" No more event,schedular exit" << endl;
			break;
		}
		clock++;

	}
	

	 
	
		}
	