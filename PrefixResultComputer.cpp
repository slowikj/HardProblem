#include "PrefixResultComputer.h"

PrefixResultComputer::PrefixResultComputer(const PrefixInfo& prevPref,
									 	   const int& revCost,
										   const string& curStr)
	: _previousPrefix(prevPref),
	  _reversingCost(revCost),
	  _lastString(curStr)
{
}

PrefixInfo PrefixResultComputer::Result () const
{
	return PrefixInfo(_lastString.String(),
					  PrefixResult(_ResultWithUnreversedEnd(),
								   _ResultWithReversedEnd()));
}

long long PrefixResultComputer::_ResultWithUnreversedEnd () const
{
	return _ResultWithEnd(_lastString.String());
}

long long PrefixResultComputer::_ResultWithReversedEnd () const
{
	long long res = _ResultWithEnd(_lastString
								   .ReversedString());

	return (res == INF ? res
					   : res + _reversingCost);
}

long long PrefixResultComputer::_ResultWithEnd(const string& s) const
{
	long long res = INF;

	if (s >= _previousPrefix.LastString())
		res = min(res,
				  _previousPrefix.ResultWithUnreversedEnd());

	if (s >= _previousPrefix.LastStringReversed())
		res = min(res,
				  _previousPrefix.ResultWithReversedEnd());

	return res;
}
