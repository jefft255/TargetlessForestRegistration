#include "Registration.h"


Registration::Registration()
{
}


Registration::~Registration()
{
}

int Factorial(int n)
{
	int result = 1;
	while (n>1) {
		result *= n--;
	}
	return result;
}

/* Found on stackoverflow, user Vaughn Cato
http://stackoverflow.com/questions/28711797/generating-n-choose-k-permutations-in-c */
std::vector<std::vector<int>> nPerm(int n, int k)
{
	std::vector<std::vector<int>> result;
	std::vector<int> d(n);
	std::iota(d.begin(), d.end(), 1);
	int repeat = Factorial(n - k);
	do
	{
		std::vector<int> tempPerm = {};
		for (int i = 0; i < k; i++)
		{
			tempPerm.push_back(d[i]);
		}
		result.push_back(tempPerm);
		for (int i = 1; i != repeat; ++i)
		{
			next_permutation(d.begin(), d.end());
		}
	} while (next_permutation(d.begin(), d.end()));

	return result;
}