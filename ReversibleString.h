//#pragma once

#include <string>

using namespace std;

class ReversibleString
{
private:
	string str, revStr;

public:
	ReversibleString(const string& s);

	const string& String () const;
	const string& ReversedString () const;
};

