#include "PrefixResultComputer.h"

PrefixResultComputer::PrefixResultComputer(const PrefixInfo& prevPref,
					 const int& revCost,
					 const string& curStr)
	: previousPrefix(prevPref),
	  reversingCost(revCost),
	  lastString(curStr)
{
}

PrefixInfo PrefixResultComputer::Result () const
{
	return PrefixInfo(this->lastString.String(),
					  PrefixResult(this->ResultWithUnreversedEnd(),
								   this->ResultWithReversedEnd()));
}

long long PrefixResultComputer::ResultWithUnreversedEnd () const
{
	return this->ResultWithEnd(this->lastString.String());
}

long long PrefixResultComputer::ResultWithReversedEnd () const
{
	long long res = this->ResultWithEnd(this->lastString
											 .ReversedString());

	return (res == INF ? res
					   : res + this->reversingCost);
}

long long PrefixResultComputer::ResultWithEnd(const string& s) const
{
	long long res = INF;

	if (s >= this->previousPrefix.LastString())
		res = min(res,
				  this->previousPrefix.ResultWithUnreversedEnd());

	if (s >= this->previousPrefix.LastStringReversed())
		res = min(res,
				  this->previousPrefix.ResultWithReversedEnd());

	return res;
}
