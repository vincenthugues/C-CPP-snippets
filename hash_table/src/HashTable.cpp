#include <iostream>
#include "HashTable.hpp"

HashTable::HashTable(size_t tableSize)
	: _tableSize(tableSize),
	_table(new Item*[tableSize])
{
	for (size_t i = 0; i < tableSize; ++i)
		_table[i] = NULL;
}

HashTable::~HashTable()
{
	for (size_t i = 0; i < _tableSize; ++i)
	{
		Item *item = _table[i];
		
		while (item != NULL)
		{
			Item *nextItem = item->next;
			
			std::cout << "Deleting item " << item->key << ":" << item->value << std::endl;
			delete item;
			item = nextItem;
		}
	}
	
	delete  _table;
}

int HashTable::Hash(std::string key) const
{
	int n = 0;
	
	for (size_t i = 0; i < key.length(); ++i)
		n += (int)key[i];
	
	return n % _tableSize;
}

void HashTable::AddItem(std::string key, std::string value)
{
	int index = Hash(key);
	
	Item *item = new Item();
	item->key = key;
	item->value = value;
	item->next = NULL;
	
	std::cout << "Storing item " << item->key << ":" << item->value << " at index " << index << std::endl;
	
	if (_table[index] == NULL)
		_table[index] = item;
	else
	{
		Item *prevItem = _table[index];
		
		while (prevItem->next != NULL)
			prevItem = prevItem->next;
		
		prevItem->next = item;
	}
}
