#include "HashTable.hpp"

void testHashTable()
{
	HashTable table(100);
	
	table.AddItem("key1", "testdata1");
	table.AddItem("key2", "testdata2");
	table.AddItem("key3", "testdata3");
	table.AddItem("1key", "testdata1bis");
}

int main()
{
	testHashTable();
	
	return 0;
}
