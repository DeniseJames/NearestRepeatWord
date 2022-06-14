#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <chrono>
#include <iomanip>
#include <unordered_map>
#include <vld.h>

using namespace std;

// NEAREST REPEATED ENTRY IN AN ARRAY
vector<pair<string, int>> repeatedEntry(vector<string> & v)
 {
	 pair<string, int> wordDistances;
	 vector<pair<string, int>> vectorWordDistances;
	 // take the first elem in vector
	 // find its duplicate and make a pair
	 // go through each one in list
	 for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
	 {
		 for (vector<string>::iterator iter = it+1; iter != v.end(); ++iter)
		 {
			 if (*it == *iter && distance(it, iter)!=0)
			 {
				 // get the distance
				 int distanceBetween = distance(it, iter);
				 wordDistances = make_pair(*iter, distanceBetween);
				 vectorWordDistances.push_back(wordDistances);
			 }
		 }
	 }
	 return vectorWordDistances;
 }

// Min function of the pair of words and distance

pair<string, int> min_distance(vector<pair<string, int>> &v)
{
	pair<string, int> min{ "notFound",100000000};
	for (auto elem: v)
	{
		if (elem.second < min.second)
		{
			min.second = elem.second;
			min.first = elem.first;
		}
	}
	return min;
}

// print vector function
void print_vector(vector<pair<string, int>> v)
{
	for (auto elem:v)
	{
		cout << "The word "<< elem.first << 
			" has distance of  " << elem.second<<endl;
	}
}

int nearestEntry(vector<string> arr)
{
	typedef unordered_map<string, int> hashmap;
	hashmap dict;
	int minDist = INT_MAX;  // INT_MAX is STL constant 2147483647
	for (int i = 0; i < arr.size(); i++)
	{
		if (dict.find(arr[i]) != dict.end())
		{
			minDist = min(minDist, i - dict.find(arr[i])->second);
		}
		dict[arr[i]] = i;
	}
	return minDist;
}

int main()
{
	
	vector<string> vec = {
		"All", "work", " and ", "no", "play", "makes", "for","no",
		"fun", " and ", "no", "results" };
	auto start = std::chrono::high_resolution_clock::now();
	vector<pair<string, int>> word_distances;
	// Get the distances between repeated words
	word_distances = repeatedEntry(vec);
	// Get the minimum distance in the vector
	pair<string, int> returned_min_distance;
	returned_min_distance = min_distance(word_distances);
	cout << endl<<"The word with the shortest distance is " << returned_min_distance.first <<
		" and the distance is " << returned_min_distance.second<< endl;
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop - start;
	std::cout << "Time to execute for the O(n*n) algo " << std::setw(9)
		 << " is : " << diff << " s\n";

	auto start2 = std::chrono::high_resolution_clock::now();
	int shortestDistance = nearestEntry(vec);
	cout << "The shortest distance between repeated words is: " << shortestDistance << endl;
	auto stop2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff2 = stop2 - start2;
	std::cout << "Time to execute for the map algo " << std::setw(9)
		<< " is : " << diff2 << " s\n";
	return 0;

}

