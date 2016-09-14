#include "TaskSolver.h"

TaskSolver::TaskSolver (const int& numberOfStrings, int *cost, string *str)
	: taskData(numberOfStrings, cost, str)
{
}

TaskSolver::TaskSolver ()
	: taskData()
{
}

long long TaskSolver::ResultForEntireSequence () const
{
	PrefixInfo prefixInfo(this->taskData.String(0),
						  PrefixResult(0, this->taskData.Cost(0)));

	int sequenceLength = this->taskData.NumberOfStrings();
	for (int i = 1; i < sequenceLength; ++i)
	{
		prefixInfo = PrefixResultComputer(prefixInfo,
										  this->taskData.Cost(i),
										  this->taskData.String(i)
										 ).Result();
	}

	long long res = min(prefixInfo.ResultWithUnreversedEnd(),
						prefixInfo.ResultWithReversedEnd());

	return res == LLONG_MAX ? -1 : res;
}

long long TaskSolver::Result ()
{
	if (this->result == NOT_COMPUTED)
		this->result = this->ResultForEntireSequence();

	return this->result;
}
