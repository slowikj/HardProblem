//#pragma once

struct PrefixResult
{
	long long lastUnreversed;
	long long lastReversed;

	PrefixResult (long long unreversed, long long reversed)
		: lastUnreversed(unreversed), lastReversed(reversed)
	{
	}
};

