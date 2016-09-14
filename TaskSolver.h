//#pragma once

#include <string>
#include "TaskData.h"
#include "PrefixResultComputer.h"

using namespace std;

class TaskSolver
{
private:
	TaskData taskData;
	
	static const long long NOT_COMPUTED = -5;
	long long result = NOT_COMPUTED;

public:
	TaskSolver (const int& numberOfStrings, int *cost, string *str);
	TaskSolver ();

private:
	long long ResultForEntireSequence () const;

public:
	long long Result ();
};
