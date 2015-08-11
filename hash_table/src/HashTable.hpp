#include <vector>
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
		: _tableSize(tableSize),
		_table(std::vector<Entry*>(tableSize)),
		_hashFunction(hashFunction),
		_nbEntries(0)
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
	}

	size_t Hash(std::string key) const
	{
		if (_hashFunction)
			return _hashFunction(key, _tableSize);
		
		int n = 0;
		
		for (size_t i = 0; i < key.length(); ++i)
			n += static_cast<size_t>(key[i]);
		
		return n % _tableSize;
	}

	void AddEntry(std::string key, T value)
	{
		size_t index = Hash(key);
		
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
	}

	void RemoveEntry(std::string key)
	{
		size_t index = Hash(key);
		
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
		size_t nbEmptyBuckets = 0, nbCollisions = 0, biggestBucketSize = 0;
		double mean = static_cast<double>(_nbEntries) / static_cast<double>(_tableSize); // Load factor
		double variance = 0, standardDeviation;
		
		for (size_t index = 0; index < _tableSize; ++index)
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
		
		variance /= _tableSize;
		standardDeviation = sqrt(variance);
		
		std::cout << "Number of entries: " << _nbEntries
			<< "\nEmpty buckets: " << nbEmptyBuckets
			<< "\nCollisions: " << nbCollisions
			<< "\nBiggest bucket size: " << biggestBucketSize
			<< "\nLoad factor: " << mean
			<< "\nVariance: " << variance
			<< "\nStandard deviation: " << standardDeviation
			<< std::endl;
	}

protected:
	size_t _tableSize;
	std::vector<Entry*> _table;
	size_t (*_hashFunction)(const std::string & key, size_t tableSize);
	size_t _nbEntries;
};

#endif
