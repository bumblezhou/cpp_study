#include <iostream>
#include <vector>

using namespace std;

#include <iostream>
#include <algorithm>

class MemoryBlock
{
public:

	// Simple constructor that initializes the resource.
	explicit MemoryBlock(size_t length)
	  : _length(length)
	  , _data(new int[length])
	{
		std::cout << "In MemoryBlock(size_t). length = "
				<< _length << "." << std::endl;
	}

	// Destructor.
	~MemoryBlock()
	{
		std::cout << "In ~MemoryBlock(). length = "
				<< _length << ".";

		if (_data != nullptr)
		{
			std::cout << " Deleting resource.";
			// Delete the resource.
			delete[] _data;
		}

		std::cout << std::endl;
	}

	// Move constructor.
    MemoryBlock(MemoryBlock&& other) noexcept
       : _data(nullptr)
       , _length(0)
    {
		std::cout << "In MemoryBlock(MemoryBlock&&). length = "
				 << other._length << ". Moving resource." << std::endl;

		*this = std::move(other);
    }
    
    // Move assignment operator.
    MemoryBlock& operator=(MemoryBlock&& other) noexcept
    {
		std::cout << "In operator=(MemoryBlock&&). length = "
				 << other._length << "." << std::endl;

		if (this != &other)
		{
			// Free the existing resource.
			delete[] _data;

			// Copy the data pointer and its length from the
			// source object.
			_data = other._data;
			_length = other._length;

			// Release the data pointer from the source object so that
			// the destructor does not free the memory multiple times.
			other._data = nullptr;
			other._length = 0;
		}
		return *this;
    }

	// Retrieves the length of the data resource.
	size_t Length() const
	{
		return _length;
	}

private:
	size_t _length; // The length of the resource.
	int* _data; // The resource.
};


int main()
{
	// Create a vector object and add a few elements to it.
	vector<MemoryBlock> v;
	v.push_back(MemoryBlock(25));
	v.push_back(MemoryBlock(75));

	// Insert a new element into the second position of the vector.
	v.insert(v.begin() + 1, MemoryBlock(50));

	return 0;
}
