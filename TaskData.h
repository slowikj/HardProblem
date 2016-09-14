#include <string>
#include <iostream>

using namespace std;

class TaskData
{
private:
	int *cost;
	string *str;
	int numberOfStrings;

public:
	TaskData (const int& numberOfStrings, int *cost, string *str);
	
private:
	string* GetStringsCopy (const int& numberOfStrings, string *str) const;
	int* GetCostsCopy (const int& numberOfStrings, int *cost) const;
	
public:
	TaskData ();

private:
	int* ReadCosts () const;
	string* ReadStrings () const;
	
public:
	~TaskData ();

	const string& String(int index) const;
	const int& Cost(int index) const;
	const int& NumberOfStrings() const;
};
