#include <string>
#include <iostream>
#include <vector>

using namespace std;

class TaskData
{
private:
	vector<int> _costs;
	vector<string> _str;

public:
	TaskData (const int& numberOfStrings, const int *costs, const string *str);
	TaskData ();

private:
	vector<int> _GetReadCosts (const int& numberOfCosts);
	vector<string> _GetReadStrings (const int& numberOfStrings);

	template<class T>
	vector<T> _GetReadSequence (const int& n);
	
public:
	const string& String (const int& index) const;
	const int& Cost (const int& index) const;
	int NumberOfStrings () const;
};
