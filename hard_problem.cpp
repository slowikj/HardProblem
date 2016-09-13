#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class TaskSolver
{
private:
	static const int MAXN = 1e5;
	static const int MAXCOST = 1e9;
	static const long long INF = (long long)MAXN * MAXCOST + 10;
	static const long long NOT_COMPUTED = -INF;

	int *cost;
	string *str;
	string *revStr;
	int numberOfStrings;
	long long result;

	string* GetStringsCopy (const int& numberOfStrings, string *str)
	{
		string *copiedStr = new string[numberOfStrings];
		for (int i = 0; i < numberOfStrings; ++i)
			copiedStr[i] = str[i];

		return copiedStr;
	}

	int* GetCostsCopy (const int& numberOfStrings, int *cost)
	{
		int *copiedCosts = new int[numberOfStrings];
		for (int i = 0; i < numberOfStrings; ++i)
			copiedCosts[i] = cost[i];

		return copiedCosts;
	}		

public:
	TaskSolver (const int& numberOfStrings, int *cost, string *str)
	{
		this->numberOfStrings = numberOfStrings;
		this->str = this->GetStringsCopy(numberOfStrings, str);
		this->cost = this->GetCostsCopy(numberOfStrings, cost);

		this->revStr = nullptr;
		this->result = NOT_COMPUTED;
	}

	~TaskSolver ()
	{
		delete[] this->cost;
		delete[] this->str;

		if (this->revStr)
			delete[] this->revStr;
	}

private:
	struct PrefixResult
	{
		long long lastUnreversed;
		long long lastReversed;

		PrefixResult (long long unreversed = INF, long long reversed = INF)
			: lastUnreversed(unreversed), lastReversed(reversed)
		{
		}
	};

	long long GetResultForPrefixWithUnreversedEnd (const int& endIndex,
												   const PrefixResult& previousPrefix)
	{
		long long res = INF;

		if (this->str[endIndex] >= this->str[endIndex - 1])
			res = min(res,
					  previousPrefix.lastUnreversed);

		if (this->str[endIndex] >= this->revStr[endIndex - 1])
			res = min(res,
					  previousPrefix.lastReversed);

		return res;
	}	

	long long GetResultForPrefixWithReversedEnd (const int& endIndex,
												 const PrefixResult& previousPrefix)
	{
		long long res = INF;

		if (this->revStr[endIndex] >= this->str[endIndex - 1])
			res = min(res,
					  previousPrefix.lastUnreversed
						+ this->cost[endIndex]);

		if (this->revStr[endIndex] >= this->revStr[endIndex - 1])
			res = min(res,
					  previousPrefix.lastReversed
						+ this->cost[endIndex]);

		return res;
	}

	string* GetReversedStrings ()
	{
		string *res = new string[this->numberOfStrings];
		for (int i = 0; i < this->numberOfStrings; ++i)
		{
			res[i] = this->str[i];
			reverse (res[i].begin(), res[i].end());
		}

		return res;
	}

	PrefixResult GetPrefixResult ()
	{
		this->revStr = this->GetReversedStrings();
		PrefixResult previousRes(0, this->cost[0]), currentRes;
		
		for (int i = 1; i < this->numberOfStrings; ++i)
		{
			currentRes = PrefixResult(this->GetResultForPrefixWithUnreversedEnd(i, previousRes),
							 		  this->GetResultForPrefixWithReversedEnd(i, previousRes));

			previousRes = currentRes;
		}

		return currentRes;
	}

public:
	long long Result ()
	{
		if (this->result == NOT_COMPUTED)
		{
			PrefixResult pr = this->GetPrefixResult();
			this->result = min(pr.lastUnreversed,
							   pr.lastReversed);
			this->result = (this->result == INF ? (long long)-1 : this->result);
		}

		return this->result;
	}
};


void ReadStrings (const int& n, string str[])
{
	for (int i = 0; i < n; ++i)
		cin >> str[i];
}

void ReadCosts (const int& n, int cost[])
{
	for (int i = 0; i < n; ++i)
		cin >> cost[i];
}

int main ()
{
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	int cost[n];
	string str[n];
	ReadCosts(n, cost);
	ReadStrings(n, str);

	TaskSolver ts(n, cost, str);
	cout << ts.Result() << endl;

	return 0;
}

