#include "Data.h"

#include <memory.h>
#include <stdlib.h>

const Data Data::Null;

Data::Data()
	: _bytes(nullptr)
	, _size(0)
{
}

Data::Data(Data&& other)
	: _bytes(nullptr)
	, _size(0)
{
	move(other);
}

Data::Data(const Data& other)
	: _bytes(nullptr)
	, _size(0)
{
	copy(other._bytes, other._size);
}

Data::~Data()
{
	clear();
}

Data& Data::operator= (const Data& other)
{
	copy(other._bytes, other._size);
	return *this;
}

Data& Data::operator= (Data&& other)
{
	move(other);
	return *this;
}

void Data::move(Data& other)
{
	_bytes = other._bytes;
	_size = other._size;

	other._bytes = nullptr;
	other._size = 0;
}

bool Data::isNull() const
{
	return (_bytes == nullptr || _size == 0);
}

unsigned char* Data::getBytes() const
{
	return _bytes;
}

ssize_t Data::getSize() const
{
	return _size;
}

void Data::copy(const unsigned char* bytes, const ssize_t size)
{
	clear();

	if (size > 0)
	{
		_size = size;
		_bytes = (unsigned char*)malloc(sizeof(unsigned char) * _size);
		memcpy(_bytes, bytes, _size);
	}
}

void Data::fastSet(unsigned char* bytes, const ssize_t size)
{
	_bytes = bytes;
	_size = size;
}

void Data::clear()
{
	free(_bytes);
	_bytes = nullptr;
	_size = 0;
}
