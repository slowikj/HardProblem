//#pragma once

#include <string>
#include <climits>
#include "PrefixInfo.h"

using namespace std;

class PrefixResultComputer
{
private:
	PrefixInfo previousPrefix;
	int reversingCost;
	ReversableString lastString;

	static const long long INF = LLONG_MAX;

public:
	PrefixResultComputer(const PrefixInfo& prevPref,
						 const int& revCost,
						 const string& curStr);

private:
	long long ResultWithUnreversedEnd () const;
	long long ResultWithReversedEnd () const;
	long long ResultWithEnd(const string& s) const;

public:
	PrefixInfo Result () const;
};
