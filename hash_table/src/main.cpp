#include "HashTable.hpp"

void testHashTable()
{
	HashTable table(100);
	
	table.AddItem("key1", "testdata1");
	table.AddItem("key2", "testdata2");
	table.AddItem("key3", "testdata3");
}

int main()
{
	testHashTable();
	
	return 0;
}
