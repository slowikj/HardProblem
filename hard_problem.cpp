#include <iostream>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class ReversableString
{
private:
	string str, revStr;

public:
	ReversableString(const string& s)
		: str(s)
	{
		this->revStr = s;
		reverse(this->revStr.begin(), this->revStr.end());
	}

	const string& String () const
	{
		return this->str;
	}

	const string& ReversedString () const
	{
		return this->revStr;
	}
};

struct PrefixResult
{
	long long lastUnreversed;
	long long lastReversed;

	PrefixResult (long long unreversed, long long reversed)
		: lastUnreversed(unreversed), lastReversed(reversed)
	{
	}
};

class PrefixInfo
{
	ReversableString lastString;
	PrefixResult result;

public:
	PrefixInfo (const string& last, const PrefixResult& pr)
		: lastString(last), result(pr)
	{
	}

	const string& LastString () const
	{
		return this->lastString.String();
	}

	const string& LastStringReversed () const
	{
		return this->lastString.ReversedString();
	}

	long long ResultWithUnreversedEnd () const
	{
		return this->result.lastUnreversed;
	}

	long long ResultWithReversedEnd () const
	{
		return this->result.lastReversed;
	}
};

class PrefixResultComputer
{
private:
	PrefixInfo previousPrefix;
	int reversingCost;
	ReversableString lastString;

public:
	PrefixResultComputer(const PrefixInfo& prevPref,
						const int& revCost,
						const string& curStr)
		: previousPrefix(prevPref),
		  reversingCost(revCost),
		  lastString(curStr)
	{
	}

private:
	long long ResultWithUnreversedEnd () const
	{
		long long res = LLONG_MAX;

		if (this->lastString.String() >= this->previousPrefix.LastString())
			res = min(res,
					  this->previousPrefix.ResultWithUnreversedEnd());

		if (this->lastString.String() >= this->previousPrefix.LastStringReversed())
			res = min(res,
					  this->previousPrefix.ResultWithReversedEnd());

		return res;
	}

	long long ResultWithReversedEnd () const
	{
		long long res = LLONG_MAX;

		if (this->lastString.ReversedString() >= this->previousPrefix.LastString())
			res = min(res,
					  this->previousPrefix.ResultWithUnreversedEnd());

		if (this->lastString.ReversedString() >= this->previousPrefix.LastStringReversed())
			res = min(res,
					  this->previousPrefix.ResultWithReversedEnd());

		return res == LLONG_MAX ? res
								: res + this->reversingCost;
	}

public:
	PrefixInfo Result () const
	{
		return PrefixInfo(this->lastString.String(),
						  PrefixResult(this->ResultWithUnreversedEnd(),
									   this->ResultWithReversedEnd()));
	}
};

class TaskData
{
private:

	int *cost;
	string *str;
	int numberOfStrings;

	string* GetStringsCopy (const int& numberOfStrings, string *str) const
	{
		string *copiedStr = new string[numberOfStrings];
		for (int i = 0; i < numberOfStrings; ++i)
			copiedStr[i] = str[i];

		return copiedStr;
	}

	int* GetCostsCopy (const int& numberOfStrings, int *cost) const
	{
		int *copiedCosts = new int[numberOfStrings];
		for (int i = 0; i < numberOfStrings; ++i)
			copiedCosts[i] = cost[i];

		return copiedCosts;
	}

	int* ReadCosts () const
	{
		int *res = new int[this->numberOfStrings];
		for (int i = 0; i < this->numberOfStrings; ++i)
			cin >> res[i];

		return res;
	}

	string* ReadStrings () const
	{
		string *res = new string[this->numberOfStrings];
		for (int i = 0; i < this->numberOfStrings; ++i)
			cin >> res[i];

		return res;
	}

public:
	TaskData (const int& numberOfStrings, int *cost, string *str)
	{
		this->numberOfStrings = numberOfStrings;
		this->str = this->GetStringsCopy(numberOfStrings, str);
		this->cost = this->GetCostsCopy(numberOfStrings, cost);
	}

	TaskData ()
	{
		cin >> this->numberOfStrings;
		this->cost = this->ReadCosts();
		this->str = this->ReadStrings();
	}

	~TaskData ()
	{
		delete[] this->cost;
		delete[] this->str;
	}

	const string& String(int index) const
	{
		return this->str[index];
	}

	const int& Cost(int index) const
	{
		return this->cost[index];
	}

	const int& NumberOfStrings() const
	{
		return this->numberOfStrings;
	}
};

class TaskSolver
{
private:
	TaskData taskData;
	
	static const long long NOT_COMPUTED = -5;
	long long result = NOT_COMPUTED;

public:
	TaskSolver (const int& numberOfStrings, int *cost, string *str)
		: taskData(numberOfStrings, cost, str)
	{
	}

	TaskSolver ()
		: taskData()
	{
	}

private:
	long long ResultForEntireSequence () const
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

public:
	long long Result ()
	{
		if (this->result == NOT_COMPUTED)
			this->result = this->ResultForEntireSequence();

		return this->result;
	}
};

int main ()
{
	ios::sync_with_stdio(false);

	TaskSolver ts;
	cout << ts.Result() << endl;

	return 0;
}

