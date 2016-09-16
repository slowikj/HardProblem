#include "ReversibleString.h"
#include <algorithm>

using namespace std;

ReversibleString::ReversibleString(const string& s)
	: _str(s)
{
	_revStr = s;
	reverse(_revStr.begin(), _revStr.end());
}

const string& ReversibleString::String () const
{
	return _str;
}

const string& ReversibleString::ReversedString () const
{
	return _revStr;
}

