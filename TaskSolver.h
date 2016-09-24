//#pragma once

#include <string>
#include "TaskData.h"
#include "PrefixResultComputer.h"

using namespace std;

class TaskSolver
{
private:
	TaskData _taskData;
	
	static const long long NOT_COMPUTED = -5;
	long long _result = NOT_COMPUTED;

public:
	TaskSolver (const int& numberOfStrings, int *cost, string *str);
	TaskSolver ();

private:
	long long _ResultForEntireSequence () const;

public:
	long long Result ();
};
