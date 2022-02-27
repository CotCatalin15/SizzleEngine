#pragma once
#include "../Object.h"

#include <vector>
#include <map>
#include "../../ObjectCoreAPI.h"
#include "../../../Core/Serialization/SArchive.h"
#include <memory>
#include "../../../Core/Debug/DebugMacros.h"

class OBJECTCORE_API SField : public Object
{
private:
	class OBJECTCORE_API SFieldSerializerAny
	{
	public:
		virtual  void Serialize(SArchive& Ar, Object* obj, SField* field) = 0;
	private:
	};

	template<typename T>
	class SFieldSerializer : public SFieldSerializerAny
	{
	public:
		virtual void Serialize(SArchive& Ar, Object* Obj, SField* Field) final override
		{
			T* val = Field->CastFieldAs<T>(Obj);
			Ar << (*val);
		}
	};

public:
	~SField() = default;
	
	template<typename T>
	static SField* CreateField(std::string const& Type, std::string const& Name, uint32_t Size, uint32_t Offset, std::vector<std::string> const& Properties)
	{
		SField* field = CreateFieldInternal(Type, Name, Size, Offset, Properties);
		field->_serializer = std::make_unique< SFieldSerializer<T> >();

		return field;
	}


	uint64_t GetSize() const override;

	std::string GetName() const override;

	Object* Clone() override;


	uint32_t GetFieldSize() const { return _size; }
	uint32_t GetFieldOffset() const { return _offset; }

	inline std::string const& GetFieldType() const { return _type; }
	inline std::string const& GetFieldName() const { return _name; }

	inline std::vector<std::string> const& GetProperties() const { return _properties; }
	inline bool HasProperty(std::string const& Property)
	{
		return std::find(_properties.begin(), _properties.end(), Property) != _properties.end();
	}

	template<typename T>
	T* CastFieldAs(Object* obj)
	{
		check(sizeof(T) == _size);
		check(obj->GetSize() <= _size);

		if (obj)
		{
			char* ptr = (char*)(obj);

			ptr += _offset;
			return (T*)(ptr);
		}

		return nullptr;
	}

	SArchive& SerializeField(SArchive& ar, Object* Obj);

	
private:
	SField(std::string const& Type, std::string const& Name, uint32_t Size, uint32_t Offset, std::vector<std::string> const& Properties);

	static SField* CreateFieldInternal(std::string const& Type, std::string const& Name, uint32_t Size, uint32_t Offset, std::vector<std::string> const& Properties);
	

	std::string _type;


	std::string _name;

	uint32_t _size;

	uint32_t _offset;

	std::vector<std::string> _properties;


	std::unique_ptr< SFieldSerializerAny > _serializer;
};


