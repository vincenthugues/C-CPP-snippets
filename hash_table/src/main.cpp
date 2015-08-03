#include <iostream>
#include "HashTable.hpp"

void testHashTable()
{
	static const std::string keys[5] = { "key1", "key2", "key3", "key1", "1yek" };
	static const std::string values[5] = { "abc", "def", "ghi", "jkl", "mno" };
	
	HashTable<std::string> table;
	
	for (size_t i = 0; i < 5; ++i)
	{
		std::cout << "Add item { key = " << keys[i] << ", value = " << values[i] << " }" << std::endl;
		table.AddItem(keys[i], values[i]);
	}
}

int main()
{
	testHashTable();
	
	return 0;
}
