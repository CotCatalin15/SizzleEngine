
#include "..\Public\SDataSerializer.h"

#include "../Public/SDataSerializer.h"
#include "..\..\CoreDebug\DebugMacros.h"
#include <string.h>

SDataSerializer::SDataSerializer() :
	SArchive(true),
	_buffer{ nullptr },
	_bufferSize{ 0 },
	_bufferCapacity{ 32 }
{
	_buffer = ::operator new(_bufferCapacity);
}

SDataSerializer::SDataSerializer(void* Data, uint64_t Size) :
	SArchive(false),
	_buffer{ Data },
	_bufferSize{ Size }
{
}

SDataSerializer::~SDataSerializer()
{
	if (!_buffer || _bufferSize == 0)
	{
		::operator delete(_buffer);
	}
}

void SDataSerializer::SerializeWrite(const void* Data, uint64_t Lenght)
{
	if (_bufferSize + Lenght >= _bufferCapacity)
	{
		//resize
		void* newPtr = ::operator new(_bufferCapacity * 2 + 1);
		check(newPtr);
		memcpy(newPtr, _buffer, _bufferSize);

		::operator delete(_buffer);

		_buffer = newPtr;
		_bufferCapacity = _bufferCapacity * 2 + 1;
	}


	memcpy((char*)_buffer + _offset, Data, Lenght);
	SetOffset(_bufferSize + Lenght);
	_bufferSize = _offset;

}

void SDataSerializer::SerializeRead(void* Data, uint64_t Lenght)
{
	check(_offset + Lenght > _bufferSize);

	memcpy(Data, ((char*)_buffer + _offset), Lenght);

	SetOffset(_offset + Lenght);	
}
