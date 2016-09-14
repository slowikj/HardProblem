#include "ReversibleString.h"
#include <algorithm>

using namespace std;

ReversibleString::ReversibleString(const string& s)
	: str(s)
{
	this->revStr = s;
	reverse(this->revStr.begin(), this->revStr.end());
}

const string& ReversibleString::String () const
{
	return this->str;
}

const string& ReversibleString::ReversedString () const
{
	return this->revStr;
}

