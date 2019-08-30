// C++ program for the illustration of 
// map::emplace() function 
#include <bits/stdc++.h> 
using namespace std; 

int main() 
{ 

	// initialize container 
	map<int, int> mp; 

	// insert elements in random order 
	int lb = mp.emplace(2, 30); 
    
	mp.emplace(1, 40); 
	mp.emplace(2, 20); 
	mp.emplace(1, 50); 
	mp.emplace(4, 50); 

	// prints the elements 
	cout << "\nThe map is : \n"; 
	cout << "KEY\tELEMENT\n"; 
	for (auto itr = mp.begin(); itr != mp.end(); itr++) 
		cout << itr->first << "\t" << itr->second << endl; 

	return 0; 
} 
