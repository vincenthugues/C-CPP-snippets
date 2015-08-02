#include "HashTable.hpp"

HashTable::HashTable(size_t tableSize)
	: _tableSize(tableSize),
	_table(new Item[tableSize])
{
	for (size_t i = 0; i < tableSize; ++i)
		_table[i] = NULL;
}

HashTable::~HashTable()
{
	delete  _table;
}

int HashTable::Hash(std::string key) const
{
	int n = 0;
	
	for (size_t i = 0; i < key.length(); ++i)
		n += (int)key[i];
	
	return n % this->_tableSize;
}

void HashTable::AddItem(std::string key, std::string value)
{
	int index = this->Hash(key);
	
	if (this->_table[index] == NULL)
	{
		Item *item = new Item();
	}
}
