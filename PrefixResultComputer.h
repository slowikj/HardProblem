//#pragma once

#include <string>
#include <climits>
#include "PrefixInfo.h"

using namespace std;

class PrefixResultComputer
{
private:
	PrefixInfo _previousPrefix;
	int _reversingCost;
	ReversibleString _lastString;

	static const long long INF = LLONG_MAX;

public:
	PrefixResultComputer(const PrefixInfo& prevPref,
						 const int& revCost,
						 const string& curStr);

	PrefixInfo Result () const;

private:
	long long _ResultWithUnreversedEnd () const;
	long long _ResultWithReversedEnd () const;
	long long _ResultWithEnd(const string& s) const;
};
