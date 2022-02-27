#pragma once
#include "../SArchive.h"
#include "../../CoreAPI.h"


//Can serialize(read) anything into a buffer
class CORE_API SDataSerializer : public SArchive
{
public:
	SDataSerializer();
	SDataSerializer(void* Data, uint64_t Size);

	~SDataSerializer();

	void* GetData() const { return _buffer; }
	uint32_t GetSize() const { return _bufferSize; }


	void SerializeWrite(const void* Data, uint64_t Lenght) override;


	void SerializeRead(void* Data, uint64_t Lenght) override;

private:

	void* _buffer;


	uint64_t _bufferSize;
	
	
	uint64_t  _bufferCapacity;
};