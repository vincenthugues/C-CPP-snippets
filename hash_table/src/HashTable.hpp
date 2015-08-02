#include <string>

#ifndef HASH_TABLE_HPP_
# define HASH_TABLE_HPP_

class HashTable {
public:
	struct Item {
		std::string key;
		std::string value;
		Item *next;
	};
	
	HashTable(size_t tableSize);
	~HashTable();
	
	int Hash(std::string key) const;
	void AddItem(std::string key, std::string value);
	
protected:
	size_t _tableSize;
	Item ** _table;
};

#endif
