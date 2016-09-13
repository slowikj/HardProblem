#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int LAST_NORM = 0;
const int LAST_REV = 1;
const int MAXN = 1e5;
const int MAXCOST = 1e9;
const long long INF = (long long)MAXN * MAXCOST + 10;

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

void ComputeForUnreversedEnd (const int& prefixEnd,
							  const string& currentStr,
							  const string& previousStr, const string& reversedPrevStr,
							  long long res[][2])
{
	if (currentStr >= previousStr)
		res[prefixEnd][LAST_NORM] = min(res[prefixEnd][LAST_NORM],
										res[prefixEnd - 1][LAST_NORM]);

	if (currentStr >= reversedPrevStr)
		res[prefixEnd][LAST_NORM] = min(res[prefixEnd][LAST_NORM],
										res[prefixEnd - 1][LAST_REV]);
}

void ComputeForReversedEnd (const int& prefixEnd,
							const string& reversedCurrentStr,
							const string& previousStr, const string& reversedPreviousStr,
							int cost[], long long res[][2])
{
	if (reversedCurrentStr >= previousStr)
		res[prefixEnd][LAST_REV] = min(res[prefixEnd][LAST_REV],
									   res[prefixEnd - 1][LAST_NORM] + cost[prefixEnd]);

	if (reversedCurrentStr >= reversedPreviousStr)
		res[prefixEnd][LAST_REV] = min(res[prefixEnd][LAST_REV],
									   res[prefixEnd - 1][LAST_REV] + cost[prefixEnd]);
}

void ComputeReversedStrings (const int& n, string str[], string revStr[])
{
	for (int i = 0; i < n; ++i)
	{
		revStr[i] = str[i];
		reverse (revStr[i].begin(), revStr[i].end());
	}
}

void AssignInitialValues (const int& n, int cost[], long long res[][2])
{
	for (int i = 0; i < n; ++i)
		res[i][0] = res[i][1] = INF;

	res[0][LAST_NORM] = 0;
	res[0][LAST_REV] = cost[0];
}

long long GetResult (const int& n, string str[], int cost[])
{
	long long res[n][2];
	AssignInitialValues(n, cost, res);

	string revStr[n];
	ComputeReversedStrings(n, str, revStr);

	for (int i = 1; i < n; ++i)
	{
		ComputeForUnreversedEnd(i, str[i], str[i - 1], revStr[i - 1], res);
		ComputeForReversedEnd(i, revStr[i], str[i - 1], revStr[i - 1], cost, res); 
	}

	return min(res[n - 1][LAST_NORM], res[n - 1][LAST_REV]);
}

void Solve (const int& n, string str[], int cost[])
{
	long long res = GetResult(n, str, cost);
	cout << (res == INF ? -1 : res) << endl;
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

	Solve(n, str, cost);

	return 0;
}

