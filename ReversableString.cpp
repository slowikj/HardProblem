#include "ReversableString.h"
#include <algorithm>

using namespace std;

ReversableString::ReversableString(const string& s)
	: str(s)
{
	this->revStr = s;
	reverse(this->revStr.begin(), this->revStr.end());
}

const string& ReversableString::String () const
{
	return this->str;
}

const string& ReversableString::ReversedString () const
{
	return this->revStr;
}

