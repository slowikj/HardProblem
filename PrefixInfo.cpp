#include "PrefixInfo.h"

PrefixInfo::PrefixInfo (const string& last, const PrefixResult& pr)
	: lastString(last), result(pr)
{
}

const string& PrefixInfo::LastString () const
{
	return this->lastString.String();
}

const string& PrefixInfo::LastStringReversed () const
{
	return this->lastString.ReversedString();
}

long long PrefixInfo::ResultWithUnreversedEnd () const
{
	return this->result.lastUnreversed;
}

long long PrefixInfo::ResultWithReversedEnd () const
{
	return this->result.lastReversed;
}

