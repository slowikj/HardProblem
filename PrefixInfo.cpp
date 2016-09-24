#include "PrefixInfo.h"

PrefixInfo::PrefixInfo (const string& last, const PrefixResult& pr)
	: _lastString(last), _result(pr)
{
}

const string& PrefixInfo::LastString () const
{
	return _lastString.String();
}

const string& PrefixInfo::LastStringReversed () const
{
	return _lastString.ReversedString();
}

long long PrefixInfo::ResultWithUnreversedEnd () const
{
	return _result.lastUnreversed;
}

long long PrefixInfo::ResultWithReversedEnd () const
{
	return _result.lastReversed;
}

