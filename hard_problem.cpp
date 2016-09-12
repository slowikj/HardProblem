#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define debug(x) cerr << #x << " = " << (x) << endl

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

void Solve (const int& n, string str[], int cost[])
{
	const int LAST_NORM = 0;
	const int LAST_REV = 1;
	const int MAXN = 1e5;
	const int MAXCOST = 1e9;
	const long long INF = (long long)MAXN * MAXCOST + 10;

	long long res[n][2];

	res[0][LAST_NORM] = 0;
	res[0][LAST_REV] = cost[0];

	for (int i = 1; i < n; ++i)
	{
		string strRev = str[i];
		reverse (strRev.begin(), strRev.end());

		string prevStrRev = str[i - 1];
		reverse (prevStrRev.begin(), prevStrRev.end());

		res[i][LAST_NORM] = res[i][LAST_REV] = INF;

		if (str[i] >= str[i - 1])
			res[i][LAST_NORM] = min(res[i][LAST_NORM], res[i - 1][LAST_NORM]);
		if (str[i] >= prevStrRev)
			res[i][LAST_NORM] = min(res[i][LAST_NORM], res[i - 1][LAST_REV]);
		
		if (strRev >= str[i - 1])
			res[i][LAST_REV] = min(res[i][LAST_REV], res[i - 1][LAST_NORM] + cost[i]);
		if (strRev >= prevStrRev)
			res[i][LAST_REV] = min(res[i][LAST_REV], res[i - 1][LAST_REV] + cost[i]);
	}

	long long finalResult = min(res[n - 1][LAST_NORM], res[n - 1][LAST_REV]);

	cout << (finalResult == INF ? -1 : finalResult)  << endl;
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

