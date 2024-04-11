#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;
class Town {
public:
	string name;
	int population;
	float x, y;
	float distance(Town other) {
		return (float)sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
	}
	int getPopulation() {
		return population;
	}
	Town() : name("temp"), population(0), x(0.0), y(0.0){}
};

void printVisited(vector<int> visited, int counter) {
	cout << counter << ". ";
	for (int vis : visited) {
		cout << vis << " ";
	}
	cout << endl;
}

bool isIn(int element, vector<int> elements) {
	for (int i : elements) {
		if (i == element) return true;
	}
	return false;
}

void z1(vector<int> elements, vector<int> visited, vector<vector<int>> *result, int K, int* counter) {
	if (visited.size() == K) {
		printVisited(visited, *counter);
		result->push_back(visited);
		(*counter)++;
		return;
	}
	for (int el : elements) {
		if (isIn(el, visited)) {
			continue;
		}
		visited.push_back(el);
		z1(elements, visited, result, K, counter);
		visited.pop_back();
	}
}

void z2(vector<int> elements, vector<int> visited, vector<vector<int>>* result, int M, int* counter) {
	if (visited.size() == M) {
		printVisited(visited, *counter);
		result->push_back(visited);
		(*counter)++;
		return;
	}
	for (int el : elements) {
		if (visited.size() != 0) {
			bool v = false;
			for (int vis : visited) {
				if (el < vis) v = true;
			}
			if (v) continue;
		}
		visited.push_back(el);
		z2(elements, visited, result, M, counter);
		visited.pop_back();
	}
}

int main() {
	int N = 4, M = 2, K = 2;
	string myText;
	vector<Town> towns;
	ifstream MyReadFile("cities.txt");
	while (getline(MyReadFile, myText)) {
		int count = 0;
		istringstream iss(myText);
		string s;
		Town town;
		if (!isdigit(myText[0])) continue;
		while (getline(iss, s, ' ')) {
			if (count == 0) {
				count++;
				continue;
			}
			else if (count == 1) town.name = s;
			else if (count == 2) town.population = stoi(s);
			else if (count == 3) town.x = stof(s);
			else if (count == 4) town.y = stof(s);
			count++;
		}
		towns.push_back(town);
	}
	vector<int> visited;
	vector<int> elements(N);
	for (int i = 0; i < N; i++) {
		elements[i] = i + 1;
	}
	vector<vector<int>> result;
	int counter = 1;
	z1(elements, visited, &result, K, &counter);
	vector<Town> bestPath;
	float bestTime = 9999999.0;
	for (vector<int> path : result) {
		float currTime = 0.0;
		Town currTown, prevTown;
		for (int i = 1; i < path.size(); i++) {
			currTown = towns[path[i] - 1];
			prevTown = towns[path[i - 1] - 1];
			currTime += currTown.distance(prevTown);
		}
		currTime += currTown.distance(towns[path[0] - 1]);
		if (currTime < bestTime) {
			bestTime = currTime;
			bestPath.clear();
			for (int town : path) {
				bestPath.push_back(towns[town - 1]);
			}
		}
	}
	cout << "The shortest cycle-path is: ";
	for (Town town : bestPath) {
		cout << town.name << " ";
	}
	cout << "with distance: " << bestTime << endl;
	result.clear();
	counter = 1;
	z2(elements, visited, &result, M, &counter);
	vector<Town> bigAvgPop;
	float biggestAvg = -0.1;
	for (vector<int> path : result) {
		float currAvg = 0.0;
		Town currTown, prevTown;
		for (int i = 0; i < path.size(); i++) {
			currTown = towns[path[i] - 1];
			currAvg += currTown.getPopulation();
		}
		currAvg /= M;
		if (currAvg > biggestAvg) {
			biggestAvg = currAvg;
			bigAvgPop.clear();
			for (int town : path) {
				bigAvgPop.push_back(towns[town - 1]);
			}
		}
	}
	cout << "The subset with the biggest AVG population is: ";
	for (Town town : bigAvgPop) {
		cout << town.name << " ";
	}
	cout << "with AVG: " << biggestAvg << endl;
	return 0;
}