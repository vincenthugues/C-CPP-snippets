#include <iostream>
#include <vector>
#include "HashTable.hpp"

// random_string
// stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string getRandomString(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		
		const size_t max_index = (sizeof(charset) - 1);
		
		return charset[rand() % max_index];
	};
	
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	
	return str;
}

size_t hashFunction(const std::string & key)
{
	int n = 0;
	
	for (size_t i = 0; i < key.length(); ++i)
		n += static_cast<size_t>(key[i]);
	
	return n;
}

// Robert Sedgwicks simple hash function
size_t RSHash(const std::string& str)
{
	size_t a = 63689, b = 378551, hash = 0;
	
	for (size_t i = 0; i < str.length(); ++i)
	{
		hash = hash * a + str[i];
		a *= b;
	}

	return hash;
}

void testHashTable1()
{
	HashTable< std::string > table(256, &hashFunction);
	std::vector< std::pair< std::string, std::string > > dataset;
	
	for (int i = 0; i < 1000; ++i)
	{
		dataset.push_back(std::pair< std::string, std::string >(
			getRandomString(rand() % 10 + 1),
			getRandomString(rand() % 30 + 1)));
		
		table.insert(dataset[i].first, dataset[i].second);
	}
	
	for (int i = 0; i < 100; ++i)
	{
		std::string key = dataset[rand() % dataset.size()].first;
		
		table.remove(key);
	}
	
	table.showDistribution();
	table.printStats();
}

void testHashTable2()
{
	HashTable< std::string > table(64, &RSHash);
	
	for (int i = 0; i < 256; ++i)
		table.insert(
			getRandomString(rand() % 10 + 1),
			getRandomString(rand() % 30 + 1));
	
	table.showDistribution();
	table.printStats();
}

int main()
{
	std::srand(std::time(0));
	
	testHashTable2();
	
	return 0;
}
