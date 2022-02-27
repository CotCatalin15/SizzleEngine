#pragma once
#include "Object.h"

#include <stdexcept>
#include <string>




template<typename T>
class SimpleObjectType : public Object
{
public:
	SimpleObjectType() : _val{}{}

	template<typename ... Args>
	SimpleObjectType(Args&& ... args) :
		_val{ std::forward<Args>(args)... }
	{}

	SimpleObjectType(SimpleObjectType<T> const& other) :
		_val{ other._val }
	{
	}

	SimpleObjectType(SimpleObjectType<T>&& other) :
		_val{ std::move(other._val) }
	{}



	operator T() const { return _val; }

	SimpleObjectType<T>& operator=(SimpleObjectType<T> const& other)
	{
		_val = other._val;
		return *this;
	}

	SimpleObjectType<T>& operator=(SimpleObjectType<T>&& other)
	{
		_val = std::move(other._val);
		return *this;
	}

	SimpleObjectType<T>& operator=(T const& val)
	{
		_val = val;
		return *this;
	}

	SimpleObjectType<T>& operator=(T&& val)
	{
		_val = std::move(val);
		return *this;
	}



	std::string GetName() const final override
	{
		return SimpleObjectType<T>::GetStaticName();
	}

	virtual uint64_t GetSize() const final override
	{
		return sizeof(T);
	}

	virtual Object* Clone() final override
	{
		return static_cast<Object*>(new SimpleObjectType<T>(std::ref(_val)));
	}

	static std::string GetStaticName()  { return "test"; }

private:
	T _val;
};


template<typename T>
T* ObjectCast(Object* obj)
{
	T* newType = dynamic_cast<T*>(obj);
	return newType;
}

template<> std::string SimpleObjectType<int32_t>::GetStaticName() { return "int32_t"; }
using Int32 = SimpleObjectType<int32_t>;

template<> std::string SimpleObjectType<uint32_t>::GetStaticName()  { return "uint32_t"; }
using UInt32 = SimpleObjectType<uint32_t>;

template<> std::string SimpleObjectType<int64_t>::GetStaticName()  { return "int64_t"; }
using Int64 = SimpleObjectType<int64_t>;

template<> std::string SimpleObjectType<uint64_t>::GetStaticName()  { return "uint64_t"; }
using UInt64 = SimpleObjectType<uint64_t>;

template<> std::string SimpleObjectType<float>::GetStaticName()  { return "float"; }
using Float = SimpleObjectType<float>;;

template<> std::string SimpleObjectType<double>::GetStaticName()   { return "double"; }
using Double = SimpleObjectType<double>;

template<> std::string SimpleObjectType<std::string>::GetStaticName()  { return "string"; }
using String = SimpleObjectType<std::string>;;