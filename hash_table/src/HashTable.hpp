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
				
				std::cout << "Destructor: Deleting item with key " << item->key << std::endl;
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

	void RemoveItem(std::string key)
	{
		int index = Hash(key);
		
		std::cout << "Removing item at index " << index << std::endl;
		
		Item *prevItem = NULL, *item = _table[index];
		while (item != NULL)
		{
			if (item->key == key)
			{
				// If there's a previous item, link it to the next one;
				// otherwise the item was the first one so the table's entry needs to be updated
				if (prevItem)
					prevItem->next = item->next;
				else
					_table[index] = item->next;
				
				// Free the node's memory space
				delete item;
				
				return;
			}
			
			prevItem = item;
			item = item->next;
		}
	}

protected:
	size_t _tableSize;
	Item ** _table;
};

#endif
