#include <string>

#ifndef HASH_TABLE_HPP_
# define HASH_TABLE_HPP_

template <typename T>
class HashTable {
public:
	struct Item {
		std::string key;
		T value;
		Item *next;
	};

	HashTable(size_t tableSize = 100)
		: _tableSize(tableSize),
		_table(new Item*[tableSize])
	{
		for (size_t i = 0; i < tableSize; ++i)
			_table[i] = NULL;
	}

	~HashTable()
	{
		for (size_t i = 0; i < _tableSize; ++i)
		{
			Item *item = _table[i];
			
			while (item != NULL)
			{
				Item *nextItem = item->next;
				
				std::cout << "Deleting item with key " << item->key << std::endl;
				delete item;
				item = nextItem;
			}
		}
		
		delete  _table;
	}

	int Hash(std::string key) const
	{
		int n = 0;
		
		for (size_t i = 0; i < key.length(); ++i)
			n += static_cast<int>(key[i]);
		
		return n % _tableSize;
	}

	void AddItem(std::string key, T value)
	{
		int index = Hash(key);
		
		Item *item = new Item();
		item->key = key;
		item->value = value;
		item->next = NULL;
		
		std::cout << "Storing item at index " << index << std::endl;
		
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

protected:
	size_t _tableSize;
	Item ** _table;
};

#endif
