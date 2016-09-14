//#pragma once

#include <string>

using namespace std;

class ReversableString
{
private:
	string str, revStr;

public:
	ReversableString(const string& s);

	const string& String () const;
	const string& ReversedString () const;
};

