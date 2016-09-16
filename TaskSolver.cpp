#include "TaskSolver.h"

TaskSolver::TaskSolver (const int& numberOfStrings, int *cost, string *str)
	: _taskData(numberOfStrings, cost, str)
{
}

TaskSolver::TaskSolver ()
	: _taskData()
{
}

long long TaskSolver::_ResultForEntireSequence () const
{
	PrefixInfo prefixInfo(_taskData.String(0),
						  PrefixResult(0, _taskData.Cost(0)));

	int sequenceLength = _taskData.NumberOfStrings();
	for (int i = 1; i < sequenceLength; ++i)
	{
		prefixInfo = PrefixResultComputer(prefixInfo,
										  _taskData.Cost(i),
										  _taskData.String(i)
										 ).Result();
	}

	long long res = min(prefixInfo.ResultWithUnreversedEnd(),
						prefixInfo.ResultWithReversedEnd());

	return res == LLONG_MAX ? -1 : res;
}

long long TaskSolver::Result ()
{
	if (_result == NOT_COMPUTED)
		_result = _ResultForEntireSequence();

	return _result;
}
