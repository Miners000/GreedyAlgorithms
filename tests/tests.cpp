#include <iostream>
#include <string>
#include <vector>

#define main cacheSim_main
#include "../src/cacheSim.cpp"
#undef main

using namespace std;

bool expectEqual(const string& testName, int actual, int expected)
{
	if(actual != expected)
	{
		cerr << "[FAIL] " << testName << " expected " << expected
			 << ", got " << actual << "\n";
		return false;
	}

	cout << "[PASS] " << testName << "\n";
	return true;
}

int main()
{
	bool allPassed = true;

	{
		vector<int> requests = {1, 2, 3, 1, 2, 3};
		allPassed &= expectEqual("FIFO warm cache then all hits", FIFO(3, requests), 3);
	}

	{
		vector<int> requests = {1, 2, 1, 3, 1, 2};
		allPassed &= expectEqual("FIFO replacement order", FIFO(2, requests), 5);
	}

	{
		vector<int> requests = {7, 7, 8, 8, 7};
		allPassed &= expectEqual("FIFO capacity one", FIFO(1, requests), 3);
	}

	{
		vector<int> requests = {
			1, 2, 3, 4, 1, 2, 5, 1, 2, 3,
			4, 5, 3, 2, 1, 4, 5, 3, 2, 1
		};
		allPassed &= expectEqual("FIFO provided example", FIFO(4, requests), 12);
	}

	{
		vector<int> requests = {1, 2, 3, 1, 2, 3};
		allPassed &= expectEqual("LRU warm cache then all hits", LRU(3, requests), 3);
	}

	{
		vector<int> requests = {1, 2, 1, 3, 1, 2};
		allPassed &= expectEqual("LRU recency-based eviction", LRU(2, requests), 4);
	}

	{
		vector<int> requests = {7, 7, 8, 8, 7};
		allPassed &= expectEqual("LRU capacity one", LRU(1, requests), 3);
	}

	{
		vector<int> requests = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
		allPassed &= expectEqual("LRU classic reference string", LRU(3, requests), 10);
	}

	if(!allPassed)
	{
		return 1;
	}

	cout << "All FIFO/LRU tests passed.\n";
	return 0;
}