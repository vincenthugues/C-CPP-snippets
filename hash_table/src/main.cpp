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

void testHashTable()
{
	HashTable<std::string> table;
	std::vector< std::pair< std::string, std::string > > dataset;
	
	for (int i = 0; i < 1000; ++i)
	{
		dataset.push_back(std::pair< std::string, std::string >(
			getRandomString(rand() % 10 + 1),
			getRandomString(rand() % 30 + 1)));
		table.AddItem(dataset[i].first, dataset[i].second);
	}
	
	for (int i = 0; i < 100; ++i)
	{
		std::string key = dataset[rand() % dataset.size()].first;
		
		std::cout << "Remove first item with key = " << key << std::endl;
		table.RemoveItem(key);
	}
}

int main()
{
	testHashTable();
	
	return 0;
}
