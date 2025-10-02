#include "Task.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include<algorithm>
using namespace std;

void SaveTasksToFile(const vector<Task>& tasks, const string& FileName)
{
	ofstream ostream(FileName);
	ostream << tasks.size();

	for (const Task& task: tasks) {
		string description = task.Get_Description();
		replace(description.begin(), description.end(), ' ', '_');
		ostream << '\n' << description << ' ' << task.Get_Done();
	}
}

vector<Task> LoadTasksFromFile(const string& FileName)
{
	if (!filesystem::exists(FileName)) {
		return vector<Task>();
	}
	vector <Task>tasks;
	ifstream istream(FileName);

	int n;
	istream >> n;
	for (int i = 0; i < n; i++) {
		string description;
		bool done;
		istream >> description >> done;
		replace(description.begin(), description.end(), '_', ' ');
		tasks.push_back(Task{ description,done });
	}
	return tasks;
}
