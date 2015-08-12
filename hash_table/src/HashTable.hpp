#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

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

	HashTable(size_t tableSize = 100, size_t (*hashFunction)(const std::string &, size_t) = NULL)
		: _table(std::vector<Entry*>(tableSize)),
		_hashFunction(hashFunction),
		_nbEntries(0),
		_loadThreshold(.75)
	{
		for (size_t i = 0; i < tableSize; ++i)
			_table[i] = NULL;
	}

	~HashTable()
	{
		destroyEntries();
	}

	size_t hash(std::string key, size_t tableSize) const
	{
		if (_hashFunction)
			return _hashFunction(key, tableSize);
		
		int n = 0;
		
		for (size_t i = 0; i < key.length(); ++i)
			n += static_cast<size_t>(key[i]);
		
		return n % tableSize;
	}

	// Add a new entry to the table
	bool insert(std::string key, T value)
	{
		size_t index = hash(key, _table.size());
		
		Entry *entry = new Entry();
		entry->key = key;
		entry->value = value;
		entry->next = NULL;
		
		if (_table[index] == NULL)
			_table[index] = entry;
		else
		{
			Entry *prevEntry = _table[index];
			
			while (prevEntry->next != NULL)
				prevEntry = prevEntry->next;
			
			prevEntry->next = entry;
		}
		
		++_nbEntries;
		
		double loadFactor = static_cast<double>(_nbEntries) / static_cast<double>(_table.size());
		if (loadFactor > _loadThreshold)
		{
			resize(_table.size() + std::max(static_cast<size_t>(_table.size() * .2), static_cast<size_t>(1000)));
			std::cout << "load factor " << loadFactor << std::endl;
		}
		
		return true;
	}

	// Remove the entry with the given key
	bool remove(std::string key)
	{
		size_t index = hash(key, _table.size());
		
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
				
				--_nbEntries;
				
				return true;
			}
			
			prevEntry = entry;
			entry = entry->next;
		}
		
		// No corresponding entry found
		return false;
	}

	void resize(size_t newSize)
	{
		std::vector<Entry*> newTable(newSize);
		
		std::cout << "Resizing table from " << _table.size() << " to " << newSize << std::endl;
		
		for (size_t index = 0; index < _table.size(); ++index)
		{
			Entry *bucketHead = _table[index];
			
			if (bucketHead)
			{
				Entry *nextEntry = NULL;
				
				for (Entry *entry = bucketHead; entry != NULL; entry = nextEntry)
				{
					size_t newIndex = hash(entry->key, newSize);
					
					// Detach the node from the list but keep the pointer for the next iteration
					nextEntry = entry->next;
					entry->next = NULL;
					
					if (newTable[newIndex] == NULL)
						newTable[newIndex] = entry;
					else
					{
						Entry *lastEntry = newTable[newIndex];
						
						while (lastEntry->next != NULL)
							lastEntry = lastEntry->next;
						
						lastEntry->next = entry;
					}
				}
			}
		}
		
		_table = newTable;
	}

	void showDistribution() const
	{
		for (size_t index = 0; index < _table.size(); ++index)
		{
			std::cout << "[" << index << "]\t";
			for (Entry *entry = _table[index]; entry != NULL; entry = entry->next)
				std::cout << "+";
			std::cout << std::endl;
		}
	}

	void printStats() const
	{
		size_t nbEmptyBuckets = 0, nbCollisions = 0, biggestBucketSize = 0;
		double mean = static_cast<double>(_nbEntries) / static_cast<double>(_table.size()); // Load factor
		double variance = 0;
		
		for (size_t index = 0; index < _table.size(); ++index)
		{
			Entry *bucketHead = _table[index];
			
			if (bucketHead)
			{
				size_t bucketSize = 0;
				
				for (Entry *entry = bucketHead; entry != NULL; entry = entry->next)
					++bucketSize;
				
				if (bucketSize > 1)
					nbCollisions += bucketSize - 1;
				
				if (bucketSize > biggestBucketSize)
					biggestBucketSize = bucketSize;
				
				variance += pow(bucketSize - mean, 2);
			}
			else
				++nbEmptyBuckets;
		}
		
		variance /= static_cast<double>(_table.size());
		
		std::cout << "Number of entries: " << _nbEntries
			<< "\nNumber of buckets: " << _table.size()
			<< "\nEmpty buckets: " << nbEmptyBuckets
			<< "\nCollisions: " << nbCollisions
			<< "\nBiggest bucket size: " << biggestBucketSize
			<< "\nLoad factor: " << mean
			<< "\nVariance: " << variance
			<< "\nStandard deviation: " << sqrt(variance)
			<< std::endl;
	}

protected:
	void destroyEntries()
	{
		for (size_t i = 0; i < _table.size(); ++i)
		{
			Entry *entry = _table[i];
			
			while (entry != NULL)
			{
				Entry *nextEntry = entry->next;
				
				delete entry;
				
				entry = nextEntry;
			}
		}
	}

protected:
	std::vector<Entry*> _table;
	size_t (*_hashFunction)(const std::string & key, size_t tableSize);
	size_t _nbEntries;
	double _loadThreshold;
};

#endif
