#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class ReversibleString
{
private:
	string str, revStr;

public:
	ReversibleString(const string& s)
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

	PrefixResult ()
	{
	}

	PrefixResult (long long unreversed, long long reversed)
		: lastUnreversed(unreversed), lastReversed(reversed)
	{
	}
};

class PrefixInfo
{
	ReversibleString lastString;
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

class TaskSolver
{
private:
	static const int MAXN = 1e5;
	static const int MAXCOST = 1e9;
	static const long long INF = (long long)MAXN * MAXCOST + 10;
	static const long long NOT_COMPUTED = -INF;

	int *cost;
	string *str;
	int numberOfStrings;
	long long result;

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

public:
	TaskSolver (const int& numberOfStrings, int *cost, string *str)
	{
		this->numberOfStrings = numberOfStrings;
		this->str = this->GetStringsCopy(numberOfStrings, str);
		this->cost = this->GetCostsCopy(numberOfStrings, cost);

		this->result = NOT_COMPUTED;
	}

private:
	int* ReadCosts ()
	{
		int *res = new int[this->numberOfStrings];
		for (int i = 0; i < this->numberOfStrings; ++i)
			cin >> res[i];

		return res;
	}

	string* ReadStrings ()
	{
		string *res = new string[this->numberOfStrings];
		for (int i = 0; i < this->numberOfStrings; ++i)
			cin >> res[i];

		return res;
	}

public:
	TaskSolver ()
	{
		cin >> this->numberOfStrings;
		this->cost = this->ReadCosts();
		this->str = this->ReadStrings();

		this->result = NOT_COMPUTED;
	}

	~TaskSolver ()
	{
		delete[] this->cost;
		delete[] this->str;
	}

private:
	long long PrefixResultWithUnreversedEnd (const PrefixInfo& previousPrefix,
											 const ReversibleString& lastStr) const
	{
		long long res = INF;

		if (lastStr.String() >= previousPrefix.LastString())
			res = min(res,
					  previousPrefix.ResultWithUnreversedEnd());

		if (lastStr.String() >= previousPrefix.LastStringReversed())
			res = min(res,
					  previousPrefix.ResultWithReversedEnd());

		return res;
	}	

	long long PrefixResultWithReversedEnd (const PrefixInfo& previousPrefix,
										   const ReversibleString& lastString,
									 	   const int& ind) const
	{
		long long res = INF;

		if (lastString.ReversedString() >= previousPrefix.LastString())
			res = min(res,
					  previousPrefix.ResultWithUnreversedEnd());

		if (lastString.ReversedString() >= previousPrefix.LastStringReversed())
			res = min(res,
					  previousPrefix.ResultWithReversedEnd());

		return res == INF ? res : res + this->cost[ind];
	}

	PrefixResult ResultForPrefix (const PrefixInfo& prefixInfo,
								  const int& ind) const
	{
		ReversibleString revStr = ReversibleString(this->str[ind]);

		return PrefixResult(this->PrefixResultWithUnreversedEnd(prefixInfo, revStr),
							this->PrefixResultWithReversedEnd(prefixInfo, revStr, ind));
	}

	long long ResultForEntireSequence () const
	{
		PrefixInfo prefixInfo(this->str[0],
							  PrefixResult(0, this->cost[0]));
		
		for (int i = 1; i < this->numberOfStrings; ++i)
			prefixInfo = PrefixInfo(this->str[i],
									this->ResultForPrefix(prefixInfo, i));

		long long res = min(prefixInfo.ResultWithUnreversedEnd(),
							prefixInfo.ResultWithReversedEnd());

		return res == INF ? -1 : res;
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

