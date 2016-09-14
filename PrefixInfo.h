//#pragma once

#include <string>
#include "PrefixResult.h"
#include "ReversibleString.h"

using namespace std;

class PrefixInfo
{
private:
	ReversibleString lastString;
	PrefixResult result;

public:
	PrefixInfo (const string& last, const PrefixResult& pr);
	
	const string& LastString () const;
	const string& LastStringReversed () const;
	
	long long ResultWithUnreversedEnd () const;
	long long ResultWithReversedEnd () const;
};

