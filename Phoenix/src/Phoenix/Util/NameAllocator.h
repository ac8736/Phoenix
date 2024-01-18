#pragma once

#include <unordered_map>

class NameAllocator
{
public:
	NameAllocator(int _maxCount) : maxCount(_maxCount)
	{

	}

	int getName();
	void returnName(int name);

private:
	int maxCount;
	int firstUnusedName = 0;
	std::unordered_map<int, int> restoredNames;
	std::unordered_map<int, int> allocatedNames;
};