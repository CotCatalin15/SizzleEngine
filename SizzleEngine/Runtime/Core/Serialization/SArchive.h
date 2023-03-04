#pragma once

#include <vector>
#include <string>
#include "../CoreAPI.h"

class CORE_API SArchive
{
public:
	SArchive() :
		_bIsWriting{ false }
	{
		SetOffset(0);
	}

	SArchive(uint64_t Offset) :
		_bIsWriting{ false }
	{
		SetOffset(Offset);
	}

	SArchive(bool IsWriting) :
		_bIsWriting{ IsWriting }
	{
		SetOffset(0);
	}

	SArchive(uint32_t Offset, bool IsWriting) :
		_bIsWriting{ IsWriting }
	{
		SetOffset(Offset);
	}

	virtual ~SArchive() {}

	virtual void SetOffset(uint64_t NewOffset)
	{
		_offset = NewOffset;
	}

	uint64_t GetOffset() const { return _offset; }

	bool IsWritable() const { return _bIsWriting; }

	virtual SArchive& operator<<(SArchive& ar)
	{
		return *this;
	}


	friend CORE_API  SArchive& operator<<(SArchive& Ar, bool& val)
	{
		if (Ar._bIsWriting)
			Ar.SerializeWrite(&val, sizeof(float));
		else
			Ar.SerializeRead(&val, sizeof(float));
		return Ar;
	}

	friend CORE_API  SArchive& operator<<(SArchive& Ar, float& val)
	{
		if (Ar._bIsWriting)
			Ar.SerializeWrite(&val, sizeof(float));
		else
			Ar.SerializeRead(&val, sizeof(float));
		return Ar;
	}

	friend CORE_API  SArchive& operator<<(SArchive& Ar, double& val)
	{
		if (Ar._bIsWriting)
			Ar.SerializeWrite(&val, sizeof(double));
		else
			Ar.SerializeRead(&val, sizeof(double));
		return Ar;
	}

	friend CORE_API  SArchive& operator<<(SArchive& Ar, long double& val)
	{
		if (Ar._bIsWriting)
			Ar.SerializeWrite(&val, sizeof(long double));
		else
			Ar.SerializeRead(&val, sizeof(long double));
		return Ar;
	}

	friend CORE_API  SArchive& operator<<(SArchive& Ar, char& val)
	{
		if (Ar._bIsWriting)
			Ar.SerializeWrite(&val, sizeof(char));
		else
			Ar.SerializeRead(&val, sizeof(char));
		return Ar;
	}

	friend CORE_API  SArchive& operator<<(SArchive& Ar, unsigned char& val)
	{
		if (Ar._bIsWriting)
			Ar.SerializeWrite(&val, sizeof(unsigned char));
		else
			Ar.SerializeRead(&val, sizeof(unsigned char));

		return Ar;
	}

    friend CORE_API SArchive& operator<<(SArchive& Ar, int32_t& Val)
    {
        if (Ar._bIsWriting)
            Ar.SerializeWrite(&Val, sizeof(int32_t));
        else
            Ar.SerializeRead(&Val, sizeof(int32_t));
        return Ar;
    }

	friend CORE_API  SArchive& operator<<(SArchive& Ar, uint32_t& val)
	{
		if (Ar._bIsWriting)
			Ar.SerializeWrite(&val, sizeof(uint32_t));
		else
			Ar.SerializeRead(&val, sizeof(uint32_t));

		return Ar;
	}

	friend CORE_API  SArchive& operator<<(SArchive& Ar, int64_t& val)
	{
		if (Ar._bIsWriting)
			Ar.SerializeWrite(&val, sizeof(int64_t));
		else
			Ar.SerializeRead(&val, sizeof(int64_t));

		return Ar;
	}

	friend CORE_API SArchive& operator<<(SArchive& Ar, uint64_t& val)
	{
		if (Ar._bIsWriting)
			Ar.SerializeWrite(&val, sizeof(uint64_t));
		else
			Ar.SerializeRead(&val, sizeof(uint64_t));
		return Ar;
	}

	friend CORE_API SArchive& operator<<(SArchive& Ar, std::string& val)
	{
		size_t Size = val.size();
		Ar << Size;

		if (Ar._bIsWriting == false)
			val.resize(Size + 1);

		if (val.size() != 0)
		{
			if (Ar._bIsWriting)
				Ar.SerializeWrite(val.data(), Size + 1);
			else
				Ar.SerializeRead(val.data(), Size + 1);
		}

		return Ar;
	}

	template<typename T, typename A>
	friend SArchive& operator<<(SArchive& Ar, std::vector<T, A>& val)
	{
		uint32_t Size = (uint32_t)val.size();
		Ar << Size;

		if (Ar._bIsWriting == false)
			val.resize(Size);

		for (uint32_t i = 0; i < Size; ++i)
			Ar << val[i];

		return Ar;
	}


	virtual void SerializeWrite(const void* Data, uint64_t Lenght) = 0;

	virtual void SerializeRead(void* Data, uint64_t Lenght) = 0;

protected:
	uint64_t _offset;

private:

	bool _bIsWriting;
};
