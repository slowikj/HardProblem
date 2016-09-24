#include "TaskData.h"
#include <algorithm>

using namespace std;

TaskData::TaskData (const int& numberOfStrings, const int *costs, const string *str)
{
	_costs.assign(costs, costs + numberOfStrings);
	_str.assign(str, str + numberOfStrings);
}

TaskData::TaskData ()
{
	int numberOfStrings;
	cin >> numberOfStrings;

	_costs = _GetReadCosts(numberOfStrings);
	_str = _GetReadStrings(numberOfStrings);
}

vector<int> TaskData::_GetReadCosts (const int& numberOfCosts)
{
	return move(_GetReadSequence<int>(numberOfCosts));
}

vector<string> TaskData::_GetReadStrings (const int& numberOfStrings)
{
	return move(_GetReadSequence<string>(numberOfStrings));
}

template <class T>
vector<T> TaskData::_GetReadSequence (const int& n)
{
	vector<T> res(n);	
	for_each(res.begin(), res.end(),
			 [](T& elem)->void
			 {
			 	cin >> elem;
			 }
			);

	return move(res);
}

const string& TaskData::String (const int& index) const
{
	return _str[index];
}

const int& TaskData::Cost (const int& index) const
{
	return _costs[index];
}

int TaskData::NumberOfStrings () const
{
	return _str.size();
}
