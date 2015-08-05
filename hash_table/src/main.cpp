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
		
		return charset[ rand() % max_index ];
	};
	
	std::string str(length,0);
	std::generate_n(str.begin(), length, randchar);
	
	return str;
}

void testHashTable()
{
	HashTable<std::string> table;
	std::vector< std::pair< std::string, std::string > > data;
	
	for (int i = 0; i < 1000; ++i)
		data.push_back(std::pair< std::string, std::string >(getRandomString(5), getRandomString(10)));
	
	for (size_t i = 0; i < data.size(); ++i)
	{
		// std::cout << "Add item { key = " << data[i].first << ", value = " << data[i].second << " }" << std::endl;
		table.AddItem(data[i].first, data[i].second);
	}
	
	// table.RemoveItem(keys[0]);
	// table.RemoveItem(keys[0]);
}

int main()
{
	testHashTable();
	
	return 0;
}
