#include "TaskData.h"

TaskData::TaskData (const int& numberOfStrings, int *cost, string *str)
{
	this->numberOfStrings = numberOfStrings;
	this->str = this->GetStringsCopy(numberOfStrings, str);
	this->cost = this->GetCostsCopy(numberOfStrings, cost);
}

string* TaskData::GetStringsCopy (const int& numberOfStrings, string *str) const
{
	string *copiedStr = new string[numberOfStrings];
	for (int i = 0; i < numberOfStrings; ++i)
		copiedStr[i] = str[i];

	return copiedStr;
}

int* TaskData::GetCostsCopy (const int& numberOfStrings, int *cost) const
{
	int *copiedCosts = new int[numberOfStrings];
	for (int i = 0; i < numberOfStrings; ++i)
		copiedCosts[i] = cost[i];

	return copiedCosts;
}

TaskData::TaskData ()
{
	cin >> this->numberOfStrings;
	this->cost = this->ReadCosts();
	this->str = this->ReadStrings();
}

int* TaskData::ReadCosts () const
{
	int *res = new int[this->numberOfStrings];
	for (int i = 0; i < this->numberOfStrings; ++i)
		cin >> res[i];

	return res;
}

string* TaskData::ReadStrings () const
{
	string *res = new string[this->numberOfStrings];
	for (int i = 0; i < this->numberOfStrings; ++i)
		cin >> res[i];

	return res;
}

TaskData::~TaskData ()
{
	delete[] this->cost;
	delete[] this->str;
}

const string& TaskData::String(int index) const
{
	return this->str[index];
}

const int& TaskData::Cost(int index) const
{
	return this->cost[index];
}

const int& TaskData::NumberOfStrings() const
{
	return this->numberOfStrings;
}
