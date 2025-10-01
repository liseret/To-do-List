#pragma once
#include <string>
#include <vector>
using namespace std;


class Task
{
public:
	string description;
	bool done;
};
void SaveTasksToFile(const vector<Task>& tasks, const string& FileName);
vector<Task> LoadTasksFromFile(const string& FileName);
