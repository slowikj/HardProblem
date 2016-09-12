#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class TaskSolver
{
private:
	static const int LAST_NORM = 0;
	static const int LAST_REV = 1;
	static const int MAXN = 1e5;
	static const int MAXCOST = 1e9;
	static const int NUMBER_OF_STATES = 2;
	static const long long INF = (long long)MAXN * MAXCOST + 10;

	int *cost;
	string *str;
	string *revStr;
	int numberOfStrings;
	long long **res;

	void CopyStrings (const int& numberOfStrings, string *str)
	{
		this->str = new string[numberOfStrings];
		for (int i = 0; i < numberOfStrings; ++i)
			this->str[i] = str[i];
	}

	void CopyCosts (const int& numberOfStrings, int *cost)
	{
		this->cost = new int[numberOfStrings];
		for (int i = 0; i < numberOfStrings; ++i)
			this->cost[i] = cost[i];
	}		

public:
	TaskSolver (const int& numberOfStrings, int *cost, string *str)
	{
		this->numberOfStrings = numberOfStrings;
		this->CopyStrings(numberOfStrings, str);
		this->CopyCosts(numberOfStrings, cost);

		this->revStr = nullptr;
		this->res = nullptr;
	}

	~TaskSolver ()
	{
		delete[] this->cost;
		delete[] this->str;

		if (this->revStr)
			delete[] this->revStr;

		if (this->res)
		{
			for (int i = 0; i < this->numberOfStrings; ++i)
				if (this->res[i])
					delete[] this->res[i];
		}
	}

private:
	void ComputeForUnreversedEnd (const int& endIndex)
	{
		if (this->str[endIndex] >= this->str[endIndex - 1])
			this->res[endIndex][LAST_NORM] = min(this->res[endIndex][LAST_NORM],
												 this->res[endIndex - 1][LAST_NORM]);

		if (this->str[endIndex] >= this->revStr[endIndex - 1])
			this->res[endIndex][LAST_NORM] = min(this->res[endIndex][LAST_NORM],
												 this->res[endIndex - 1][LAST_REV]);
	}	

	void ComputeForReversedEnd (const int& endIndex)
	{
		if (this->revStr[endIndex] >= this->str[endIndex - 1])
			this->res[endIndex][LAST_REV] = min(this->res[endIndex][LAST_REV],
												this->res[endIndex - 1][LAST_NORM] + this->cost[endIndex]);

		if (this->revStr[endIndex] >= this->revStr[endIndex - 1])
			this->res[endIndex][LAST_REV] = min(this->res[endIndex][LAST_REV],
												this->res[endIndex - 1][LAST_REV] + this->cost[endIndex]);
	}

	void ComputeReversedStrings ()
	{
		for (int i = 0; i < this->numberOfStrings; ++i)
		{
			this->revStr[i] = this->str[i];
			reverse (this->revStr[i].begin(), this->revStr[i].end());
		}
	}

	void AssignInitialValues ()
	{
		for (int i = 0; i < this->numberOfStrings; ++i)
			this->res[i][0] = this->res[i][1] = INF;

		this->res[0][LAST_NORM] = 0;
		this->res[0][LAST_REV] = this->cost[0];
	}

	void CreateResArray ()
	{
		this->res = new long long*[this->numberOfStrings];
		
		for (int i = 0; i < this->numberOfStrings; ++i)
			this->res[i] = new long long[NUMBER_OF_STATES];
	}

	void CreateRevStrArray()
	{
		this->revStr = new string[this->numberOfStrings];
	}

	void Initialize ()
	{
		this->CreateResArray();
		this->AssignInitialValues();

		this->CreateRevStrArray();
		this->ComputeReversedStrings();
	}

	void ComputeResult ()
	{
		this->Initialize();
		
		for (int i = 1; i < this->numberOfStrings; ++i)
		{
			this->ComputeForUnreversedEnd(i);
			this->ComputeForReversedEnd(i);
		}
	}

	bool ResultIsNotComputed ()
	{
		return this->res == nullptr;
	}

public:
	long long GetResult ()
	{
		if (this->ResultIsNotComputed())
			this->ComputeResult();
	
		long long tmpTotalRes = min(res[this->numberOfStrings - 1][LAST_NORM],
								    res[this->numberOfStrings - 1][LAST_REV]);

		return (tmpTotalRes == INF ? (long long)-1 : tmpTotalRes);
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
	cout << ts.GetResult() << endl;

	return 0;
}

