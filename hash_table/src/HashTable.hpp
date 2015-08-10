#include <string>

#ifndef HASH_TABLE_HPP_
# define HASH_TABLE_HPP_

template <typename T>
class HashTable {
public:
	struct Entry {
		std::string key;
		T value;
		Entry *next;
	};

	HashTable(size_t tableSize = 100, int (*hashFunction)(const std::string &, int) = NULL)
		: _tableSize(tableSize),
		_table(new Entry*[tableSize]),
		_hashFunction(hashFunction)
	{
		for (size_t i = 0; i < tableSize; ++i)
			_table[i] = NULL;
	}

	~HashTable()
	{
		for (size_t i = 0; i < _tableSize; ++i)
		{
			Entry *entry = _table[i];
			
			while (entry != NULL)
			{
				Entry *nextEntry = entry->next;
				
				// std::cout << "Destructor: Deleting entry with key " << entry->key << std::endl;
				delete entry;
				entry = nextEntry;
			}
		}
		
		delete [] _table;
	}

	int Hash(std::string key) const
	{
		if (_hashFunction)
			return _hashFunction(key, _tableSize);
		
		int n = 0;
		
		for (size_t i = 0; i < key.length(); ++i)
			n += static_cast<int>(key[i]);
		
		return n % _tableSize;
	}

	void AddEntry(std::string key, T value)
	{
		int index = Hash(key);
		
		Entry *entry = new Entry();
		entry->key = key;
		entry->value = value;
		entry->next = NULL;
		
		// std::cout << "Storing entry at index " << index << std::endl;
		
		if (_table[index] == NULL)
			_table[index] = entry;
		else
		{
			Entry *prevEntry = _table[index];
			
			while (prevEntry->next != NULL)
				prevEntry = prevEntry->next;
			
			prevEntry->next = entry;
		}
	}

	void RemoveEntry(std::string key)
	{
		int index = Hash(key);
		
		// std::cout << "Removing entry at index " << index << std::endl;
		
		Entry *prevEntry = NULL, *entry = _table[index];
		while (entry != NULL)
		{
			if (entry->key == key)
			{
				// If there's a previous entry, link it to the next one;
				// otherwise the entry was the first one so the table's entry needs to be updated
				if (prevEntry)
					prevEntry->next = entry->next;
				else
					_table[index] = entry->next;
				
				// Free the node's memory space
				delete entry;
				
				return;
			}
			
			prevEntry = entry;
			entry = entry->next;
		}
	}

	void showDistribution() const
	{
		for (size_t index = 0; index < _tableSize; ++index)
		{
			std::cout << "[" << index << "]\t";
			for (Entry *entry = _table[index]; entry != NULL; entry = entry->next)
				std::cout << "+";
			std::cout << std::endl;
		}
	}

	void printStats() const
	{
		size_t nbEntries = 0, nbEmptyBuckets = 0, nbCollisions = 0, biggestBucketSize = 0;
		float loadFactor, variance, standardDeviation;
		
		for (size_t index = 0; index < _tableSize; ++index)
		{
			Entry *bucketHead = _table[index];
			
			if (bucketHead)
			{
				size_t bucketSize = 0;
				
				for (Entry *entry = bucketHead; entry != NULL; entry = entry->next)
					++bucketSize;
				
				nbEntries += bucketSize;
				
				if (bucketSize > 1)
					nbCollisions += bucketSize - 1;
				
				if (bucketSize > biggestBucketSize)
					biggestBucketSize = bucketSize;
			}
			else
				++nbEmptyBuckets;
		}
		
		loadFactor = nbEntries / _tableSize;
		
		std::cout << "Entries: " << nbEntries
			<< "\nEmpty buckets: " << nbEmptyBuckets
			<< "\nCollisions: " << nbCollisions
			<< "\nBiggest bucket size: " << biggestBucketSize
			<< "\nLoad factor: " << loadFactor
			<< std::endl;
	}

protected:
	size_t _tableSize;
	Entry ** _table;
	int (*_hashFunction)(const std::string & key, int tableSize);
};

#endif
