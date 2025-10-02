#pragma once
#include <string>
#include <vector>
using namespace std;


class Task
{
private:
	string description;
	bool done;
public:
	Task(const string& desk="", bool isDone = false) {
		description = desk;
		done = isDone;
	}
	string Get_Description() const {return description;}
	bool Get_Done() const { return done; }

	void Set_Description(const string& desk) { description = desk; }
	void Set_Done(bool isDone) { done = isDone; }




};
void SaveTasksToFile(const vector<Task>& tasks, const string& FileName);
vector<Task> LoadTasksFromFile(const string& FileName);
